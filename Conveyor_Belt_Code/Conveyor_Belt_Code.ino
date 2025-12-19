#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define IR 13
#define IR_OUT 49
int value_ir;

//  MOtor Pin definitions
#define dirPin  2
#define stepPin  3
#define enPin  4


LiquidCrystal_I2C lcd(0x27,20,4); 

void setup() {
  // Motor Pin config
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enPin, OUTPUT);

  //IR sensor Pin config
  pinMode(IR,INPUT);
  pinMode(IR_OUT,OUTPUT);
  
  digitalWrite(enPin, LOW);    // Enable motor and set direction
  digitalWrite(dirPin,LOW);

  lcd.init();   //Setup lcd screen
  lcd.backlight();

}

void loop() {
  value_ir = digitalRead(IR);  //Reading sensor data
  digitalWrite(IR_OUT,value_ir);

  lcd.clear();

  if(value_ir == HIGH){
    digitalWrite(stepPin,HIGH);
    delaymicrosecond(800);
    digitalWrite(stepPin,LOW);
    delaymicrosecond(800);

    lcd.setCursor(3,0);
    lcd.print("DETECTED");
  }else{
    lcd.setCursor(3,0);
    lcd.print("NOT DETECTED");
  }

  
}