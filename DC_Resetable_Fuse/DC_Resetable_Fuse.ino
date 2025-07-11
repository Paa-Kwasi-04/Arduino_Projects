// Teensy 4.1 Example for KS-032 PTC8 Fuse Module
#define SHIFT_LOAD_PIN  19 // S/L pin on KS032
#define CLOCK_PIN       20  // CLK pin on KS032
#define DATA_OUT_PIN    17  // DO pin on KS032

void setup() {
  Serial.begin(115200);

  // Configure pins
  pinMode(SHIFT_LOAD_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_OUT_PIN, INPUT);

  // Initialize pins to default state
  digitalWrite(SHIFT_LOAD_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW);
}

//void loop() {
//  uint8_t fuseStatus = readFuseStatus();
//
//  Serial.print("Fuse States: ");
//  Serial.println(fuseStatus, BIN);  // Print as binary, e.g., 00001100
//
//  delay(1000);  // Read once per second
//}

uint8_t readFuseStatus() {
  uint8_t result = 0;

  // 1. Latch current fuse states into shift register
  digitalWrite(SHIFT_LOAD_PIN, LOW);
  delayMicroseconds(5);  // brief delay to ensure latch happens
  digitalWrite(SHIFT_LOAD_PIN, HIGH);

  // 2. Read 8 bits from the DO pin
  for (int i = 0; i < 8; i++) {
    digitalWrite(CLOCK_PIN, HIGH);             // Advance to next bit
    delayMicroseconds(2);                      // Small pulse width
    result |= (digitalRead(DATA_OUT_PIN) << (7 - i)); // Store bit
    digitalWrite(CLOCK_PIN, LOW);
    delayMicroseconds(2);
  }

  return result;
}










void loop() {
  uint8_t fuseStatus = readFuseStatus();

  Serial.print("Raw Fuse States (Binary): ");
  Serial.println(fuseStatus, BIN);

  for (int i = 0; i < 8; i++) {
    Serial.print("Fuse ");
    Serial.print(i + 1);
    Serial.print(": ");
    if (fuseStatus & (1 << (7 - i))) {
      Serial.println("TRIPPED");
    } else {
      Serial.println("OK");
    }
  }

  delay(1000);
}
