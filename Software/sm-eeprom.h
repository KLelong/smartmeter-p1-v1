/*
 * sm-eeprom.h
 * 
 * module to handle EEPROM
 */

String EEPROMreadString(int add, int maxlen)
{
  int i;
  char data[maxlen];
  int len=0;
  unsigned char k;

  DEBUG_LOG("r add:");
  DEBUG_LOG(add);
  DEBUG_LOG("\n");
  
  k=EEPROM.read(add);
  while((k != '\0') && (len<maxlen))   //Read until null character or max length
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

void EEPROMwriteString(int add,String data, int maxlen)
{
  bool mod_val;
  int _size = data.length();
  int i;
  if (_size>maxlen) _size=maxlen;
  
  DEBUG_LOG("w add:");
  DEBUG_LOG(add);
  DEBUG_LOG("\n");
  
  mod_val=EEPROMreadString(add,maxlen)!=data;
  if (mod_val) {
    DEBUG_LOG("modified");
    for(i=0;i<_size;i++)
    {
      EEPROM.write(add+i,data[i]);
    }
    EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
    EEPROM.commit();
  }
  DEBUG_LOG("\n");
}

void EEPROMsetup() {
  EEPROM.begin(512);
  DEBUG_LOG("EEPROM magic :");
  DEBUG_LOG(highByte(EEPROM_MAGIC)*256+lowByte(EEPROM_MAGIC));
  DEBUG_LOG("|\n");

 int eeprom_magic=EEPROM.read(EEPROM_MAGIC_ADDR)*256+EEPROM.read(EEPROM_MAGIC_ADDR+1);
 if (eeprom_magic!=EEPROM_MAGIC){  //EEPROM not valid : clear it
    DEBUG_LOG("\nEEPROM init\n");
    for (int i = 0; i < 512; i++) {
      EEPROM.write(i, 0);
    }
//    EEPROM.commit();
    EEPROM.write(EEPROM_MAGIC_ADDR,highByte(EEPROM_MAGIC));
    EEPROM.write(EEPROM_MAGIC_ADDR+1,lowByte(EEPROM_MAGIC));
    EEPROM.commit();
    DEBUG_LOG("\nEEPROM read after init :");
    DEBUG_LOG(EEPROM.read(EEPROM_MAGIC_ADDR)*256+EEPROM.read(EEPROM_MAGIC_ADDR+1));
    DEBUG_LOG("|\n");
    wifiManager.resetSettings();      
    delay(1000);
    ESP.restart();
    delay(5000);

 }
 else {  // Magic OK -> EEPROM valid
  String tempString;
  tempString=EEPROMreadString(HOSTNAME_ADDR,HOSTNAME_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(hostName,int(HOSTNAME_LEN));
  DEBUG_LOG("Hostname :");
  DEBUG_LOG(hostName);
  DEBUG_LOG("\n");

  tempString=EEPROMreadString(MQTTSERVER_ADDR,MQTTSERVER_LEN);
  if (tempString.length()>0) {
    tempString.toCharArray(mqtt_server,int(MQTTSERVER_LEN));
    mqtt_server_def=true;    
  }
  DEBUG_LOG("mqtt_server :");
  DEBUG_LOG(mqtt_server);
  DEBUG_LOG("\n");

  tempString=EEPROMreadString(MQTTPASS_ADDR,MQTTPASS_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(mqtt_pass,int(MQTTPASS_LEN));
  DEBUG_LOG("mqtt_pass :");
  DEBUG_LOG(mqtt_pass);
  DEBUG_LOG("\n");
  
  tempString=EEPROMreadString(MQTTPORT_ADDR,MQTTPORT_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(mqtt_port,int(MQTTPORT_LEN));
  DEBUG_LOG("mqtt_port :");
  DEBUG_LOG(mqtt_port);
  DEBUG_LOG("\n");
  
  tempString=EEPROMreadString(MQTTTOPIC_ADDR,MQTTTOPIC_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(mqtt_topic,int(MQTTTOPIC_LEN));
  DEBUG_LOG("mqtt_topic :");
  DEBUG_LOG(mqtt_topic);
  DEBUG_LOG("\n");
  
  tempString=EEPROMreadString(MQTTCLIENT_ADDR,MQTTCLIENT_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(mqtt_client,int(MQTTCLIENT_LEN));
  DEBUG_LOG("mqtt_client :");
  DEBUG_LOG(mqtt_client);
  DEBUG_LOG("\n");

  tempString=EEPROMreadString(DELAY_ADDR,DELAY_LEN);
  if (tempString.length()>0) 
    PublishDelay=tempString.toInt();
  DEBUG_LOG("delay :");
  DEBUG_LOG(PublishDelay);
  DEBUG_LOG("\n");

  tempString=EEPROMreadString(OTAPASS_ADDR,OTAPASS_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(OTAPassword,OTAPASS_LEN);
  DEBUG_LOG("OTApassw :");
  DEBUG_LOG(OTAPassword);
  DEBUG_LOG("\n");

  tempString=EEPROMreadString(WWWUSER_ADDR,WWWUSER_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(www_username,WWWUSER_LEN);
  DEBUG_LOG("www_username :");
  DEBUG_LOG(www_username);
  DEBUG_LOG("\n");

  tempString=EEPROMreadString(WWWPASS_ADDR,WWWPASS_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(www_password,WWWPASS_LEN);
  DEBUG_LOG("www_password :");
  DEBUG_LOG(www_password);
  DEBUG_LOG("\n");

  tempString=EEPROMreadString(MQTTS_ADDR,MQTTS_LEN);
  if (tempString.length()>0) 
    tempString.toCharArray(fingerprint,MQTTS_LEN);
  DEBUG_LOG("mqtt fingerprint :");
  DEBUG_LOG(fingerprint);
  DEBUG_LOG("\n");
}
}
 
