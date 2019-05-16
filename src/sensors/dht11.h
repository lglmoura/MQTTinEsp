#include <Adafruit_Sensor.h>
#include <DHT.h>

// construtor do objeto para comunicar com o sensor
DHT dht(DHTPIN, DHTTYPE);

//variáveis que armazenarão os valores lidos da umidade e temperatura
float umidade = 0.0;
float temperatura = 0.0;

boolean initSensorDHT11(void){
 
  //inicializa o objeto para comunicarmos com o sensor DHT
  dht.begin();
  return true; 
}

void readSensorDHT11() {

  //faz a leitura da umidade
  umidade = dht.readHumidity();
   Serial.print("Umidade: ");
   Serial.println(umidade);
  //faz a leitura da temperatura
  temperatura = dht.readTemperature();
  Serial.print("temp: ");
  Serial.println(String(temperatura).c_str());
  MQTTClient.publish(TOPICOTEM2, String(temperatura).c_str());
  MQTTClient.publish(TOPICOUMI2,String(umidade).c_str());

  }
