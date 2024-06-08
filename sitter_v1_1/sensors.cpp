#include <Wire.h>
#include <Arduino.h>
#include <AHT20.h>
#include "sensors.h"

AHT20 aht20;

//Initialize AHT20
bool AHT20_init(){
    if (aht20.begin() == false){
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    return 0;
  }
  Serial.println("AHT20 acknowledged.");
  return 1;
}


float AHT20_getData(){
    Serial.print(aht20.getTemperature());
    Serial.print(", ");
    Serial.println(aht20.getHumidity());
    return 1;
}
