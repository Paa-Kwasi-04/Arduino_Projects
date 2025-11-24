// Incremental PI (Tustin-discretized) - Ts = 1 ms
const int Capacitor_Volt_Pin = A0;
const int Pot_Volt_Pin = A1;
const int pwmPin = 11;
const float Vref = 5.0;
const int ADCmax = 1023;
const unsigned long Ts_ms = 1;   // 1 ms sample time

// Discrete incremental coefficients (from Tustin)
const float a = 0.96464;
const float b = 0.982;


// Limits (u in volts)
const float u_min = 0.0;
const float u_max = 5.0;

float e = 0.0, e_prev = 0.0;
float u = 0.0, u_prev = 0.0;



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

  // measure Capacitor voltage 
  int raw = analogRead(Capacitor_Volt_Pin);
  float Vcap = (raw / (float)ADCmax) * Vref;

  //Get Setpoint Voltage
  int Setpoint_raw = analogRead(Pot_Volt_Pin);
  float Setpoint = (Setpoint_raw / (float)ADCmax) * Vref;
  
  // compute error
  e = Setpoint - Vcap;

  //  PI Control Algorithm 
  u = u_prev + a*(e - b*e_prev); 

  // map to PWM and write
  int pwm = (int)round((u / Vref) * 255.0);
  pwm = constrain(pwm, 0, 255);
  analogWrite(pwmPin, pwm);

  int resolution = 4;

  // telemetry
  Serial.print("Setpoint"); Serial.print(":");Serial.print(Setpoint,resolution); Serial.print(" , ");
  Serial.print("Error_Signal"); Serial.print(":");Serial.print(e,resolution); Serial.print(" , ");
  Serial.print("Capacitor Volt"); Serial.print(":");Serial.print(Vcap,resolution); Serial.print(" , ");
  Serial.print("PID Signal"); Serial.print(":");Serial.print(u,resolution); Serial.print(" , ");
  Serial.print("PWM Signal"); Serial.print(":");Serial.println(pwm);

  // shift states
  e_prev = e;
  u_prev = u;
}
