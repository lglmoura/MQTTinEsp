#include <OneWire.h>
#include <DallasTemperature.h>

// Setup a oneWire instance to communicate with any OneWire 
// devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(SENSORTEMPTOP1);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;

void printAddress(DeviceAddress deviceAddress);
void printTemperature(DeviceAddress deviceAddress);

void readTemperatura()
{
    sensors.requestTemperatures();
    printTemperature(insideThermometer);
}

boolean conectaSensorDS18b(void){
  Serial.println("Dallas Temperature Library");

  // locate devices on the bus
  Serial.print("Locating devices...");
  sensors.begin();
  
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  if (!sensors.getAddress(insideThermometer, 0)){ 
       Serial.println("Unable to find address for Device 0");
       return false; 
  }
  Serial.println("Unable to find address for insideThermometer");

  // show the addresses we found on the bus
  Serial.print("Device  Address: ");
  printAddress(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);
  return true; 
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.println(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
  //char str[4]=""
  //sprintf(str, "%f", tempC);
  MQTTClient.publish(TOPICOTEM1, String(tempC).c_str());
}