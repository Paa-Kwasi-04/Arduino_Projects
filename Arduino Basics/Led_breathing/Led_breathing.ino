int ledPin = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<= 255;i++){ // PWM function, for varing voltage output
    analogWrite(ledPin,i);
    delay(10);
  }

  for(int j=255;j>0;j--){
    analogWrite(ledPin,j);
    delay(10);
  }
  delay(200);

}
