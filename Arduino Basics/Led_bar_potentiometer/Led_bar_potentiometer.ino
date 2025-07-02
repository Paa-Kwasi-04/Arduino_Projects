
void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<10;i++){
    pinMode(i,OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  float a = analogRead(0);
  a = map(a,0,1023,0,9);

  for(int i=0;i<=a;i++){
    digitalWrite(i,HIGH);
  }
    for(int j= 9w
    ;j>a;j--){
      digitalWrite(j,LOW);
  }
  delay(50);
}
