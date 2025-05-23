#include <LiquidCrystal.h>
const int rs = 5, en = 6, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Servo.h>
#define servoPin 3
Servo myservo;
int pos = 0;

#define PhotoResistor A0
int light;




void setup() {
  // set up the LCD's number of columns and rows:
  myservo.attach(servoPin);
  myservo.write(pos);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Light Intensity");
}

void loop() {
  light = analogRead(PhotoResistor);
  pos = map(light,0,1023,0,180);
  myservo.write(pos);
 
  

  lcd.setCursor(0,1);
  lcd.print("Val: ");
  lcd.print(light);
  lcd.print(" Deg: ");
  lcd.print(pos);
  lcd.print("                          ");
  delay(10000);
  
}
