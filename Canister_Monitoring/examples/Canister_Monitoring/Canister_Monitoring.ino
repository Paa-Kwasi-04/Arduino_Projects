
#include "Canister_Monitoring.h"


std::vector<uint8_t> sensorPorts = {0, 1, 2, 3, 4, 5, 6};

CanisterMonitoring canisterSensors(sensorPorts);

void setup() {
  Serial.begin(9600);
  while (!Serial);

    if(!canisterSensors.begin()) {
    Serial.println("Sensor init failed!");
    while(1);
  }

}

void loop() {

  // Canister Data
  std::vector<float> temps = canisterSensors.getAllTemperatures();
  std::vector<float> hums = canisterSensors.getAllHumidities();


  // Canister Monitoring Data
  Serial.print("CANISTER_TEMPERATURE:");
  for (size_t i = 0; i < temps.size(); ++i) {
      Serial.print(temps[i]);
      if (i < temps.size() - 1) Serial.print(",");
  }
    Serial.print("|CANISTER_HUMIDITY:");
  for (size_t i = 0; i < hums.size(); ++i) {
      Serial.print(hums[i]);
      if (i < hums.size() - 1) Serial.print(",");
  }

  Serial.println(); // End of frame
  delay(500); // Adjust rate as needed
}