#include <OneWire.h>
#include <DallasTemperature.h>

// Pin connected to the DS18B20 data line
#define ONE_WIRE_BUS 5  // GPIO 5 (D1 on ESP-12E)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float getWaterTemperatureFloat() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

String getWaterTemperatureString() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  if (tempC == DEVICE_DISCONNECTED_C) {
    return "Error: Could not read temperature";
  } else {
    return String(tempC) + " °C";
  }
}

void tempSensorBegin(){
  sensors.begin();
}