// Incremental PI (Tustin-discretized) - Ts = 1 ms
const int analogPin = A0;
const int pwmPin = 11;
const float Vref = 5.0;
const int ADCmax = 1023;
const unsigned long Ts_ms = 1;   // 1 ms sample time

// Discrete incremental coefficients (from Tustin)
const float b0 = 6.9703;// multiplies e[k]
const float b1 = -6.6461;// multiplies e[k-1] (note sign is included here)


// Limits (u in volts)
const float u_min = 0.0;
const float u_max = 5.0;

float e = 0.0, e_prev = 0.0;
float u = 0.0, u_prev = 0.0;
float Setpoint = 1.2; // volts

unsigned long lastMillis = 0;

void setup() {
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);
  Serial.begin(115200);
  lastMillis = millis();
  Serial.println("time(ms),Vcap,u_volts,pwm");
}

void loop() {
  // run at ~1 ms intervals
  if (millis() - lastMillis < Ts_ms) return;
  lastMillis = millis();

  // measure voltage (volts)
  int raw = analogRead(analogPin);
  float Vcap = (raw / (float)ADCmax) * Vref;

  // compute error
  e = Setpoint - Vcap;

  // incremental PI update (discrete Tustin form)
  float du = B0 * e + B1 * e_prev; // note B1 is negative already
  u = u_prev + du;

  // map to PWM and write
  int pwm = (int)round((u / Vref) * 255.0);
  pwm = constrain(pwm, 0, 255);
  analogWrite(pwmPin, pwm);

  // telemetry
  Serial.print(millis()); Serial.print(",");
  Serial.print(Vcap,4); Serial.print(",");
  Serial.print(u,4); Serial.print(",");
  Serial.println(pwm);

  // shift states
  e_prev = e;
  u_prev = u;
}
