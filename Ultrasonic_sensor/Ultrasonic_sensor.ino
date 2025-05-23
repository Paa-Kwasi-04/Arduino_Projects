#include <LiquidCrystal.h>



#define Trig 8
#define Echo 9

float duration, distance;
char str [] = "Reading Dist... ";
const int rs = 5, en = 6, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  lcd.setCursor(16,0);
  for(int i = 0;i<16;i++){
    lcd.scrollDisplayLeft();
    lcd.print(str[i]);
    delay(250);
  }


}

void loop() {
  lcd.clear();
  digitalWrite(Trig, LOW);  // ensures that the pin is actually low before
  delayMicroseconds(2);  
  digitalWrite(Trig, HIGH);  // sends the ultrasound out for 10 microseconds
  delayMicroseconds(10);  
  digitalWrite(Trig, LOW); 

  duration = pulseIn(Echo, HIGH); // listens in for the echopin to be high and for how long
  distance = (duration*.0343)/2;  // calculates the distance the object is away from sensor

  lcd.setCursor(0,0);
  lcd.print("Distance:"); 
  lcd.print(distance,2); 
  lcd.print("cm"); 
  delay(1000); 




}
