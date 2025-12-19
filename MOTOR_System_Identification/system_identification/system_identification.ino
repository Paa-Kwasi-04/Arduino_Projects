/* --------------------------------------------------------
    DC Motor System Identification Logger
    USING CPR = 315 (from your measurements)

    Outputs CSV:
        time_ms, pwm, rpm

    Step test:
        2s baseline
        6s at PWM = 150
        2s decay
--------------------------------------------------------- */

#define PWM_PIN   9
#define IN1_PIN   6
#define IN2_PIN   7

#define ENC_A_PIN 2
#define ENC_B_PIN 3

// ************* YOUR MEASURED CPR *************
const int CPR = 315;

// Step test timing
const int PWM_STEP = 255;
const unsigned long T_BASELINE = 2000;
const unsigned long T_STEP     = 6000;
const unsigned long T_POST     = 2000;
const unsigned long SAMPLE_INTERVAL = 20; // ms

// Quadrature decoder variables
volatile long quadCount = 0;
volatile uint8_t prevAB = 0;

// Quadrature decode lookup table
const int8_t qtable[16] = {
  0, +1, -1, 0,
  -1, 0, 0, +1,
  +1, 0, 0, -1,
   0, -1, +1, 0
};

unsigned long lastSample = 0;


// --------------------------------------------------------
// INTERRUPTS
// --------------------------------------------------------
void isrA() {
  uint8_t a = digitalRead(ENC_A_PIN);
  uint8_t b = digitalRead(ENC_B_PIN);
  uint8_t curr = (a << 1) | b;
  uint8_t index = (prevAB << 2) | curr;

  int8_t delta = qtable[index];
  if (delta) quadCount += delta;

  prevAB = curr;
}

void isrB() {
  uint8_t a = digitalRead(ENC_A_PIN);
  uint8_t b = digitalRead(ENC_B_PIN);
  uint8_t curr = (a << 1) | b;
  uint8_t index = (prevAB << 2) | curr;

  int8_t delta = qtable[index];
  if (delta) quadCount += delta;

  prevAB = curr;
}


// --------------------------------------------------------
// Setup
// --------------------------------------------------------
void setup() {

  Serial.begin(115200);
  delay(300);

  // Motor output pins
  pinMode(PWM_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  // Force motor direction (always forward)
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);

  // Encoder pins
  pinMode(ENC_A_PIN, INPUT);
  pinMode(ENC_B_PIN, INPUT);

  prevAB = (digitalRead(ENC_A_PIN) << 1) | digitalRead(ENC_B_PIN);

  attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), isrB, CHANGE);

  Serial.println("time_ms,pwm,rpm");

  lastSample = millis();
}


// --------------------------------------------------------
// Main loop (runs state machine)
// --------------------------------------------------------
void loop() {
//
//  // ------------------ 1) Baseline ------------------
//  unsigned long t0 = millis();
//  while (millis() - t0 < T_BASELINE) {
//    sampleAndPrint(0);
//  }

  // ------------------ 2) Step Input ------------------
  unsigned long t1 = millis();
  while (millis() - t1 < T_STEP) {
    analogWrite(PWM_PIN, PWM_STEP);
    sampleAndPrint(PWM_STEP);
  }

//  // ------------------ 3) Post Decay ------------------
//  analogWrite(PWM_PIN, 0);
//  unsigned long t2 = millis();
//  while (millis() - t2 < T_POST) {
//    sampleAndPrint(0);
//  }

  // Stop forever
  analogWrite(PWM_PIN, 0);
  while (1) delay(1000);
}


// --------------------------------------------------------
// Sampling function
// --------------------------------------------------------
void sampleAndPrint(int pwm_cmd) {

  unsigned long now = millis();
  if (now - lastSample < SAMPLE_INTERVAL) return;
  lastSample = now;

  // Read encoder counts
  noInterrupts();
  long counts = quadCount;
  quadCount = 0;
  interrupts();

  // Convert counts → RPM
  float rev = (float)counts / CPR;
  float rev_per_sec = rev * (1000.0 / SAMPLE_INTERVAL);
  float rpm = rev_per_sec * 60.0;

  // CSV print
  Serial.print(now);
  Serial.print(",");
  Serial.print(pwm_cmd);
  Serial.print(",");
  Serial.println(rpm, 3);
}
