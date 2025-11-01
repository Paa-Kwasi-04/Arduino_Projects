/**
 * @file PowerSensor.h
 * @brief Header file for the PowerSensor library
 * 
 * This library provides a simplified interface to multiple INA260 and INA3221 power sensors,
 * offering power, current, and voltage readings.
 * 
 * @license BSD-3-Clause
 */

#ifndef POWER_SENSOR_H
#define POWER_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include "INA260.h"
#include "INA3221.h"

// INA260 sensor setup
#define INA260_COUNT 3
extern INA260 INA260_sensors[INA260_COUNT]; 
extern INA3221 INA3221_sensor;

// PCA mux addresses
#define PCAADDR_260 0x72
#define PCAADDR_3221 0x74

struct SensorReading {
    float power;
    float current;
    float voltage;
};

class PowerSensor {
public:
    /**
     * @brief Initialize the sensors with given addresses
     * @return true if initialization succeeded, false otherwise
     */
    bool begin();

    /**
     * @brief Read all sensor values (power, current, voltage) into an array of SensorReading
     * @param readings Array of SensorReading to fill
     * @param maxCount Maximum number of readings to store
     * @return Number of successful readings
     */
    uint8_t readAll(SensorReading* readings, uint8_t maxCount);

    /**
     * @brief Read INA260 sensor readings into an array of SensorReading
     * @param readings Array of SensorReading structs to fill
     * @param maxCount Maximum number of readings to store
     * @return Number of successful readings
     */
    uint8_t readINA260(SensorReading* readings, uint8_t maxCount);

    /**
     * @brief Read INA3221 sensor readings into an array of SensorReading
     * @param readings Array of SensorReading structs to fill
     * @param maxCount Maximum number of readings to store
     * @return Number of successful readings
     */
    uint8_t readINA3221(SensorReading* readings, uint8_t maxCount);


    /**
     * @brief Get number of initialized INA260 sensors
     * @return INA260 sensor count
     */
    uint8_t getINA260SensorCount() { return _INA260SensorCount; }

    /**
     * @brief Get number of initialized INA3221 sensors
     * @return INA3221 sensor count
     */
    uint8_t getINA3221SensorCount() { return _INA3221SensorCount; }

    /**
     * @brief Get total number of initialized sensors
     * @return Total sensor count
     */
    uint8_t getSensorCount() { return _INA260SensorCount + _INA3221SensorCount; }

    /**
     * @brief Select a specific channel on the PCA multiplexer
     * @param channel Channel number (0-7)
     * @param pcaAddr PCA multiplexer I2C address
     */
    void pcauselect(uint8_t channel, uint8_t pcaAddr );

private:
    uint8_t _INA260SensorCount = 0;
    uint8_t _INA3221SensorCount = 0;
    bool _initialized = false;
};

#endif
