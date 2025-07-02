void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<6;i++){
    pinMode(i,OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=2;i<6;i++){
    digitalWrite(i,HIGH);
    delay(300);
    digitalWrite(i,LOW);
  }
    for(int j=6;j>0;j--){
      digitalWrite(j,HIGH);
      delay(300);
      digitalWrite(j,LOW);
  }
  
}
