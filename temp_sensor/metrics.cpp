#include <ESP8266WiFi.h>
#include "waterTempSensor.h"

#define IOT_DEVICE_NAME "esp-12E-jacuzzy"
#define IOT_WATER_TEMP_SENSOR_NAME "DS18B20"
#define IOT_AIR_TEMP_SENSOR_NAME "AIR_SENS"

String getDefaultLabels(){
  String macAddress = WiFi.macAddress();
  String labels = "";
  labels += "name=\"" + String(IOT_DEVICE_NAME) + "\"";
  labels += ", mac_address=\"" + macAddress + "\"";
  labels += ", location=\"kiulo\"";

  return labels;
}

String metricsGetSystem(){
  String labels = getDefaultLabels();

  unsigned long uptime = millis() / 1000;  // Uptime in seconds
  size_t freeHeap = ESP.getFreeHeap();     // Free heap in bytes
  int rssi = WiFi.RSSI();                  // Wi-Fi signal strength in dBm

  String metrics = "# HELP iot_uptime_seconds The uptime of the IoT device in seconds\n";
  metrics += "# TYPE iot_uptime_seconds counter\n";
  metrics += "iot_uptime_seconds{" + labels + "} " + String(uptime) + "\n";

  metrics += "\n# HELP iot_free_heap_bytes The free heap memory in bytes\n";
  metrics += "# TYPE iot_free_heap_bytes gauge\n";
  metrics += "iot_free_heap_bytes{" + labels + "} " + String(freeHeap) + "\n";

  metrics += "\n# HELP iot_wifi_signal_strength_dbm Wi-Fi signal strength in dBm\n";
  metrics += "# TYPE iot_wifi_signal_strength_dbm gauge\n";
  metrics += "iot_wifi_signal_strength_dbm{" + labels + "} " + String(rssi) + "\n";

  return metrics;
}

String metricsGetTemp(){
  String labels = getDefaultLabels();
  labels += ", sensor_type=\"" + String(IOT_WATER_TEMP_SENSOR_NAME) + "\"";
  labels += ", measured_object=\"jacuzzi\"";

  String metrics = "\n# HELP iot_measured_temperature_celsius The measured temperature by the IoT device in Celsius\n";
  metrics += "# TYPE iot_measured_temperature_celsius gauge\n";
  metrics += "iot_measured_temperature_celsius{" + labels + "} " + String(getWaterTemperatureFloat()) + "\n";

  labels = getDefaultLabels();
  labels += ", sensor_type=\"" + String(IOT_AIR_TEMP_SENSOR_NAME) + "\"";
  labels += ", measured_object=\"kiulo\"";

  metrics += "iot_measured_temperature_celsius{" + labels + "} " + String(getWaterTemperatureFloat()) + "\n";

  return metrics;
}

