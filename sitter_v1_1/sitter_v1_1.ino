
#include <SPI.h>
#include <Wire.h>
#include <ESP32Time.h>
#include <AHT20.h>

#include "sensors.h"
#include "sd_reader.h"

#define SERIAL_BAUD 115200
#define PRINT_DEBUG 0

#define PIN_FAN_HIGH 32
#define PIN_FAN_LOW 33

#define PIN_BTN0 14
#define PIN_BTN1 25

char outLine[50];

void setup(){
    Wire.begin();
    Serial.begin(SERIAL_BAUD);
    AHT20_init();
    sdInit();
    pinMode(PIN_FAN_HIGH, OUTPUT);
    pinMode(PIN_FAN_LOW, OUTPUT);
}

void loop(){
    AHT20_getData();
    digitalWrite(PIN_FAN_HIGH, HIGH);
    digitalWrite(PIN_FAN_LOW, LOW);
    delay(1000);


}