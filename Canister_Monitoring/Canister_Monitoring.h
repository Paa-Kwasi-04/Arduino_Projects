/**
 * @file Canister_Monitoring.h
 * @brief Header file for the ATH10 Sensor Library
 * 
 * This library provides a simplified interface to the ATH10 sensor,
 * offering temperature and humidity readings
 * 
 * @license MIT
 */

#ifndef CANISTER_MONITORING_H
#define CANISTER_MONITORING_H       

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_AHTX0.h"
#include <vector>

class CanisterMonitoring {
public:
    /**
     * @brief Constructor that takes a vector of port numbers to use
     * @param sensorPorts Vector of port numbers where sensors are connected (0-7)
     */
    explicit CanisterMonitoring(const std::vector<uint8_t>& sensorPorts);

    /** 
     * @brief Initializes the sensor system with specified ports
     * @param i2cAddr I2C address of the multiplexer (default 0x70)
     * @param wire Pointer to the Wire object for I2C communication
     * @return true if initialization is successful, false otherwise
     */
    bool begin(uint8_t i2cAddr = 0x70, TwoWire &wire = Wire);

    /**
     * @brief Get sensor readings from a specific sensor
     * @param sensor_index Index of the sensor in the ports array
     * @param temperature Reference to store temperature in degrees Celsius
     * @param humidity Reference to store relative humidity percentage
     * @return true if reading successful, false otherwise
     */
    bool readSensor(uint8_t sensor_index, float &temperature, float &humidity);

    /**
     * @brief Get the number of configured sensors
     * @return Number of sensors
     */
    uint8_t getNumSensors() const { return sensorPorts.size(); }

    /**
     * @brief Get all temperature readings (0 if not present)
     * @return Vector of temperatures for each configured port
     */
    std::vector<float> getAllTemperatures();

    /**
     * @brief Get all humidity readings (0 if not present)
     * @return Vector of humidities for each configured port
     */
    std::vector<float> getAllHumidities();


private:
    std::vector<uint8_t> sensorPorts;         // Array of sensor port numbers
    std::vector<Adafruit_AHTX0> ahtSensors;            
    bool initialized = false;                  // Flag to check if the sensor is initialized

    uint8_t muxAddr = 0x70;                   // I2C address of the multiplexer
    TwoWire* wire = &Wire;                    // Pointer to I2C communication object

    uint8_t currentPort = 0;                  // Currently selected multiplexer port
    std::vector<bool> sensorStatus;           // Track initialization status of each sensor

    /**
     * @brief Helper to write to the multiplexer and select a port
     * @param port The port number to select
     * @return true if successful, false otherwise
     */
    bool selectPort(uint8_t port);
};

#endif
