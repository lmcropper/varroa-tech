#ifndef SD_H
#define SD_H

#include "FS.h"
#include <SD.h>

#define PIN_SPI_CS 2
#define PIN_SPI_CLK 18
#define PIN_SPI_MISO 19
#define PIN_SPI_MOSI 23

//Initialize SD card, return 0 if failed
bool sd_init(bool printDebug = false);

//Append to file. Usage: appendFile(SD, "/hello.csv", "Hello, world!\n");
//Return 0 if failed
bool sd_appendFile(fs::FS &fs, const char * message, bool printDebug = false);

#endif