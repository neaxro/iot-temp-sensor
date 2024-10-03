#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>

Adafruit_BMP280 bmp; // I2C
Adafruit_AHTX0 aht;

sensors_event_t humidity, temp;

void initBMP(){
  unsigned status;

  status = bmp.begin();
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

float getAirPressureFloat(){
  return bmp.readPressure();
}


void initAHT(){
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
}

void readAHT(){
  aht.getEvent(&humidity, &temp);
}

// Celsius
float getAirTemperatureFloat(){
  readAHT();
  return temp.temperature;
}

// rH
float getAirHumidityFloat(){
  readAHT();
  return humidity.relative_humidity;
}

void initAirSensor(){
  Wire.begin();

  initBMP();
  initAHT();
}
