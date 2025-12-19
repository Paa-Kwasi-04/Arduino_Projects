#define A_PIN 2

volatile unsigned long edgeCount = 0;

void isrA() {
  edgeCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(A_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(A_PIN), isrA, RISING);

  Serial.println("Rotate shaft ONE revolution slowly…");
}

void loop() {
  Serial.print("Edges: ");
  Serial.println(edgeCount);
  delay(200);
}
