#include <Wire.h>
#include "INA3221.h"
INA3221 INA(0x40);


#define PCAADDR 0x74


void pcauselect(uint8_t i) {
    if (i > 7) return;

    Wire.beginTransmission(PCAADDR);
    Wire.write(1 << i);  // Select channel i
    Wire.endTransmission();
}

void setup() {
    Serial.begin(115200);
    pinMode(12,OUTPUT);
    pinMode(24,OUTPUT);
  
    while (!Serial) delay(10);
  
    Serial.println("\nQwiic Mux + INA3221 Scan & Read Example");
  
    Wire.begin();

    for (uint8_t t = 0; t < 8; t++) {
        pcauselect(t);
        Serial.print("Scanning PCA Port #");
        Serial.println(t);

        for (uint8_t addr = 1; addr < 127; addr++) {
            if (addr == PCAADDR) continue; // Skip mux itself

            Wire.beginTransmission(addr);
            if (!Wire.endTransmission()) {
                Serial.print("Found I2C device at 0x");
                Serial.println(addr, HEX);
            }
        }
        
    }    Serial.println("\nScan complete.\n");


  
     if(!INA.begin() ){
          Serial.println("could not connect. Fix and Reboot");
     }else{
          Serial.print("Found: \t");
          Serial.println(INA.getAddress());
      }
      INA.setShuntR(0, 0.100);
      INA.setShuntR(1, 0.102);
      INA.setShuntR(2, 0.099);
      

  
}

void loop() {
    digitalWrite(12,HIGH);
    digitalWrite(24,HIGH);

  
    // Iterate over mux channels
    for (int j = 0; j < 6; j++) {
        pcauselect(j);
        Serial.print("\nChannel: ");
        Serial.println(j);
        Serial.println("\nCHAN\tBUS\tCURRENT\tPOWER");
          for (int ch = 0; ch < 3; ch++){
            Serial.print(ch);
            Serial.print("\t");
            Serial.print(INA.getBusVoltage(ch), 3);
            Serial.print("\t");
            Serial.print(INA.getCurrent(ch), 3);
            Serial.print("\t");
            Serial.print(INA.getPower(ch), 3);
            Serial.println();
            delay(1000);
          }  
   }     
}
