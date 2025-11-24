#define Vc1 A0
#define Vc2 A1
#define VPot A2
#define  PWMpin 11


const float vref = 5.0;
const int ADCmax = 1023;
const unsigned long Ts_ms = 1;
unsigned long lastMillis,currentMillis;
int pwm = 0;

float x1,x2,kx,r;
float k1 = -1.8985;
float k2 = 1.1107;
float ko = 0.2122;
float u = 0;
float I = 0;
float e = 0;
float dt = 0;

void setup() {
  pinMode(Vc1,INPUT);
  pinMode(Vc2,INPUT);
  pinMode(VPot,INPUT);
  pinMode(PWMpin, OUTPUT);
  Serial.begin(115200);
  lastMillis = millis();

}

void loop() {

  currentMillis = millis();
dt = currentMillis - lastMillis;
if (dt >= Ts_ms){
    lastMillis = currentMillis;

    float dt_s = dt / 1000.0;   

    x1 = analogRead(Vc1)*(vref/ADCmax);
    x2 = analogRead(Vc2)*(vref/ADCmax);
    r  = analogRead(VPot)*(vref/ADCmax);

    e = r - x2;
    kx = k1*x1 + k2*x2;

    I += e * dt_s;

    u = -kx + ko*I;

    pwm = (int)round((u / vref) * 255.0);
    pwm = constrain(pwm, 0, 255);
    analogWrite(PWMpin, pwm);

    Serial.print("Setpoint: ");Serial.print(r); Serial.print(" , ");
    Serial.print("Error_Signal: ");Serial.print(e); Serial.print(" , ");
    Serial.print("X1: ");Serial.print(x1); Serial.print(" , ");
    Serial.print("X2: ");Serial.print(x2); Serial.print(" , ");
    Serial.print("Control Signal: ");Serial.print(u); Serial.print(" , ");
    Serial.print("PWM Signal: ");Serial.println(pwm);

}


}
