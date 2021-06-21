/*
 * to do
 * MQTT : als host en user gelijk zijn aan een ander device : mqtt-connect in een eindeloze lus. Er voor zorgen dat setup kan 
 *        gebruikt worden (hoe ?).
 * MQTT : beveiliging of niet : bij definitie van fingerprint : beveiligde mqtt, anders niet. Twee WiFiClients, één secure, andere niet.
 * 
*/

/*
 * device = ESP8266 Wemos D1 R2 & mini  
*/

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <ESP8266mDNS.h>
//#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <Ticker.h>

#include "index_html.h"
#include "about_html.h"
#include "config_html.h"
#include "update_html.h"
#include "smartmeter_css.h"
#include "favicon_ico.h"

/*
 * Version
 */
const char* P1Version = "1.19a";

#define DEBUG0
//
// If we did then DEBUG_LOG will log a string, otherwise
// it will be ignored as a comment.
//
#ifdef DEBUG
#  define DEBUG_LOG(x) Serial.print(x)
#else
#  define DEBUG_LOG(x)
#endif

#define EEPROM_MAGIC 31415 // to test if EEPROM is valid
#define EEPROM_MAGIC_ADDR 0 // 2 bytes
#define HOSTNAME_ADDR EEPROM_MAGIC_ADDR+2 // 
#define HOSTNAME_LEN 33
#define MQTTSERVER_ADDR HOSTNAME_ADDR+HOSTNAME_LEN
#define MQTTSERVER_LEN 33
#define MQTTPASS_ADDR MQTTSERVER_ADDR+MQTTSERVER_LEN
#define MQTTPASS_LEN 33
#define MQTTPORT_ADDR MQTTPASS_ADDR+MQTTPASS_LEN
#define MQTTPORT_LEN 6
#define MQTTTOPIC_ADDR MQTTPORT_ADDR+MQTTPORT_LEN
#define MQTTTOPIC_LEN 33
#define MQTTCLIENT_ADDR MQTTTOPIC_ADDR+MQTTTOPIC_LEN
#define MQTTCLIENT_LEN 33
#define DELAY_ADDR MQTTCLIENT_ADDR+MQTTCLIENT_LEN
#define DELAY_LEN 7
#define OTAPASS_ADDR DELAY_ADDR+DELAY_LEN
#define OTAPASS_LEN 33
#define WWWUSER_ADDR OTAPASS_ADDR+OTAPASS_LEN
#define WWWUSER_LEN 33
#define WWWPASS_ADDR WWWUSER_ADDR+WWWUSER_LEN
#define WWWPASS_LEN 33
#define MQTTS_ADDR WWWPASS_ADDR+WWWPASS_LEN  //sha1-fingerprint of mqtt-server
#define MQTTS_LEN 60

IPAddress mqttServerIP;
WiFiManager wifiManager;
WiFiClientSecure espClientS;
PubSubClient sclient(espClientS);
ESP8266WebServer httpserver(80);

#define MAXLINELENGTH 64
char telegram[MAXLINELENGTH];

char hostName[HOSTNAME_LEN] = "smartmeter-p1";
char mqtt_server[MQTTSERVER_LEN] = "";
char mqtt_pass[MQTTPASS_LEN] = "";
char mqtt_port[MQTTPORT_LEN] = "1883";
char mqtt_client[MQTTCLIENT_LEN] = "smartmeter";
char mqtt_topic[MQTTTOPIC_LEN] = "energy/p1";
char OTAPassword[OTAPASS_LEN] = "";
char www_username[WWWUSER_LEN] = "admin";
char www_password[WWWPASS_LEN] = "smartmeter-p1";
char fingerprint[MQTTS_LEN];// = "xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx";
// allows you to set the realm of authentication Default:"Login Required"
const char* www_realm = "Setup smartmeter-p1";
// the Content of the HTML response in case of Unautherized Access Default:empty
String authFailResponse = "Authentication Failed";

char TopicSub[MQTTTOPIC_LEN];  //topic to subscribe to
char TopicPub[MQTTTOPIC_LEN];  //topic to publish to
String tempTopic;
String mqttP1TopicS;
int mqttP1TopicSLen;
String P1VersionStr;
#define VERSION_LEN 25
char P1VersionArr[VERSION_LEN];

const bool outputOnSerial = true;
bool resetReq = false;
bool initReq = false;
bool mqtt_server_def = false;

// Vars to store meter readings
long powerConsumptionDay = 0;      //Meter reading Electrics - consumption day tariff in watt hours
long powerConsumptionNight = 0;    //Meter reading Electrics - consumption night tariff  in watt hours
long powerProductionDay = 0;       //Meter reading Electrics - return day tariff  in watt hours
long powerProductionNight = 0;     //Meter reading Electrics - return night tariff  in watt hours
long CurrentPowerConsumption = 0;  //Meter reading Electrics - Actual consumption in watts
long CurrentPowerProduction = 0;   //Meter reading Electrics - Actual return in watts
float GasConsumption = 0.0;        //Meter reading Gas in m3

//Infrastructure stuff
int PublishDelay = 10;             // 10 P1 telegrams before update of values.  
int TelegramCount = 0;             // Counter for received telegrams
//flag for saving data of WiFi manager
bool shouldSaveConfig = false;

#include "sm-eeprom.h"
#include "sm-io.h"
#include "sm-wifi.h"
#include "sm-http.h"
#include "sm-mqtt.h"
#include "sm-OTA.h"
#include "sm-serial.h"

void setup() {
    // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Booting");
  Serial.print("smartmeter-p1");
  Serial.println(" on Wemos D1 Mini & R2");
  Serial.print("Version : ");
  Serial.println(P1Version);
  
  EEPROMsetup();
  ioSetup();
  WiFiManagersetup();
  OTAsetup();
  MQTTsetup();
  httpSetup();
}

void loop() {
    // put your main code here, to run repeatedly:
  
  if (mqtt_server_def) {
    if (!sclient.connected()) {
      reconnect();
    }
    else {
      sclient.loop();
    }
  }
  readTelegram();    
  ArduinoOTA.handle();
  httpserver.handleClient();
  ioLoop();
  if (resetReq || initReq) {
    if (initReq) {  // Factory defaults ?
     EEPROM.write(EEPROM_MAGIC_ADDR,0);
     EEPROM.commit();
     DEBUG_LOG("EEPROM cleared\n");
    }
    delay (1000);                                // Yes, wait some time
    ESP.restart();                               // Reboot
    delay (1000);                                // Yes, wait some time
  } 
  MDNS.update(); 
  wifiloop();
}
