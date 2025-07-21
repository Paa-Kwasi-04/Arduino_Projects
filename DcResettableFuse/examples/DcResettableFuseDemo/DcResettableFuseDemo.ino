#include "DcResettableFuse.h"
#define NUM_REGISTERS   1  // Example: 1 shift register = 8 fuses

DcResettableFuse fuse;
bool fuseStates[MAX_FUSES];  // Boolean array for fuse states
uint8_t numFuses;  // Number of fuses read

void setup() {
    Serial.begin(115200);

    if (fuse.begin(NUM_REGISTERS)) {
        Serial.println("Fuses initialized successfully.");
    } else {
        Serial.println("Failed to initialize fuses.");
    }
}

void loop() {
    numFuses = fuse.readAllStates(fuseStates);

    Serial.println("Fuse states:");
    for (uint8_t i = 0; i < numFuses; ++i) {
        Serial.print("Fuse ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(fuseStates[i] ? "TRIPPED" : "OK");
    }

    delay(1000);
}
