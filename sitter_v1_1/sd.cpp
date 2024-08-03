#include <SD.h>
#include <HardwareSerial.h>
#include <ESP32Time.h>
#include <SPI.h>
#include "sd.h"

char fileName[50];
//Initialize SD card, return 0 if failed
bool sd_init(bool printDebug){
  if(!SD.begin()){
    if(printDebug) Serial.println("Card Mount Failed");
    return 0;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    if(printDebug) Serial.println("No SD card attached");
    return 0;
  }
  
  sprintf(fileName, "/sensor_data_%d.txt", 1);
  sd_appendFile(SD, fileName, "Start of sensor data:\n");
  sd_appendFile(SD, fileName, "Temp, Humidity, MICS, SGP30(TVOC), SGP30(CO2), SGP41\n");

  return 1;
}

//Append to file. Usage: appendFile(SD, "/hello.csv", "Hello, world!\n");
//Return 0 if failed
bool sd_appendFile(fs::FS &fs, const char * message, bool printDebug){
  if(printDebug) Serial.printf("Appending to file: %s\n", fileName);

  File file = fs.open(fileName, FILE_APPEND);
  if(!file){
    if(printDebug) Serial.println("Failed to open file for appending");
    return 0;
  }
  if(file.print(message)){
    if(printDebug) Serial.println("Message appended");
    file.close();
    return 1;
  } else {
    if(printDebug) Serial.println("Append failed");
    file.close();
    return 0;
  }
}
