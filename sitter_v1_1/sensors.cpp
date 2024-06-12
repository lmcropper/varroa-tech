#include <Wire.h>
#include <Arduino.h>
#include <AHT20.h>
#include <SparkFun_SGP30_Arduino_Library.h>
#include "sensors.h"

AHT20 aht20;
SGP30 sgp30;

Sensor_Data sensorOutput {0, 0, 0, 0, 0};

bool sensors_init(){
    if(sensors_AHT20_init){
        return 1;
    }
    return 0;
}

Sensor_Data sensors_getData(){
    return sensorOutput;
}

//Initialize AHT20
bool sensors_AHT20_init(){
    if (aht20.begin() == false){
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    return 0;
  }
  Serial.println("AHT20 acknowledged.");
  return 1;
}

//Initialize SGP30

bool sensors_SGP30_init(){
    
    //TODO: Add humidity compensation from AHT20 data
    return 0;
}

//Initialize SGP41
bool sensors_SGP41_init(){
    return 0;
}

//Get AHT20 data
bool sensors_AHT20_getData(){
    if(aht20.available()){
        sensorOutput.temperature = aht20.getTemperature();
        sensorOutput.humidity = aht20.getHumidity();
        return 1;
    }
    return 0;
}

// Get SGP30 data
// NOTES: SGP30 must gather in 1s intervals for baseline compensation to work.
// For the first 15s, it will return dummy values
// Data is returned in 2 3-byte sections, where 2 bytes are the data and 1 byte is CRC.
// Byte 1: CO2eq (ppm)
// Byte 2: TVOC (ppb)
bool sensors_SGP30_getData(){
    return 0;
}

//Get SGP41 Data
bool sensors_SGP41_getData(){
    return 0;
}

//Get MICS data
bool sensors_MICS_getData(){
    return 0;
}