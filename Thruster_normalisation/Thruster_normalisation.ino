#include <Adafruit_ADS1X15.h>
#include <cmath>

using namespacing std;
Adafruit_ADS1015 ads;

#define PWM_pin 15
#define EN 14
#define SPEED_PIN A0

float rpm,temp;


void setup()
{
    Serial.begin(9600);
    
    pinMode(EN,OUTPUT);
    pinMode(PWM_pin,OUTPUT);
    pinMode(SPEED_PIN,INPUT);
    digitalWrite(EN,HIGH);
    
    if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  
   ads.setGain(GAIN_ONE); // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
}

  

void loop() {

    delay(500);      // Wait for ESCON to stabilize
  
    int16_t temp_raw = ads.readADC_SingleEnded(1);
    float temp_volts = ads.computeVolts(temp_raw);  // voltage range is 0 - 4.096V
    int16_t speed_raw = ads.readADC_SingleEnded(0);
    float voltage = ads.computeVolts(speed_raw);    // Convert raw ADC reading to voltage (ADS1115 is 16-bit) 
   
    
  
    // Convert back to original -4V to +4V signal:
    // signal = (voltage - 2.5) / 0.625
    float speed_volts = (voltage - 2) / 0.625;
    
  
    temp = (35*temp_volts)/4.096 + 25.4;
 
//    if( speed_volts >= -3.881){
//      rpm = 2276.04422*speed_volts + 7206.09163;
//    }else{
//      rpm = 88853.058*speed_volts + 353312.153;
//    }
//    rpm_2 = 428.52*pow(speed_volts,5)+ 4278.37*pow(speed_volts,4)+15467.16*pow(speed_volts,3)+ 24606.19*pow(speed_volts,2)+ 18842.05*speed_volts+10829.21;

    
    Serial.print("Temp_Raw: ");Serial.print(temp_raw );Serial.print(" ");
    Serial.print("Temp_Volts: ");Serial.print(temp_volts );Serial.print(" ");
    Serial.print("Temperature: ");Serial.println(temp);
    Serial.println(" ");
  
    Serial.print("Speed_Raw: ");Serial.print(speed_raw);Serial.print(" ");
    Serial.print("Speed_Volts: ");Serial.print(speed_volts);Serial.print(" ");
    Serial.print("Rpm: ");Serial.println(rpm_2);

}
