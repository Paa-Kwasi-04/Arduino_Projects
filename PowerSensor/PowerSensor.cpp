#include "PowerSensor.h"

// ================= Constants for Configuration ===================

// PCA9548 multiplexer supports 8 channels (0 to 7)
const uint8_t MAX_PCA_CHANNELS = 8;

// I2C addresses range from 1 to 126
const uint8_t MIN_I2C_ADDRESS = 1;
const uint8_t MAX_I2C_ADDRESS = 126;

// Each INA3221 sensor has 3 separate sensor channels
const uint8_t INA3221_CHANNEL_COUNT = 3;

// =================================================================

// Initialize the INA260 sensors with their I2C addresses
INA260 INA260_sensors[INA260_COUNT] = {
    INA260(0x40),
    INA260(0x44),
    INA260(0x45)
};

// Initialize the single INA3221 sensor (default I2C address 0x40)
INA3221 INA3221_sensor(0x40);


void PowerSensor::pcauselect(uint8_t channel, uint8_t pcaAddr) {
    if (channel >= MAX_PCA_CHANNELS) return;
    Wire.beginTransmission(pcaAddr);
    Wire.write(1 << channel);  // Set the bit to select the channel
    Wire.endTransmission();
}


bool PowerSensor::begin() {
    _INA260SensorCount = 0;
    _INA3221SensorCount = 0;

    // -------- Scan for INA260 sensors at known addresses --------
    const uint8_t INA260_ADDRESSES[] = {0x40, 0x44, 0x45};
    const uint8_t INA260_ADDRESS_COUNT = sizeof(INA260_ADDRESSES) / sizeof(INA260_ADDRESSES[0]);

    for (uint8_t channel = 0; channel < MAX_PCA_CHANNELS; channel++) {
        pcauselect(channel, PCAADDR_260);  // Select the PCA channel

        for (uint8_t i = 0; i < INA260_ADDRESS_COUNT; i++) {
            uint8_t addr = INA260_ADDRESSES[i];
            Wire.beginTransmission(addr);
            if (!Wire.endTransmission()) {
                _INA260SensorCount++;  // Count if the sensor responds
            }
        }
    }

    // -------- Scan for INA3221 sensors at known address (e.g., 0x40) --------
    const uint8_t INA3221_ADDRESS = 0x40;

    for (uint8_t channel = 0; channel < MAX_PCA_CHANNELS; channel++) {
        pcauselect(channel, PCAADDR_3221);

        Wire.beginTransmission(INA3221_ADDRESS);
        if (!Wire.endTransmission()) {
            _INA3221SensorCount += 3;  // INA3221 has 3 channels, count all
        }
    }

    _initialized = true;
    return _initialized;
}



uint8_t PowerSensor::readINA3221(SensorReading* readings, uint8_t maxCount) {
    if (!_initialized || readings == nullptr) return 0;

    uint8_t totalReads = 0;

    for (uint8_t muxChannel = 0; muxChannel < getINA3221SensorCount() / INA3221_CHANNEL_COUNT && totalReads < maxCount; muxChannel++) {
        pcauselect(muxChannel, PCAADDR_3221);  // Select PCA channel

        for (uint8_t subChannel = 0; subChannel < INA3221_CHANNEL_COUNT && totalReads < maxCount; subChannel++) {
            SensorReading reading;
            reading.power = INA3221_sensor.getPower(subChannel);
            reading.current = INA3221_sensor.getCurrent(subChannel);
            reading.voltage = (INA3221_sensor.getBusVoltage_mV(subChannel) + INA3221_sensor.getShuntVoltage_mV(subChannel)) / 1000.0f;

            if (!isnan(reading.power) && !isnan(reading.current) && !isnan(reading.voltage)) {
                readings[totalReads++] = reading;
            } else {
                totalReads++;  // Reserve space even if invalid (optional)
            }
        }
    }

    return totalReads;
}


uint8_t PowerSensor::readINA260(SensorReading* readings, uint8_t maxCount) {
    if (!_initialized || readings == nullptr) return 0;

    uint8_t totalReads = 0;

    for (uint8_t muxChannel = 0; muxChannel < MAX_PCA_CHANNELS && totalReads < maxCount; muxChannel++) {
        pcauselect(muxChannel, PCAADDR_260);

        if (muxChannel == 3) {
            // On channel 3, read all INA260 sensors (addresses 0x40, 0x44, 0x45)
            for (uint8_t sensorIdx = 0; sensorIdx < INA260_COUNT && totalReads < maxCount; sensorIdx++) {
                SensorReading reading;
                reading.voltage = (INA260_sensors[sensorIdx].getBusVoltage_mV() + INA260_sensors[sensorIdx].getShuntVoltage_mV()) / 1000.0f;
                reading.current = INA260_sensors[sensorIdx].getCurrent();
                reading.power = INA260_sensors[sensorIdx].getPower();

                if (!isnan(reading.power) && !isnan(reading.current) && !isnan(reading.voltage)) {
                    readings[totalReads++] = reading;
                }
            }
        }
        else if (muxChannel == 0 || (muxChannel > 4 && muxChannel < 8) || muxChannel == 2) {
            // On channels 0, 2, and 5-7, read from INA260_sensors[1] (address 0x44)
            SensorReading reading;
            reading.voltage = (INA260_sensors[1].getBusVoltage_mV() + INA260_sensors[1].getShuntVoltage_mV()) / 1000.0f;
            reading.current = INA260_sensors[1].getCurrent();
            reading.power = INA260_sensors[1].getPower();

            if (!isnan(reading.power) && !isnan(reading.current) && !isnan(reading.voltage)) {
                readings[totalReads++] = reading;
            }
        }
        else {
            // Other channels: read from INA260_sensors[0] (address 0x40)
            SensorReading reading;
            reading.voltage = (INA260_sensors[0].getBusVoltage_mV() + INA260_sensors[0].getShuntVoltage_mV()) / 1000.0f;
            reading.current = INA260_sensors[0].getCurrent();
            reading.power = INA260_sensors[0].getPower();

            if (!isnan(reading.power) && !isnan(reading.current) && !isnan(reading.voltage)) {
                readings[totalReads++] = reading;
            }
        }
    }

    return totalReads;
}


uint8_t PowerSensor::readAll(SensorReading* readings, uint8_t maxCount) {
    if (!_initialized || readings == nullptr) return 0;

    uint8_t totalReads = 0;

    // Read INA260 readings first
    totalReads += readINA260(readings, maxCount);

    // If space remains, read INA3221 sensors
    if (totalReads < maxCount) {
        totalReads += readINA3221(&readings[totalReads], maxCount - totalReads);
    }

    return totalReads;
}
