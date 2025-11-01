#include "Wire.h"
#include "INA260.h"

#define LEDpin 24
#define INA_COUNT  3
#define PCAADDR 0x72

INA260 INA[INA_COUNT] = {
    INA260(0x40),
    INA260(0x44),
    INA260(0x45)
};


void displayChannel(int k){
    Serial.print("\nChannel: ");
    Serial.println(k);
    Serial.println("VOLTAGE\tCURRENT\tPOWER");
}


// Function to select a channel on the PCA9548 mux
void pcauselect(uint8_t i) {
    if (i > 7) return;

    Wire.beginTransmission(PCAADDR);
    Wire.write(1 << i);  // Select channel i
    Wire.endTransmission();
}

void setup() {
    Serial.begin(9600);
    pinMode(LEDpin, OUTPUT);
    pinMode(12,OUTPUT);
    Wire.begin();

    delay(1000);

}    

void loop() {
    int k = 1;
    digitalWrite(LEDpin, HIGH);
    digitalWrite(12,HIGH);

    // Iterate over mux channels
    Serial.println();
    Serial.println("10 CHANNEL HIGH CURRENT SENSOR");
    for (int j = 0; j < 8; j++) {
        pcauselect(j);

        if (j == 3) {
            // If on channel 2, read all INA260 sensors
            for (int ID = 0; ID < INA_COUNT; ID++) {
                displayChannel(k);
                Serial.print(INA[ID].getBusVoltage(), 3);
                Serial.print("\t");
                Serial.print(INA[ID].getCurrent(), 3);
                Serial.print("\t");
                Serial.print(INA[ID].getPower(), 3);
                k++;
                Serial.println();
                delay(1000);
            }
        }
        else if(j == 0|| (j<8 && j>4) || j== 2){
            // On other channels, only read INA[0]
            displayChannel(k);
            Serial.print(INA[1].getBusVoltage(), 3);
            Serial.print("\t");
            Serial.print(INA[1].getCurrent(), 3);
            Serial.print("\t");
            Serial.print(INA[1].getPower(), 3);
            k++;
            Serial.println();
            delay(1000);
        }
        else {
            // On other channels, only read INA[0]
            displayChannel(k);
            Serial.print(INA[0].getBusVoltage(), 3);
            Serial.print("\t");
            Serial.print(INA[0].getCurrent(), 3);
            Serial.print("\t");
            Serial.print(INA[0].getPower(), 3);
            k++;
            Serial.println();
            delay(1000);
        }
        
    }
}
