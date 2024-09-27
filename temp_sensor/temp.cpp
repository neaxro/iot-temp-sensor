// Make sure to include Onewire and Dallas Temperature libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// Connect your yellow pin to Pin12 on Arduino
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void tempBegin(){
  sensors.begin();
}

float getTempCelsius(){
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}

float getTempFahrenheit(){
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  return sensors.getTempFByIndex(0);
}
