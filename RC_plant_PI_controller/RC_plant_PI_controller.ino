#include "ArduPID.h"

ArduPID myController;


// Incremental PI (Tustin-discretized) - Ts = 1 ms
const int Capacitor_Volt_Pin = A0;
const int Pot_Volt_Pin = A1;
const int pwmPin = 11;
//const float Vref = 5.0;
//const int ADCmax = 1023;
//const unsigned long Ts_ms = 1;   // 1 ms sample time

double input;
double output;
double setpoint;

double p = 0.95598;
double i = 17.33192;
double d = 0.0;

void setup() {
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);
  Serial.begin(115200);
  myController.begin(&input, &output, &setpoint, p, i, d);
  myController.setSampleTime(1);      // OPTIONAL - will ensure at least 10ms have past between successful compute() calls
  myController.setOutputLimits(0, 255);
  myController.setBias(255.0 / 2.0);
  myController.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up
  
  myController.start();
               
}

void loop() {
  // measure Capacitor voltage 
  input = analogRead(Capacitor_Volt_Pin);
  
  //Get Setpoint Voltage
  setpoint = analogRead(Pot_Volt_Pin);
  myController.compute();
  myController.debug(&Serial, "myController", PRINT_INPUT    | // Can include or comment out any of these terms to print
                                              PRINT_OUTPUT   | // in the Serial plotter
                                              PRINT_SETPOINT |
                                              PRINT_BIAS     |
                                              PRINT_P        |
                                              PRINT_I        |
                                              PRINT_D);
  
  analogWrite(pwmPin, output); // Replace with plant control signal
  int resolution = 4;


  // telemetry
  Serial.print("Setpoint"); Serial.print(":");Serial.print(setpoint); Serial.print(" , ");
  Serial.print("Capacitor Volt"); Serial.print(":");Serial.print(input); Serial.print(" , ");
  Serial.print("PID PWM Signal"); Serial.print(":");Serial.println(output);

}
