#include "SevSeg.h"
SevSeg sevseg;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = true; // So 01:05 shows as 0105
  bool disableDecPoint = true;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins,
               resistorsOnSegments, updateWithDelays,
               leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {
  static unsigned long previousMillis = 0;
  static int minutesPassed = 0;

  if (millis() - previousMillis >= 60000) { // Every 60,000 ms = 1 minute
    previousMillis += 60000;
    minutesPassed++;

    if (minutesPassed >= 1440) { // 24 hours = 1440 minutes
      minutesPassed = 0;
    }

    int hours = minutesPassed / 60;
    int minutes = minutesPassed % 60;
    int timeToDisplay = hours * 100 + minutes; // e.g. 01:05 becomes 105 → 0105 on display

    sevseg.setNumber(timeToDisplay);
  }

  sevseg.refreshDisplay(); // Must be called continuously
}
y
