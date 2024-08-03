#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <ESP32Time.h>
#include <AHT20.h>

#include "sensors.h"
#include "sd.h"

#define SERIAL_BAUD 115200
#define PRINT_DEBUG 0

#define PIN_FAN_HIGH 32
#define PIN_FAN_LOW 33

#define PIN_BTN0 14
#define PIN_BTN1 25

// Time to sleep (in microseconds)
#define uS_TO_S_FACTOR 1000000  // Conversion factor for micro seconds to seconds
#define mS_TO_S_FACTOR 1000
#define TIME_TO_SLEEP  60    // Time ESP32 will go to sleep (6 hours = 21600 seconds)
#define DATA_COLLECTION_INTERVAL 1 * mS_TO_S_FACTOR
#define DATA_COLLECTION_DURATION 120 * mS_TO_S_FACTOR

// RTC_DATA_ATTR attribute makes variable retain its value during deep sleep
RTC_DATA_ATTR int bootCount = 0;

char outLine[50];

Sensor_Data sensorData {0, 0, 0, 0, 0};
uint32_t collectionDurationTimer = 0;
uint32_t collectionIntervalTimer = 0;

void runDataCollection(){
    bootCount++;
    Serial.println("ESP32 just woke up! Boot number: " + String(bootCount));

    Serial.println("Beginning data collection cycle...");
    
    sd_appendFile(SD, "Interval start\n");
    collectionDurationTimer = millis();
    while(millis() - collectionDurationTimer < DATA_COLLECTION_DURATION){
        collectionIntervalTimer = millis();
        //Collect and output data
        digitalWrite(2, HIGH);  //Blink
        sensorData = sensors_getData();
        sprintf(outLine, "%f, %f, %d, %d, %d, %d\n", sensorData.temperature, sensorData.humidity, sensorData.tvoc_MICS, sensorData.tvoc_SGP30, sensorData.co2_SGP30, sensorData.tvoc_SGP41);
        Serial.println(outLine);
        sd_appendFile(SD, outLine, true);
        digitalWrite(2, LOW);
        //Wait for next interval cycle
        while(millis() - collectionIntervalTimer < DATA_COLLECTION_INTERVAL);
    }
    
}

void setup(){
    Wire.begin();
    Serial.begin(SERIAL_BAUD);
    delay(1000); // Give time for serial monitor to connect

    // Print the reason for waking up
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    switch (wakeup_reason) {
        case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup caused by timer"); break;
        default: Serial.println("Wakeup was not caused by deep sleep"); break;
    }
    //Initialize SD reader and sensors
    sensors_init();
    sd_init(true);

    //Set up pins
    pinMode(PIN_FAN_HIGH, OUTPUT);
    pinMode(PIN_FAN_LOW, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(PIN_MICS_5524_A0, INPUT);
    pinMode(PIN_MICS_5524_EN, OUTPUT);

    //Turn on fan
    digitalWrite(PIN_FAN_HIGH, HIGH);
    digitalWrite(PIN_FAN_LOW, LOW);

    //Run data collection routine
    runDataCollection();

    //Turn off fan
    digitalWrite(PIN_FAN_HIGH, HIGH);
    digitalWrite(PIN_FAN_LOW, LOW);

    // Go to deep sleep for 6 hours
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Going to sleep now for 6 hours...");
    delay(1000);
    esp_deep_sleep_start();
}

void loop(){
    Serial.println("How did you get here");
}