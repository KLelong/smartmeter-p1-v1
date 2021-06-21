/*
 * sm-http.h
 * 
 * module to handle http-server stuff
 */

bool updateReq = false;
bool loggedIn = false;
long rssi;
IPAddress oldIP;
IPAddress loginIP;

void handleRoot(){
// loggedIn=false;
 DEBUG_LOG("You called root page\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
  httpserver.sendHeader("Location", "/index.html",true);   //Redirect to our html web page
  httpserver.send(302, "text/plain","");
  
}

void handleIndex() {
 loggedIn=false;
 DEBUG_LOG("You called index page\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
 String s = FPSTR(index_html); //Read HTML contents
 httpserver.send(200, "text/html", s); //Send web page
}
 
void handleCSS() {
 loggedIn=loggedIn && (httpserver.client().remoteIP()==loginIP);
 DEBUG_LOG("You called CSS page\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
 String s = FPSTR(smartmeter_css); //Read HTML contents
 httpserver.send(200, "text/css", s); //Send web page
}

void handleConfig() {
 DEBUG_LOG("You called config page\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
 if (!httpserver.authenticate(www_username, www_password))
      //Basic Auth Method with Custom realm and Failure Response
      //return server.requestAuthentication(BASIC_AUTH, www_realm, authFailResponse);
      //Digest Auth Method with realm="Login Required" and empty Failure Response
      //return server.requestAuthentication(DIGEST_AUTH);
      //Digest Auth Method with Custom realm and empty Failure Response
      //return server.requestAuthentication(DIGEST_AUTH, www_realm);
      //Digest Auth Method with Custom realm and Failure Response
 {
   DEBUG_LOG("Auth start\n");
   return httpserver.requestAuthentication(DIGEST_AUTH, www_realm, authFailResponse);
 }
 String s = FPSTR(config_html); //Read HTML contents
 httpserver.send(200, "text/html", s); //Send web page
 loggedIn=true;
 loginIP=httpserver.client().remoteIP();
 DEBUG_LOG("Auth OK\n");
}
 
void handleAbout() {
 loggedIn=false;
 DEBUG_LOG("You called about page\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
 DEBUG_LOG(httpserver.client().remoteIP().toString());
 DEBUG_LOG("\n");
 String s = FPSTR(about_html); //Read HTML contents
 httpserver.send(200, "text/html", s); //Send web page
}

void handleFavIcon() {
 DEBUG_LOG("You called favIcon\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
 String s = FPSTR(favicon_ico); //Read HTML contents
 httpserver.send(200, "image/x-icon", s); //Send web page
 }

void handleData() {
  char output[256] = "Not recognized";
  String tempStr;
  char temp[32];
  char temp1[32];
  char msgpub[256];
  String message="";

 DEBUG_LOG("You called data\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
 if (httpserver.method()==HTTP_GET) {
  if (httpserver.args()>0) {
    if (httpserver.argName(0)==String("data")) {
      rssi = WiFi.RSSI();
      if (powerConsumptionDay>0) {
        message.concat("ConsDay=");
        tempStr="%lu";
        tempStr.toCharArray(temp,32);
        sprintf(temp1,temp,powerConsumptionDay);
        message.concat(temp1);
        message.concat(" ");
      }
      if (powerConsumptionNight>0) {
        message.concat("ConsNight=");
        tempStr="%lu";
        tempStr.toCharArray(temp,32);
        sprintf(temp1,temp,powerConsumptionNight);
        message.concat(temp1);
        message.concat(" ");
      }
      if (powerProductionDay>0) {
        message.concat("ProdDay=");
        tempStr="%lu";
        tempStr.toCharArray(temp,32);
        sprintf(temp1,temp,powerProductionDay);
        message.concat(temp1);
        message.concat(" ");
      }
      if (powerProductionNight>0) {
        message.concat("ProdNight=");
        tempStr="%lu";
        tempStr.toCharArray(temp,32);
        sprintf(temp1,temp,powerProductionNight);
        message.concat(temp1);
        message.concat(" ");
      }
      if (GasConsumption>0) {
        message.concat("ConsGas=");
        tempStr="%1.3f";
        tempStr.toCharArray(temp,32);
        sprintf(temp1,temp,GasConsumption);
        message.concat(temp1);
        message.concat(" ");
      }
      message.concat("ConsNow=%lu ");
      message.concat("ProdNow=%lu ");
      message.concat("Version=");
      message.concat(P1Version);
      message.concat(" Delay=");
      message.concat(PublishDelay);
      message.concat(" rssi=%d");
      
      message.toCharArray(msgpub, 256);
      sprintf(output,msgpub,CurrentPowerConsumption,CurrentPowerProduction,rssi);
      DEBUG_LOG(output);
      DEBUG_LOG("\n");
    }
    else {
      if (httpserver.argName(0)==String("config")) {
        message="HostName=";
        message.concat(hostName);
        message.concat(" MQTTServ=");
        message.concat(mqtt_server);
        message.concat(" MQTTPort=");
        message.concat(mqtt_port);
        message.concat(" MQTTUsr=");
        message.concat(mqtt_client);
        message.concat(" MQTTPass=NoneNone");
        message.concat(" MQTTfinger=");
        message.concat(fingerprint);
        message.concat(" MQTTTopic=");
        message.concat(mqtt_topic);
        message.concat(" Delay=");
        message.concat(PublishDelay);
        message.concat(" OTApass=NoneNone");
        message.concat(" www-user=");
        message.concat(www_username);
        message.concat(" www-pass=NoneNone");
        message.toCharArray(msgpub, 256);
        sprintf(output,msgpub,CurrentPowerConsumption,CurrentPowerProduction);
        DEBUG_LOG(output);
        DEBUG_LOG("\n");
      }
      else {
        if (httpserver.argName(0)==String("reset")) {
          DEBUG_LOG("Reset request");
          DEBUG_LOG("\n");
          resetReq=true;
          message="reset accepted";
          message.toCharArray(output,256);
        }
        else {
          if (httpserver.argName(0)==String("getdefs")) {
            DEBUG_LOG("defs request");
            DEBUG_LOG("\n");
            DEBUG_LOG("HostName:");
            DEBUG_LOG(EEPROMreadString(HOSTNAME_ADDR,HOSTNAME_LEN));
            DEBUG_LOG("|\n");
            DEBUG_LOG("MQTTServ:") ;
            DEBUG_LOG(EEPROMreadString(MQTTSERVER_ADDR,MQTTSERVER_LEN));
            DEBUG_LOG("|\n");
            DEBUG_LOG("MQTTPort:") ;
            DEBUG_LOG(EEPROMreadString(MQTTPORT_ADDR,MQTTPORT_LEN));
            DEBUG_LOG("|\n");
            DEBUG_LOG("MQTTUsr:") ;
            DEBUG_LOG(EEPROMreadString(MQTTCLIENT_ADDR,MQTTCLIENT_LEN));
            DEBUG_LOG("|\n");
            DEBUG_LOG("MQTTPass:") ;
            DEBUG_LOG(EEPROMreadString(MQTTPASS_ADDR,MQTTPASS_LEN));
            DEBUG_LOG("|\n");
            DEBUG_LOG("MQTTTopic:") ;
            DEBUG_LOG(EEPROMreadString(MQTTTOPIC_ADDR,MQTTTOPIC_LEN));
            DEBUG_LOG("|\n");
            DEBUG_LOG("Delay:") ;
            DEBUG_LOG(EEPROMreadString(DELAY_ADDR,DELAY_LEN));
            DEBUG_LOG("|\n");
            DEBUG_LOG("OTApass:") ;
            DEBUG_LOG(EEPROMreadString(OTAPASS_ADDR,OTAPASS_LEN));
            DEBUG_LOG("|\n");
            message="defaults accepted";
            message.toCharArray(output,256);
          }
          else {
            if (httpserver.argName(0)==String("update")) {
              DEBUG_LOG("update request");
              DEBUG_LOG("\n");
              message="Nog geen web-updates";
              message.toCharArray(output,256);
            }
          }
        }
      }
    }
  }
 httpserver.send(200, "text/plain", output); //Send web page
 }
 else {
   if (httpserver.method()==HTTP_POST) {
     DEBUG_LOG("data POST\n");
     loggedIn=loggedIn && (httpserver.client().remoteIP()==loginIP);
     if (httpserver.args()>0) {
        if (httpserver.argName(0)==String("saveprefs") && loggedIn) {
          DEBUG_LOG("save prefs\n");
          for(int i=0;i<httpserver.args();i++)
          {
            DEBUG_LOG(httpserver.argName(i));
            DEBUG_LOG(":");
            DEBUG_LOG(httpserver.arg(i));
            DEBUG_LOG("\n");
            if (httpserver.argName(i)=="HostName") {
              EEPROMwriteString(HOSTNAME_ADDR,httpserver.arg(i),HOSTNAME_LEN);
              DEBUG_LOG("saved\n");
            }
            else
            if (httpserver.argName(i)=="MQTTServ") {
              EEPROMwriteString(MQTTSERVER_ADDR,httpserver.arg(i),MQTTSERVER_LEN);
              DEBUG_LOG("saved\n");
            }
            else
            if (httpserver.argName(i)=="MQTTPort") {
              EEPROMwriteString(MQTTPORT_ADDR,httpserver.arg(i),MQTTPORT_LEN);
              DEBUG_LOG("saved\n");
            }
            else
            if (httpserver.argName(i)=="MQTTUsr") {
              EEPROMwriteString(MQTTCLIENT_ADDR,httpserver.arg(i),MQTTCLIENT_LEN);
              DEBUG_LOG("saved\n");
            }
            else
            if (httpserver.argName(i)=="MQTTPass") {
              if (!(httpserver.arg(i)=="NoneNone")) {
                EEPROMwriteString(MQTTPASS_ADDR,httpserver.arg(i),MQTTPASS_LEN);
                DEBUG_LOG("saved\n");
              }
            }
           else
            if (httpserver.argName(i)=="MQTTfinger") {
                EEPROMwriteString(MQTTS_ADDR,httpserver.arg(i),MQTTS_LEN);
                DEBUG_LOG("saved\n");
            }
           else
            if (httpserver.argName(i)=="MQTTTopic") {
              EEPROMwriteString(MQTTTOPIC_ADDR,httpserver.arg(i),MQTTTOPIC_LEN);
              DEBUG_LOG("saved\n");
            }
            else
            if (httpserver.argName(i)=="Delay") {
              EEPROMwriteString(DELAY_ADDR,httpserver.arg(i),DELAY_LEN);
              DEBUG_LOG("saved\n");
            }
            else
            if (httpserver.argName(i)=="OTApass") {
              if (!(httpserver.arg(i)=="NoneNone")) {
                EEPROMwriteString(OTAPASS_ADDR,httpserver.arg(i),OTAPASS_LEN);
                DEBUG_LOG("saved\n");
              }
            }
            else
            if (httpserver.argName(i)=="www-pass") {
              if (!(httpserver.arg(i)=="NoneNone")) {
                EEPROMwriteString(WWWPASS_ADDR,httpserver.arg(i),WWWPASS_LEN);
                DEBUG_LOG("saved\n");
              }
            }
            else
            if (httpserver.argName(i)=="www-user") {
                EEPROMwriteString(WWWUSER_ADDR,httpserver.arg(i),WWWUSER_LEN);
                DEBUG_LOG("saved\n");
            }
          }
          message="prefs saved";
          message.toCharArray(output,256);
          httpserver.send(200, "text/plain", output); //Send web page
        }
        else {
          message="prefs not saved (not logged in)";
          message.toCharArray(output,256);
          httpserver.send(403, "text/plain", output); //Send web page
        }
     }
   }
 }
 DEBUG_LOG("end data\n\n");
 }

void handleUpdate() {
 DEBUG_LOG("You called update page\n");
 DEBUG_LOG(httpserver.uri());
 DEBUG_LOG("\n");
 loggedIn=loggedIn && (httpserver.client().remoteIP()==loginIP);
 if (loggedIn) {
   String s = FPSTR(update_html); //Read HTML contents
   httpserver.send(200, "text/html", s); //Send web page
 }
 else {
   httpserver.send(403, "text/plain", "403 : Forbidden");
   DEBUG_LOG("not logged in\n");
 }
}
 
void handleNotFound() {

 DEBUG_LOG("Not found\n");
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += httpserver.uri();
  message += "\nMethod: ";
  message += (httpserver.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += httpserver.args();
  message += "\n";
  for (uint8_t i=0; i<httpserver.args(); i++){
    message += " NAME:"+httpserver.argName(i) + "\n VALUE:" + httpserver.arg(i) + "\n";
  }
 httpserver.send(404, "text/plain", message);
 DEBUG_LOG(message);
 DEBUG_LOG("\n");
}

void httpSetup() {
  httpserver.on("/", handleRoot);
  httpserver.on("/index.html", handleIndex); 
  httpserver.on("/smartmeter.css", handleCSS);
  httpserver.on("/favicon.ico", handleFavIcon);
  httpserver.on("/setup.html", handleConfig);
  httpserver.on("/about.html", handleAbout);
  httpserver.on("/update.html", handleUpdate);
  httpserver.on("/data/", handleData);
  httpserver.onNotFound(handleNotFound); 

    httpserver.on("/upload", HTTP_POST, []() {
      httpserver.sendHeader("Connection", "close");
      httpserver.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      delay(1000);
      ESP.restart();
    }, []() {
      HTTPUpload& upload = httpserver.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        WiFiUDP::stopAll();
        Serial.printf("Update: %s\n", upload.filename.c_str());
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if (!Update.begin(maxSketchSpace)) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      }
      yield();
    });
  
  httpserver.begin();
  MDNS.addService("http", "tcp", 80);

}
 
