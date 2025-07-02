#define IN1 2
#define IN2 3
#define En 9



void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(En,OUTPUT);

}

void loop() {
  // so the motor will increase in one direction and change direction
  for(int i =50;i<256;i += 50){
      analogWrite(En,i);
      direction_1();
      delay(3000);
  }

  delay(2000);
  for(int i =50;i<256;i +=50){
      analogWrite(En,i);
      direction_2();
      delay(3000);
  }
}

void direction_1(void){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}

void direction_2(void){
  digitalWrite(IN2,HIGH);
  digitalWrite(IN1,LOW);
}
