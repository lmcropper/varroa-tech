#ifndef SENSORS_H
#define SENSORS_H

#define PIN_I2C_SDA 21
#define PIN_I2C_SCL 22


#define ADDR_I2C_SGP30
#define ADDR_I2C_SGP41
#define PIN_MICS_5524_A0 34
#define PIN_MICS_5524_EN 27

//AHT20 Temperature/Humidity Sensor I2C codes (NOT USING, USING LIBRARY)
// #define AHT20_ADDR              0x38
// #define AHT20_INIT_COMMAND      0xBE
// #define AHT20_INIT_PARAM_1      0x08
// #define AHT20_INIT_PARAM_2      0x00
// #define AHT20_MEASURE_COMMAND   0xAC
// #define AHT20_MEASURE_PARAM_1   0x33
// #define AHT20_MEASURE_PARAM_2   0x00
// #define AHT20_SOFTRESET_COMMAND 0xBA
// #define AHT20_STATUS_COMMAND    0x71
// #define AHT20_STATUS_CAL_MASK   0b00001000
// #define AHT20_STATUS_BUSY_MASK  0b10000000

//SGP30 VOC sensor I2C codes (NOT USING, USING LIBRARY)
// #define SGP30_ADDR                  0x58
// #define SGP30_COMMAND_INIT          0x2003
// #define SGP30_COMMAND_MEASURE       0x2008
// #define SGP30_COMMAND_GET_BASELINE  0x2015
// #define SGP30_COMMAND_SET_BASELINE  0x201E
// #define SGP30_COMMAND_SET_HUMIDITY  0x2061
// #define SGP30_COMMAND_MEASURE_TEST  0x2032
// #define SGP30_COMMAND_GET_FEATURE   0x202F
// #define SGP30_COMMAND_MEASURE_RAW   0x2050

struct Sensor_Data{
    double temperature;
    double humidity;
    int voc_MICS;
    int voc_SGP31;
    int voc_SGP40;
};

bool sensors_init();

Sensor_Data sensors_getData();

bool sensors_AHT20_init();

bool sensors_SGP30_init();

bool sensors_SGP41_init();

bool sensors_AHT20_getData();

bool sensors_SGP30_getData();

bool sensors_SGP41_getData();

bool sensors_MICS_getData();

#endif