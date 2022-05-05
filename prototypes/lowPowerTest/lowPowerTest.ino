#include "ArduinoLowPower.h"


void setup() {
  pinMode(1, OUTPUT);
  
}


void loop() {
  digitalWrite(1, HIGH);
  LowPower.deepSleep(1000);
  //delay(1000);
  digitalWrite(1, LOW);
  delay(1000);
}
