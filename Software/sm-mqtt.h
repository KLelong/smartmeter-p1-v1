/*
 * sm-mqtt.h
 * 
 * module to handle mqtt stuff
 */

void SubCallback(char* topic, byte* payload, unsigned int length) {
#ifdef DEBUG
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
#endif
  String topicStr(topic);
  if (topicStr.startsWith(mqttP1TopicS)) {
    String PayloadStr("");
    topicStr.remove(0,mqttP1TopicSLen);
    DEBUG_LOG(topicStr);
    if (topicStr=="delay")
     {
      DEBUG_LOG("\ngood topic\n");
      for (int i = 0; i < length; i++) {
        PayloadStr.concat((char)payload[i]);
      }
      PublishDelay=PayloadStr.toInt();
     }
    else
      if (topicStr=="version")
       {
        DEBUG_LOG("\ngood topic\n");
        sclient.publish(TopicPub, P1VersionArr);
        DEBUG_LOG("topic published :");
        DEBUG_LOG(P1Version);
        DEBUG_LOG("\n");
       }
  }
}

void MQTTsetup(){ 
  
  tempTopic=String(mqtt_topic);
  tempTopic.toCharArray(TopicPub,MQTTTOPIC_LEN);
  DEBUG_LOG("TopicPub:");
  DEBUG_LOG(TopicPub);
  DEBUG_LOG("\n");
  tempTopic.concat("/setup");
  mqttP1TopicS=tempTopic;
  mqttP1TopicSLen=mqttP1TopicS.length()+1; // subtract 1 to account for final "/"
  tempTopic.concat("/#");
  tempTopic.toCharArray(TopicSub,MQTTTOPIC_LEN);
  DEBUG_LOG("TopicSub:");
  DEBUG_LOG(TopicSub);
  DEBUG_LOG("\n");

  DEBUG_LOG("mqtt_server:");
  DEBUG_LOG(mqtt_server);
  DEBUG_LOG("\n");
  DEBUG_LOG("mqtt_port:");
  DEBUG_LOG(atoi(mqtt_port));
  DEBUG_LOG("\n");

  P1VersionStr="{\"Version\": \"";
  P1VersionStr.concat(String(P1Version));
  P1VersionStr.concat("\"}");
  P1VersionStr.toCharArray(P1VersionArr,VERSION_LEN);

  if (!(mqtt_server=="")) {
    sclient.setServer(mqtt_server, atoi(mqtt_port));
    sclient.setCallback(SubCallback);    
  }
}

long mqtt_reconnect=-10000;

void reconnect() {
  String tempTopic;
  if ((millis()-mqtt_reconnect)>5000) {
    DEBUG_LOG(mqtt_client);
    DEBUG_LOG("\n");
    DEBUG_LOG("Attempting MQTT connection...");
    if (sclient.connect(hostName,mqtt_client,mqtt_pass)) {
      Serial.println("mqtt connected");
      sclient.subscribe(TopicSub);
    } 
    else {
      Serial.print("failed, rc=");
      Serial.println(sclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      mqtt_reconnect=millis();
//      delay(5000);
    }
  }
}
/*  old version
void reconnect() {
  String tempTopic;
    DEBUG_LOG(mqtt_client);
    DEBUG_LOG("\n");
    DEBUG_LOG("Attempting MQTT connection...");
    if (client.connect(mqtt_client,mqtt_client,mqtt_pass)) {
      Serial.println("mqtt connected");
      client.subscribe(TopicSub);
    } 
    else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
}
*/
void publishP1ToMqtt(){
  char msgpub[256];
  char output[256];
  String tempStr;
  char temp[32];
  char temp1[32];
  String msg = "{";
  if (powerConsumptionDay>0) {
    msg.concat("\"powerConsumptionDay\": ");
    tempStr="%lu";
    tempStr.toCharArray(temp,32);
    sprintf(temp1,temp,powerConsumptionDay);
    msg.concat(temp1);
    msg.concat(",");
  }
  if (powerConsumptionNight>0) {
    msg.concat("\"powerConsumptionNight\": ");
    tempStr="%lu";
    tempStr.toCharArray(temp,32);
    sprintf(temp1,temp,powerConsumptionNight);
    msg.concat(temp1);
    msg.concat(",");
  }
  if (powerProductionDay>0) {
    msg.concat("\"powerProductionDay\": ");
    tempStr="%lu";
    tempStr.toCharArray(temp,32);
    sprintf(temp1,temp,powerProductionDay);
    msg.concat(temp1);
    msg.concat(",");
  }
  if (powerProductionNight>0) {
    msg.concat("\"powerProductionNight\": ");
    tempStr="%lu";
    tempStr.toCharArray(temp,32);
    sprintf(temp1,temp,powerProductionNight);
    msg.concat(temp1);
    msg.concat(",");
  }
  if (GasConsumption>0) {
    msg.concat("\"GasConsumption\": ");
    tempStr="%1.3f";
    tempStr.toCharArray(temp,32);
    sprintf(temp1,temp,GasConsumption);
    msg.concat(temp1);
    msg.concat(",");
  }
  msg.concat("\"CurrentPowerConsumption\": %lu,");
  msg.concat("\"CurrentPowerProduction\": %lu");
  msg.concat("}");
  msg.toCharArray(msgpub, 256);
  
  sprintf(output,msgpub,CurrentPowerConsumption,CurrentPowerProduction);
  sclient.publish(TopicPub, output);
  
  DEBUG_LOG("topic published :");
  DEBUG_LOG(output); 
  DEBUG_LOG("\n");
 
}

 
