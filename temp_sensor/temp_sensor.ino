#include "httpServer.h"
#include "waterTempSensor.h"

void setup() {
  Serial.begin(115200);

  tempSensorBegin();

  initHttpServer();
}

// Loop function
void loop() {
  // Handle client requests
  handleClients();
}
