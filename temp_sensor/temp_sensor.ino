// Make sure to include Onewire and Dallas Temperature libraries
#include "temp.h"

void setup(void)
{
  // initialize the Serial Monitor at a baud rate of 9600.
  Serial.begin(9600);
  
  tempBegin();
}

void loop(void){ 
  Serial.print("Celsius temperature: ");
  Serial.println(getTempCelsius());

  delay(1000);
}