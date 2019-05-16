#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ArduinoJson.h>

// construtor do objeto para comunicar com o sensor
DHT dht(DHTPIN, DHTTYPE);

//variáveis que armazenarão os valores lidos da umidade e temperatura
float umidade = 0.0;
float temperatura = 0.0;


char* createJson(float temperatura, float umidade);

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
  char* jsonTemHum = createJson(temperatura , umidade);
  Serial.println(jsonTemHum);
  MQTTClient.publish(TOPICOTEM2, jsonTemHum);
  MQTTClient.publish(TOPICOUMI2,String(umidade).c_str());

  }


  char* createJson(float temperatura, float umidade){
    StaticJsonDocument<500> doc;
    doc["sensor"] = "DHT11";
    doc["typeSensor"]="TempHum";
    doc["time"]="1234567890";
    JsonArray values = doc.createNestedArray("data");
    values.add(temperatura);
    values.add(umidade);
    char json[256];
    serializeJson(doc, json);;
    

    return json;
  }
