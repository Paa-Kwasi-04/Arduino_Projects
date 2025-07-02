#include <Servo.h>

Servo myservo;int i,j;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);  // using the servo library disables PWM function of digital pinsF
  myservo.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(i=0;i<=180;i+= 20){  // Increases angle of motor to 180 with increment of 20
    myservo.write(i);
    delay(1000);
  }
  for(j=180;j>0;j-= 20){
    myservo.write(j);
    delay(1000);
  }

}
