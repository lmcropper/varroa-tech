#include <Wire.h>
#include <Arduino.h>
#include <AHT20.h>
#include <SparkFun_SGP30_Arduino_Library.h>
#include <SensirionI2CSgp41.h>
#include "sensors.h"

AHT20 aht20;
SGP30 sgp30;
SensirionI2CSgp41 sgp41;

uint16_t sgp41_conditioning_s = 10; //Conditioning timer for SGP41

Sensor_Data sensorOutput {0, 0, 0, 0, 0, 0};

bool sensors_init(){
    // Serial.println("Initializing AHT20...");
    // if(!sensors_AHT20_init()){
    //     return 0;
    // }
    Serial.println("Initializing SGP30...");
    if(!sensors_SGP30_init()){
        return 0;
    }
    Serial.println("Initializing MICS-5524...");
    if(!sensors_MICS_init()){
        return 0;
    }
    return 1;
}

//Get readings from each sensor and return struct with all data values
Sensor_Data sensors_getData(){
    //sensors_AHT20_getData();
    sensors_SGP30_getData();
    sensors_MICS_getData();
    return sensorOutput;
}

//Initialize AHT20
bool sensors_AHT20_init(){
    if (aht20.begin() == false){
    Serial.println("AHT20 not detected. Check connections.");
    return 0;
  }
  Serial.println("AHT20 initialized.");
  return 1;
}

//Initialize SGP30
bool sensors_SGP30_init(){
    if(sgp30.begin() == false){
        Serial.println("SGP30 not detected. Check connections.");
        return 0;
    }
    sgp30.initAirQuality();
    //TODO: Add humidity compensation from AHT20 data
    Serial.println("SGP30 initialized.");
    return 1;
}

//Initialize SGP41
bool sensors_SGP41_init(){
    return 0;
}

//Initialize MICS-5524
bool sensors_MICS_init(){
    pinMode(PIN_MICS_5524_A0, INPUT);
    pinMode(PIN_MICS_5524_EN, OUTPUT);
    Serial.println("MICS-5524 Initialized.");
    digitalWrite(PIN_MICS_5524_EN, LOW);
    return 1;
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
// These notes are irrelavant since we're using the library, but for efficiency's sake we might want to switch to raw I2C eventually
// NOTES: SGP30 must gather in 1s intervals for baseline compensation to work.
// For the first 15s, it will return dummy values
// Data is returned in 2 3-byte sections, where 2 bytes are the data and 1 byte is CRC.
// Byte 1: CO2eq (ppm)
// Byte 2: TVOC (ppb)
bool sensors_SGP30_getData(){
    sgp30.measureAirQuality();
    sensorOutput.tvoc_SGP30 = sgp30.TVOC;
    sensorOutput.co2_SGP30 = sgp30.CO2;
    return 1;
}

//Get SGP41 Data
bool sensors_SGP41_getData(){
    return 1;
}

//Get MICS data
// Just analog reading, probably with some calibration in the future.
bool sensors_MICS_getData(){
    sensorOutput.tvoc_MICS = analogRead(PIN_MICS_5524_A0);
    return 1;
}