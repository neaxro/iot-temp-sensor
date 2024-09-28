#include "httpServer.h"
#include "waterTempSensor.h"

// WiFi credentials
#define SSID ""
#define PASSWORD ""

// For additional settings
// go to metrics.cpp for:
// - IOT_DEVICE_NAME
// - IOT_WATER_TEMP_SENSOR_NAME
// - IOT_AIR_TEMP_SENSOR_NAME
// go to waterTempSensor.cpp for:
// - ONE_WIRE_BUS

void setup() {
  Serial.begin(115200);

  tempSensorBegin();

  initHttpServer(SSID, PASSWORD);
}

// Loop function
void loop() {
  // Handle client requests
  handleClients();
}
