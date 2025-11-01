/**
 * @file ThrusterTemperature.h
 * @brief Professional MAX31865 RTD Temperature Sensor Library
 * 
 * Manages multiple MAX31865 sensors for thruster temperature monitoring.
 * Supports simultaneous reading of all sensors or individual queries.
 * 
 * @license MIT
 */

#ifndef THRUSTER_TEMPERATURE_H
#define THRUSTER_TEMPERATURE_H

#include <Arduino.h>
#include <SPI.h>
#include <PwFusion_MAX31865.h>

class ThrusterTemperature {
public:
    /**
     * @brief Initialize temperature sensors
     * @param cs_pins Array of chip select pins
     * @param count Number of sensors
     * @param wire_config RTD wire configuration (2/3/4 wire)
     * @param rtd_type RTD type (PT100/PT1000)
     * @return true if initialization succeeded
     */
    bool begin(const uint8_t* cs_pins, uint8_t count, 
              uint8_t wire_config = 4, 
              uint16_t rtd_type = 100);

    /**
     * @brief Read all sensor temperatures
     * @param temp_array Array to store temperatures (°C)
     * @param fault_array Optional array to store fault status
     * @return Number of successful readings
     */
    uint8_t readAllTemperatures(float* temp_array);

    /**
     * @brief Read specific sensor temperature
     * @param index Sensor index (0 to count-1)
     * @return Temperature in °C, NAN if failed
     */
    float readTemperature(uint8_t index);

    /**
     * @brief Set temperature thresholds for all sensors
     * @param low_temp Lower threshold (°C)
     * @param high_temp Upper threshold (°C)
     */
    void setThresholds(float low_temp, float high_temp);

    /**
     * @brief Get number of initialized sensors
     */
    uint8_t getSensorCount() { return _sensorCount; }

private:
    MAX31865* _sensors;
    uint8_t _sensorCount = 0;
    bool _initialized = false;
};

#endif