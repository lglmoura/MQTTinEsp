#include <Arduino.h>
#include "config/config.h"
#include "connection/wifi.h"
#include "connection/mqtt.h"
#include "sensors/ds18b.h"
#include "sensors/dht11.h"

unsigned long readTime;

void setup() {
  Serial.begin(115200);
  readTime = 0;
  delay(10);
  
  if (conectaWiFi()){
     iniciaMQTT();
     iniciaGPIO();
     initSensorDHT11();
     conectaSensorDS18b();
       
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
      if (!MQTTClient.connected()) {
        connectaClienteMQTT();
      }
      if(millis() > readTime+6000){
          readTime = millis();
          readSensorDS18B();
          readSensorDHT11();
      }
  
      MQTTClient.loop(); 
  }else{
     if (conectaWiFi()){
         iniciaMQTT();
         conectaSensorDS18b();  
     }   
      
  }
}