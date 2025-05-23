#define ledPin 2
#define tiltPin 9
int state;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(tiltPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(tiltPin);
  digitalWrite(ledPin,state);
  

}
