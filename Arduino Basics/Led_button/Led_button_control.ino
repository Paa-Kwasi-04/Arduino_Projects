int LedPin = 8;
int Button = 2;
int status = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(Button,INPUT);
  pinMode(LedPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    status = digitalRead(Button);
    if (status == LOW){
      digitalWrite(LedPin,HIGH);
    }
    if(status == HIGH){
      digitalWrite(LedPin,LOW);
    }
    
}
