#ifndef SENSORS_H
#define SENSORS_H

#define PIN_I2C_SDA 21
#define PIN_I2C_SCL 22


#define ADDR_I2C_SGP30
#define ADDR_I2C_SGP41
#define PIN_MICS_5524_A0 34
#define PIN_MICS_5524_EN 27

//AHT20 Temperature/Humidity Sensor I2C codes
#define AHT20_ADDR          0x38
#define AHT20_INIT_COMMAND      0xBE
#define AHT20_INIT_PARAM_1      0x08
#define AHT20_INIT_PARAM_2      0x00
#define AHT20_MEASURE_COMMAND   0xAC
#define AHT20_MEASURE_PARAM_1   0x33
#define AHT20_MEASURE_PARAM_2   0x00
#define AHT20_SOFTRESET_COMMAND 0xBA
#define AHT20_STATUS_COMMAND    0x71
#define AHT20_STATUS_CAL_MASK   0b00001000
#define AHT20_STATUS_BUSY_MASK  0b10000000

bool AHT20_init();

float AHT20_getData();

#endif