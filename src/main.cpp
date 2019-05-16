#include <Arduino.h>
#include "config/config.h"
#include "connection/wifi.h"
#include "connection/mqtt.h"

unsigned long readTime;

void setup() {
  Serial.begin(115200);
  readTime = 0;
  delay(10);
  iniciaGPIO();
  if (conectaWiFi()){
     iniciaMQTT();
     
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
      if (!MQTTClient.connected()) {
        connectaClienteMQTT();
      }
      if(millis() > readTime+6000){
          readTime = millis();
          
      }
  
      MQTTClient.loop(); 
  }else{
     if (conectaWiFi()){
     iniciaMQTT();
       
     }   
      
  }
}