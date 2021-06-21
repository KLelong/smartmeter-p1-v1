/*
 * sm-io.h
 * 
 * module to setup IO use
 */

//#define FACTORY_BUTTON D2
#define FACTORY_BUTTON D2

void ioSetup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(FACTORY_BUTTON, INPUT_PULLUP);
}

long factoryStart = 0;
int factButtonState = 0;

void ioLoop() {

factButtonState=digitalRead(FACTORY_BUTTON);
if (factButtonState==HIGH) {
 factoryStart=0;
 }
else
 {
  if (factoryStart==0) {
    factoryStart=millis();
  }   
  else
    if (millis()-factoryStart>5000) {
      DEBUG_LOG("factory reset\n");
      initReq=true;
    }
 }
}
