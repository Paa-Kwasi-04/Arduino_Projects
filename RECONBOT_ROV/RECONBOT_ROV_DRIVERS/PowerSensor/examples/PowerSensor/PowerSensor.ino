/**
 * @file PowerSensor.ino
 * @brief Example usage of PowerSensor library with multiple INA260 and INA3221 sensors
 */

#include "PowerSensor.h"
#define MAX_SENSOR_COUNT 28 // Adjust based on your setup

PowerSensor powerSensor;
SensorReading readings[MAX_SENSOR_COUNT]; // Adjust size as needed

void setup() {
    Wire.begin();
    pinMode(12, OUTPUT);
    pinMode(24,OUTPUT); 
    digitalWrite(12, HIGH);
    digitalWrite(24, HIGH); 
    Serial.begin(9600);
    while (!Serial);  // Wait for serial monitor

    if (!powerSensor.begin()) {
        Serial.println("Failed to initialize power sensors!");
        while (1);  // Halt if initialization fails
    }

    Serial.println("Power Sensors Ready");
    Serial.println("-------------------");
    Serial.print("INA260 Sensor Count: "); Serial.println(powerSensor.getINA260SensorCount());
    Serial.print("INA3221 Sensor Count: "); Serial.println(powerSensor.getINA3221SensorCount());

}

void loop() {
    uint8_t count = powerSensor.readAll(readings, MAX_SENSOR_COUNT);
    Serial.println(" ");
    for (uint8_t i = 0; i < count; i++) {
        Serial.println(" ");
        Serial.print("Sensor "); Serial.print(i + 1); Serial.println(":");
        Serial.print("  Power: "); Serial.print(readings[i].power); Serial.println(" W");
        Serial.print("  Current: "); Serial.print(readings[i].current); Serial.println(" A");
        Serial.print("  Voltage: "); Serial.print(readings[i].voltage); Serial.println(" V");
    }
    Serial.println(" ");
    delay(1000);
}