int ledPin = 13;
int pot = 0; // sets potentiometer to A0


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int a = analogRead(pot);
  if(a > 500){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }

}
