/**
 * @file Main.ino
 * @brief Thruster Temperature Monitoring Example
 */

#include "ThrusterTemperature.h"

// CS pins for 8 thrusters (0,1,2,3,4,5,9,10)
const uint8_t cs_pins[] = {0, 1, 2, 3, 4, 5, 9, 10};
const uint8_t sensorCount = sizeof(cs_pins)/sizeof(cs_pins[0]);

ThrusterTemperature tempSensors;

void setup() {
    Serial.begin(9600);
    while (!Serial);  // Wait for serial console

    if (!tempSensors.begin(cs_pins, sensorCount)) {
        Serial.println(F("Sensor initialization failed!"));
        while (1);
    }

    // Set safety thresholds (30°C to 70°C)
    tempSensors.setThresholds(30.0, 70.0);
    
    Serial.println(F("Thruster Temperature System Ready"));
    Serial.println(F("-------------------------------"));
}

void loop() {
    // Method 1: Read all sensors at once
    float temperatures[sensorCount];
    
    tempSensors.readAllTemperatures(temperatures);

    for (uint8_t i = 0; i < sensorCount; i++) {
        Serial.print(F("Thruster ")); Serial.print(i); 
        Serial.print(F(": ")); Serial.print(temperatures[i], 1);
        Serial.println(F("°C"));
    }

    // Method 2: Read individual sensor
    // float temp = tempSensors.readTemperature(2);
    // Serial.print(F("Thruster 2: ")); Serial.print(temp); Serial.println(F("°C"));
    
    Serial.println(F("-------------------------------"));
    delay(500);
}