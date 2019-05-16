#define ledTop1 D4 // Led digital 2
int staLed1 = HIGH;

#define ledTop2 D5 // Led digital 5
int staLed2 = LOW;

#define DHTPIN D6     // pino de dados do DHT será ligado no D6 do esp
#define DHTTYPE DHT11   // tipo do sensor



void iniciaGPIO(void){
  
  pinMode(ledTop1, OUTPUT);
  digitalWrite(ledTop1, staLed1);

  pinMode(ledTop2, OUTPUT);
  digitalWrite(ledTop2, LOW);

 
}