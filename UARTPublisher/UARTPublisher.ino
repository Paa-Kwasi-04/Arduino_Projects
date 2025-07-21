/**
   @file ReconRobotSerialOutput.ino
   @brief Streams all sensor data over Serial (USB) in CSV format
*/

#include "EnvironmentalSensor.h"
#include "LeakSensor.h"
#include "PowerSensor.h"
#include "ThrusterTemperature.h"
#include "ThrusterMonitor.h"
#include "Canister_Monitoring.h"
#include "SystemPower.h"
#include "DcResettableFuse.h"

// ... (Keep your sensor/pin definitions from original code)
// Sensor counts
constexpr uint8_t NUM_THRUSTERS_ = 6;
constexpr uint8_t NUM_THRUSTERS_TEMPS = 8;
constexpr uint8_t NUM_LEAK_SENSORS = 4;
constexpr uint8_t MAX_NUM_POWER_SENSORS = 28;
constexpr uint8_t NUM_CANISTER_SENSORS = 4;
#define NUM_REGISTERS   3 // Example: 1 shift register = 8 fuses

// Hardware pins
const uint8_t leakSensorPins[NUM_LEAK_SENSORS] = {28, 29, 30, 31};
const uint8_t thrusterTempPins[NUM_THRUSTERS_TEMPS] = {0, 1, 2, 3, 4, 5, 9, 10};
const uint8_t thrusterSpeedPins[NUM_THRUSTERS] = {A0, A2, A6, A8, A10, A16};
// Which multiplexer ports have sensors connected to(0-7)
uint8_t sensorPorts[NUM_CANISTER_SENSORS] = {4, 5, 6, 7};

// Sensor instances
EnvironmentalSensor envSensor;
LeakSensor leakSystem;
PowerSensor powerSensor;
ThrusterTemperature thrusterTempSensors;
ThrusterMonitor thrusterMonitor;
CanisterMonitoring canisterSensors(sensorPorts, NUM_CANISTER_SENSORS);
DcResettableFuse fuse;

// Variables to hold sensor data
float temp, pressure, humidity;
bool leaks[NUM_LEAK_SENSORS];
SensorReading powerSensorReadings[MAX_NUM_POWER_SENSORS];
float thrusterTemps[NUM_THRUSTERS_TEMPS];
float thrusterControllerTemps[NUM_THRUSTERS_];
float thrusterSpeeds[NUM_THRUSTERS_];
float canister_temp[NUM_CANISTER_SENSORS];
float canister_humidity[NUM_CANISTER_SENSORS];
uint8_t NUM_POWER_SENSORS;
SystemPower systemPowerMonitor;
bool fuseStates[MAX_FUSES];  // Boolean array for fuse states
uint8_t numFuses;  // Number of fuses read

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);

  // Initialize sensors (same as before)
  thrusterMonitor.begin();
  systemPowerMonitor.begin();
  
  if (!envSensor.begin() ||
      !leakSystem.begin(leakSensorPins, NUM_LEAK_SENSORS) ||
      !powerSensor.begin() ||
      !thrusterTempSensors.begin(thrusterTempPins, NUM_THRUSTERS_TEMPS) ||
      !canisterSensors.begin() ||
      !fuse.begin(NUM_REGISTERS)) {
    Serial.println("Sensor init failed!");
    while (1);
  }

  thrusterTempSensors.setThresholds(30.0, 70.0);
}

