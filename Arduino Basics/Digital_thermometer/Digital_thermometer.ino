#include <LiquidCrystal.h> // include the library

#define B 3950  // Thermistor B value

LiquidCrystal lcd(5, 6, 10, 11, 12, 13);
char temp[] = "Temp: ";

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // Set up the LCD's columns and rows
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Reading Temp...");

  static unsigned long previousMillis = 0;

  int a = analogRead(A0);  // Read thermistor value
  float R0 = 10000.0;
  float R = R0 * (1023.0 / a - 1.0);
  float temperature = 1.0 / (log(R / R0) / B + 1.0 / 298.15) - 273.15;

  if (millis() - previousMillis >= 10000) {
    previousMillis += 10000;

    lcd.clear();
    lcd.setCursor(0, 1);

    for (int i = 0; i < 6; i++) {
      lcd.print(temp[i]);
      delay(250);
    }

    lcd.print(temperature, 1); // Print temperature with 1 decimal place
    lcd.print(" C");
    delay(2000);
    lcd.clear();
  }
}

  
