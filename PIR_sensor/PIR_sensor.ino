#define ledPin 2
#define PIR 3


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(PIR,INPUT);

}

void loop() {
  int motion = digitalRead(PIR);

  digitalWrite(ledPin,motion);

}
