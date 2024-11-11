#ifndef BME280_H
#define BME280_H

#include <cstdint>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <iostream>

#define I2C_DEVICE "/dev/i2c-1"
#define BME280_I2C_ADDR 0x76

// BME280 Registers, derived from the sensor's design provided by the manufacturer (Bosch in the
// case of the BME280).
//
// These are provided in the sensor's datasheet.

#define BME280_TEMP_MSB_REG 0xFA
#define BME280_CTRL_MEAS_REG 0xF4
#define BME280_CALIB00_REG 0x88

class Bme280Sensor {
public:
    Bme280Sensor();
    ~Bme280Sensor();
    bool initialize();
    float readTemperature();

private:
    int file;
    int32_t t_fine; // Global variable used in temperature compensation

    uint16_t dig_T1;
    int16_t dig_T2, dig_T3;

    void readCalibrationData();
    int32_t rawReadTemperature();
    float compensateTemperature(int32_t rawTemperatureData);
};

#endif // BME280_H