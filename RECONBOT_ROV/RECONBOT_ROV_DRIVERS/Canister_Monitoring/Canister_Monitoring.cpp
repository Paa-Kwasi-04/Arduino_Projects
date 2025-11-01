
#include "Canister_Monitoring.h"





CanisterMonitoring::CanisterMonitoring(const std::vector<uint8_t>& ports) {
    // Filter out invalid ports (>7) and store valid ones
    for (uint8_t port : ports) {
        if (port <= 7) {
            sensorPorts.push_back(port);
        }
    }

    // Ensure at least one valid port
    if (sensorPorts.empty()) {
        sensorPorts.push_back(0);
    }

    sensorStatus.resize(sensorPorts.size(), false);
    ahtSensors.resize(sensorPorts.size()); // One sensor instance per port
}

bool CanisterMonitoring::begin(uint8_t i2cAddr, TwoWire &wire) {
    this->muxAddr = i2cAddr;
    this->wire = &wire;

    // Initialize the multiplexer
    wire.begin();

    // Initialize each sensor on specified ports
    for (size_t i = 0; i < sensorPorts.size(); ++i) {
        if (!selectPort(sensorPorts[i])) {
            sensorStatus[i] = false;
            continue;
        }

        if (!ahtSensors[i].begin()) {
            sensorStatus[i] = false;
            continue;
        }
        sensorStatus[i] = true; // Mark sensor as initialized
    }

    initialized = true;
    return std::any_of(sensorStatus.begin(), sensorStatus.end(), [](bool s){ return s; });
}


bool CanisterMonitoring::readSensor(uint8_t port, float &temperature, float &humidity) {
    // Check if port is valid (0-7)
    if (port > 7 || !initialized) {
        temperature = 0;
        humidity = 0;
        return false;
    }

    // Find if this port is in sensorPorts and get its index
    auto it = std::find(sensorPorts.begin(), sensorPorts.end(), port);
    if (it == sensorPorts.end()) {
        // No sensor configured for this port
        temperature = 0;
        humidity = 0;
        return false;
    }
    size_t sensor_index = std::distance(sensorPorts.begin(), it);

    if (!sensorStatus[sensor_index]) {
        temperature = 0;
        humidity = 0;
        return false;
    }

    // Select the appropriate port for the sensor
    if (!selectPort(port)) {
        temperature = 0;
        humidity = 0;
        return false;
    }

    // Read temperature and humidity from the sensor
    sensors_event_t humidityEvent, tempEvent;
    ahtSensors[sensor_index].getEvent(&humidityEvent, &tempEvent);

    temperature = tempEvent.temperature;
    humidity = humidityEvent.relative_humidity;

    return true;
}


bool CanisterMonitoring::selectPort(uint8_t port) {
    if (port > 7) {  // Valid ports are 0-7
        return false;
    }

    wire->beginTransmission(muxAddr);
    wire->write(1 << port);
    return (wire->endTransmission() == 0);
}
std::vector<float> CanisterMonitoring::getAllTemperatures() {
    std::vector<float> temps(sensorPorts.size(), 0.0f);
    for (size_t i = 0; i < sensorPorts.size(); ++i) {
        float t = 0, h = 0;
        if (readSensor(sensorPorts[i], t, h)) {
            temps[i] = t;
        }
        // else leave as 0
    }
    return temps;
}

std::vector<float> CanisterMonitoring::getAllHumidities() {
    std::vector<float> hums(sensorPorts.size(), 0.0f);
    for (size_t i = 0; i < sensorPorts.size(); ++i) {
        float t = 0, h = 0;
        if (readSensor(sensorPorts[i], t, h)) {
            hums[i] = h;
        }
        // else leave as 0
    }
    return hums;
}
