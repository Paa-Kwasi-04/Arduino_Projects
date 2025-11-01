/**
 * @file ThrusterTemperature.cpp
 * @brief Implementation of MAX31865 temperature monitoring
 * 
 * @license MIT
 */

#include "ThrusterTemperature.h"

bool ThrusterTemperature::begin(const uint8_t* cs_pins, uint8_t count, 
                              uint8_t wire_config, uint16_t rtd_type) {
    if (count == 0 || cs_pins == nullptr) return false;

    SPI.begin();
    _sensors = new MAX31865[count];
    _sensorCount = count;

    for (uint8_t i = 0; i < count; i++) {
        pinMode(cs_pins[i], OUTPUT);
        _sensors[i].begin(cs_pins[i]);
    }

    _initialized = true;
    return true;
}

uint8_t ThrusterTemperature::readAllTemperatures(float* temp_array) {
    if (!_initialized || temp_array == nullptr) return 0;

    uint8_t successCount = 0;
    for (uint8_t i = 0; i < _sensorCount; i++) {
        _sensors[i].sample();
        temp_array[i] = _sensors[i].getTemperature();
        if (!isnan(temp_array[i])) successCount++;
    }
    return successCount;
}

float ThrusterTemperature::readTemperature(uint8_t index) {
    if (!_initialized || index >= _sensorCount) return NAN;
    _sensors[index].sample();
    return _sensors[index].getTemperature();
}

void ThrusterTemperature::setThresholds(float low_temp, float high_temp) {
    if (!_initialized) return;
    
    for (uint8_t i = 0; i < _sensorCount; i++) {
        _sensors[i].setLowFaultTemperature(low_temp);
        _sensors[i].setHighFaultTemperature(high_temp);
    }
}