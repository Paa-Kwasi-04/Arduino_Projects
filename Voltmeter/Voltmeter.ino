#include <LiquidCrystal.h>// include the library code

int tim = 250,tim2 = 5000;  //the value of delay time
const int volt = 0;
char arr1 []="Voltage Reading ";


LiquidCrystal lcd(5, 6, 10, 11, 12, 13);

void setup()
{
  pinMode(volt,INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
  lcd.setCursor(16,0);
  for(int pos1=0;pos1<16;pos1++){
    lcd.scrollDisplayLeft();
    lcd.print(arr1[pos1]);
    delay(tim);
  }
  
}

void loop(){
  
  float a = analogRead(volt)* (5.0/1023);
  
//  Serial.print("Voltage Reading: ");
//  Serial.println(a);


  lcd.setCursor(0,1);
  lcd.print("Voltage: ");
  lcd.print(a,2);
  lcd.print("V  ");
  delay(tim);
}
