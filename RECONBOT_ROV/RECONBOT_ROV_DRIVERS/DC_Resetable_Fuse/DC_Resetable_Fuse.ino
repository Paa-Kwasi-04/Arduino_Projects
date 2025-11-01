#define SHIFT_LOAD_PIN  19 // S/L pin on KS032
#define CLOCK_PIN       20 // CLK pin on KS032
#define DATA_OUT_PIN    17 // DO pin on KS032

void setup() {
  Serial.begin(115200);

  pinMode(SHIFT_LOAD_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_OUT_PIN, INPUT);

  digitalWrite(SHIFT_LOAD_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW);
}

void loop() {
  uint8_t fuseStatus = readFuseStatus();

  Serial.print("Fuse States: ");
  Serial.println(fuseStatus,BIN);  // Now prints Fuse 1 as the rightmost bit

  delay(1000);
}

uint8_t readFuseStatus() {
  uint8_t result = 0;

  // Latch the inputs into the shift register
  digitalWrite(SHIFT_LOAD_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(SHIFT_LOAD_PIN, HIGH);

  // Read 8 bits, storing the first-read bit as bit 0 (Fuse 1)
  for (int i = 0; i <= 8; i++) {
    digitalWrite(CLOCK_PIN, HIGH);
    result |= (digitalRead(DATA_OUT_PIN) << i);  // << i instead of << (7 - i)
    digitalWrite(CLOCK_PIN, LOW);
  }

  return result;
}
