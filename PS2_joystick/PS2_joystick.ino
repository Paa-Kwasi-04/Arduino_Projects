#include <ezButton.h>
#include <LiquidCrystal.h>

#define VRX A1
#define VRY A0
ezButton button(2);
int X_POS = 0;
int Y_POS = 0,bVal ;




// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 6, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Coordinates");
}

void loop() {
  button.loop();
  X_POS = map(analogRead(VRX),0,1023,-50,50);
  Y_POS = map(analogRead(VRY),0,1023,50,-50);
  bVal = button.getState();



  lcd.setCursor(0,1);
  lcd.print("X:");
  lcd.print(X_POS);
  lcd.print(" Y:");
  lcd.print(Y_POS);
  lcd.print(" Z:");
  lcd.print(bVal);
  lcd.print("           ");
  delay(500);
  
  
  
  
}