void loop() {
  // Environmental Data
  temp = envSensor.readTemperature();
  pressure = envSensor.readPressureBar();
  humidity = envSensor.readHumidity();

  // Leak Sensors
  leakSystem.readAll(leaks);

  // Power Data
  NUM_POWER_SENSORS = powerSensor.readAll(powerSensorReadings, MAX_NUM_POWER_SENSORS);

  // Thruster Data
  thrusterTempSensors.readAllTemperatures(thrusterTemps);
  thrusterMonitor.updateAll();

  // Canister Data
  canisterSensors.getAllTemperatures(canister_temp, NUM_CANISTER_SENSORS);
  canisterSensors.getAllHumidities(canister_humidity, NUM_CANISTER_SENSORS);

  //DC Resettable Fuse
  numFuses = fuse.readAllStates(fuseStates);

  // CSV Format:
  // ENV:temp,pressure,humidity|LEAK:0,1,0,0|POWER:p1,p2,p3,p4|c1,c2,c3,c4|v1,v2,v3,v4|THRUSTER_TEMP:t1,t2,t3,t4,t5,t6,t7,t8|THRUSTER_CONTROLLER_TEMP:t1,t2,t3,t4,t5,t6|THRUSTER_SPEED:s1,s2,s3,s4,s5,s6|CANISTER_MONITORING:t0,t1,t2,t3,t4,t5,t6|CANISTER_HUMIDITY:h0,h1,h2,h3,h4,h5,h6
  Serial.print("ENV:");
  Serial.print(temp); Serial.print(",");
  Serial.print(pressure); Serial.print(",");
  Serial.print(humidity);

  Serial.print("|LEAK:");
  for (int i = 0; i < NUM_LEAK_SENSORS; i++) {
    Serial.print(leaks[i] ? "1" : "0");
    if (i < NUM_LEAK_SENSORS - 1) Serial.print(",");
  }

  Serial.print("|POWER:");
  for (uint8_t i = 0; i < NUM_POWER_SENSORS; i++) {
    Serial.print(powerSensorReadings[i]._power);
    if (i < NUM_POWER_SENSORS - 1) Serial.print(",");
  }

  Serial.print("|CURRENT:");
  for (uint8_t i = 0; i < NUM_POWER_SENSORS; i++) {
    Serial.print(powerSensorReadings[i]._current);
    if (i < NUM_POWER_SENSORS - 1) Serial.print(",");
  }

  Serial.print("|VOLTAGE:");
  for (uint8_t i = 0; i < NUM_POWER_SENSORS; i++) {
    Serial.print(powerSensorReadings[i]._voltage);
    if (i < NUM_POWER_SENSORS - 1) Serial.print(",");
  }

  Serial.print("|THRUSTER_TEMP:");
  for (int i = 0; i < NUM_THRUSTERS_TEMPS; i++) {
    Serial.print(thrusterTemps[i]);
    if (i < NUM_THRUSTERS_TEMPS - 1) Serial.print(",");
  }

  Serial.print("|THRUSTER_CONTROLLER_TEMP:");
  for (int i = 0; i < NUM_THRUSTERS_; i++) {
    Serial.print(thrusterMonitor.getTemperature(i + 1));  //gets normalized temperature
    if (i < NUM_THRUSTERS_ - 1) Serial.print(",");
  }

  Serial.print("|THRUSTER_SPEED:");
  for (int i = 0; i < NUM_THRUSTERS_; i++) {
    Serial.print(thrusterMonitor.getSpeed(i + 1)); // Add 1 to display Thruster 1-6
    if (i < NUM_THRUSTERS_ - 1) Serial.print(",");
  }

  // Canister Monitoring Data
  Serial.print("|CANISTER_TEMPERATURE:");
  for (size_t i = 0; i < NUM_CANISTER_SENSORS; ++i) {
    Serial.print(canister_temp[i]);
    if (i < NUM_CANISTER_SENSORS - 1) Serial.print(",");
  }
  Serial.print("|CANISTER_HUMIDITY:");
  for (size_t i = 0; i < NUM_CANISTER_SENSORS; ++i) {
    Serial.print(canister_humidity[i]);
    if (i < NUM_CANISTER_SENSORS - 1) Serial.print(",");
  }
  Serial.print("|SYSTEM_VOLTAGE:"); Serial.print(systemPowerMonitor.voltage());

  Serial.print("|SYSTEM_CURRENT:"); Serial.print(systemPowerMonitor.current());

  Serial.print("|SYSTEM_POWER:"); Serial.print(systemPowerMonitor.power());

  Serial.print("|SYSTEM_ENERGY:"); Serial.print(systemPowerMonitor.energy());

  Serial.print("|SYSTEM_FREQUENCY:"); Serial.print(systemPowerMonitor.frequency());

  Serial.print("|SYSTEM_POWER_FACTOR:"); Serial.print(systemPowerMonitor.powerFactor());

  Serial.print("|DC_RESETTABLE_FUSE:");
  for (uint8_t i = 0; i < numFuses; ++i) {
    Serial.print(fuseStates[i]);
    if (i < numFuses - 1) Serial.print(",");
  }

  Serial.println(); // End of frame
  delay(500); // Adjust rate as needed
}
