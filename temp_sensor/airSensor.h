#ifndef AIR_SENSOR_H
#define AIR_SENSOR_H

void initAirSensor();

void initBMP();

float getAirPressureFloat();

void initAHT();

// Celsius
float getAirTemperatureFloat();

// % rH
float getAirHumidityFloat();

#endif