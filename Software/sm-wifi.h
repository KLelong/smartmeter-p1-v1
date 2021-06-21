/*
 * sm-wifi.h
 * 
 * module to setup wiFi
 */

Ticker ticker;

void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of built-in LED
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *MywifiManager) {
/*
  DEBUG_LOG("Entered config mode\n");
  DEBUG_LOG(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  DEBUG_LOG(MywifiManager->getConfigPortalSSID());
  DEBUG_LOG("\n");
  */
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}

//callback notifying us of the need to save config
void saveConfigCallback () {
  DEBUG_LOG("Should save config\n");
  shouldSaveConfig = true;
}

void WiFiManagersetup() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostName);
  DEBUG_LOG("start WiFiManager\n");

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    //reset saved settings
//    wifiManager.resetSettings();
//    wifiManager.setRemoveDuplicateAPs(false);
  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    wifiManager.setConfigPortalTimeout(300); //300 seconds timeout
#ifdef DEBUG
    DEBUG_LOG("start WiFiManager debug on\n");
    wifiManager.setDebugOutput(true);
#else
    DEBUG_LOG("start WiFiManager debug off\n");
    wifiManager.setDebugOutput(false);
#endif
    wifiManager.setCustomHeadElement("<style>body{background-color: lightsalmon;font-family: Arial, Helvetica, sans-serif;}input{border-radius: 10px;}button{background-color:#128F76;border-radius: 10px;}</style>");

    WiFiManagerParameter custom_hostname("hostname", "hostname", "", 40);
    wifiManager.addParameter(&custom_hostname);
    if (!wifiManager.autoConnect(hostName,"Koenraad")) {
      Serial.println("after time-out");
      delay(1000);
      ESP.reset();
      delay(1000);
    }
    //if you get here you have connected to the WiFi
    Serial.println("WiFi connected...");
    DEBUG_LOG("orig fingerprint : ");
    DEBUG_LOG(fingerprint);
    DEBUG_LOG("\n");
    String fingerprint_str=String(fingerprint);
    fingerprint_str.replace(':',' ');
    char mod_fingerprint[MQTTS_LEN];
    fingerprint_str.toCharArray(mod_fingerprint,MQTTS_LEN);
    DEBUG_LOG("mod fingerprint : ");
    DEBUG_LOG(mod_fingerprint);
    DEBUG_LOG("\n");
    espClientS.setFingerprint(mod_fingerprint);

    ticker.detach();
  //keep LED on
    digitalWrite(BUILTIN_LED, LOW);
   
    if (shouldSaveConfig) {
      DEBUG_LOG("saving config\n");
      if (custom_hostname.getValueLength()>0) {
        strcpy(hostName, custom_hostname.getValue());
        DEBUG_LOG("hostname :");
        DEBUG_LOG(hostName);
        DEBUG_LOG("\n");
        EEPROMwriteString(HOSTNAME_ADDR,hostName,HOSTNAME_LEN);
      }
    }
    Serial.println(WiFi.localIP());
//    DEBUG_LOG(WiFi.hostname);
    WiFi.setAutoReconnect(true);

}

long wifiTime = 0;
bool tickerAttached = false;

void wifiloop() {
if ((millis()-wifiTime) > 5000) {
  if (!WiFi.isConnected()) {
    if (!tickerAttached) {
      ticker.attach(1, tick);
      tickerAttached=true;
      DEBUG_LOG("wifi disconnected\n");      
    }
  }
  else {
    if (tickerAttached) {
      ticker.detach();
      tickerAttached=false;
      DEBUG_LOG("wifi OK\n");
    }
  }
  wifiTime=millis();  
}
}
