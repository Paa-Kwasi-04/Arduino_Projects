#include "Wire.h"
#include "INA260.h"
#include "INA3221.h"

// LED pins for status indication
#define LEDpinINA3221 24
#define LEDpinINA260 12

// INA260 sensor setup
#define INA260_COUNT 3
INA260 INA260_sensors[INA260_COUNT] = {
    INA260(0x40),
    INA260(0x44),
    INA260(0x45)
};

// INA3221 sensor setup
INA3221 INA3221_sensor(0x40);

// PCA mux addresses
#define PCAADDR_260 0x72
#define PCAADDR_3221 0x74

void displayChannel(int k){
    Serial.print("\nChannel: ");
    Serial.println(k);
    Serial.println("VOLTAGE\tCURRENT\tPOWER");
}


// Function to select a channel on a given PCA mux
void pcauselect(uint8_t channel, uint8_t pcaAddr) {
    if (channel > 7) return;
    Wire.beginTransmission(pcaAddr);
    Wire.write(1 << channel);
    Wire.endTransmission();
}

void setup() {
    Serial.begin(115200);
    Wire.begin();
    pinMode(LEDpinINA3221, OUTPUT);
    pinMode(LEDpinINA260, OUTPUT);
    delay(1000);

    int NumSensors = 0;
//
//    Serial.println("I2C Scan Start:\n");
//
//    // Scan for INA260 on mux 0x72
//    Serial.println("Scanning Mux 0x72 for INA260 sensors:");
//    for (uint8_t channel = 0; channel < 8; channel++) {
//        pcauselect(channel, PCAADDR_260);
//        Serial.print("PCA72 Channel "); Serial.println(channel);
//        for (uint8_t addr = 1; addr < 127; addr++) {
//            if (addr == PCAADDR_260) continue;
//            Wire.beginTransmission(addr);
//            if (!Wire.endTransmission()) {
//                Serial.print("Found I2C device at 0x");
//                Serial.println(addr, HEX);
//            }
//        }
//    }
//
//    // Scan for INA3221 on mux 0x74
//    Serial.println("\nScanning Mux 0x74 for INA3221 sensors:");
//    for (uint8_t channel = 0; channel < 8; channel++) {
//        pcauselect(channel, PCAADDR_3221);
//        Serial.print("PCA74 Channel "); Serial.println(channel);
//        for (uint8_t addr = 1; addr < 127; addr++) {
//            if (addr == PCAADDR_3221) continue;
//            Wire.beginTransmission(addr);
//            if (!Wire.endTransmission()) {
//                Serial.print("Found I2C device at 0x");
//                Serial.println(addr, HEX);
//            }
//        }
//    }
//    Serial.println("\nScan complete.\n");
//
}


void loop() {
    int k = 1,l = 1;
    digitalWrite(LEDpinINA260, HIGH);
    digitalWrite(LEDpinINA3221, HIGH);

    // --- Read from mux 0x72 (INA260) ---
    Serial.println();Serial.println();Serial.println();
    Serial.println("10 CHANNEL HIGH CURRENT SENSOR");
    for (int j = 0; j < 8; j++) {
        pcauselect(j,PCAADDR_260);

        if (j == 3) {
            for (int ID = 0; ID < INA260_COUNT; ID++) {
                displayChannel(k);
                Serial.print(INA260_sensors[ID].getBusVoltage(), 3);
                Serial.print("\t");
                Serial.print(INA260_sensors[ID].getCurrent(), 3);
                Serial.print("\t");
                Serial.print(INA260_sensors[ID].getPower(), 3);
                k++;
                Serial.println();
                delay(1000);
            }
        }
        else if(j == 0|| (j<8 && j>4) || j== 2){
            // On other channels, only read INA[0]
            displayChannel(k);
            Serial.print(INA260_sensors[1].getBusVoltage(), 3);
            Serial.print("\t");
            Serial.print(INA260_sensors[1].getCurrent(), 3);
            Serial.print("\t");
            Serial.print(INA260_sensors[1].getPower(), 3);
            k++;
            Serial.println();
            delay(1000);
        }
        else {
            // On other channels, only read INA[0]
            displayChannel(k);
            Serial.print(INA260_sensors[0].getBusVoltage(), 3);
            Serial.print("\t");
            Serial.print(INA260_sensors[0].getCurrent(), 3);
            Serial.print("\t");
            Serial.print(INA260_sensors[0].getPower(), 3);
            k++;
            Serial.println();
            delay(1000);
        }
        
    }

    // --- Read from mux 0x74 (INA3221) ---
    Serial.println();Serial.println();Serial.println();
    Serial.println("18 CHANNEL LOW CURRENT SENSOR");
    for (int j = 0; j < 6; j++) {
        pcauselect(j,PCAADDR_3221);

          for (int ch = 0; ch < 3; ch++){
            displayChannel(k);
            Serial.print(INA3221_sensor.getBusVoltage(ch), 3);
            Serial.print("\t");
            Serial.print(INA3221_sensor.getCurrent(ch), 3);
            Serial.print("\t");
            Serial.print(INA3221_sensor.getPower(ch), 3);
            k++;
            Serial.println();
            delay(1000);
          }  
   } 

    delay(1000);  // Short pause before repeating
}
