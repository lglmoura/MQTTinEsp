#include <Arduino.h>
#include "config/config.h"
#include "config/gpio.h"
#include "connection/wifi.h"


void setup() {
  Serial.begin(115200);
  delay(10);
  iniciaGPIO();
  if (conectaWiFi()){
     
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}