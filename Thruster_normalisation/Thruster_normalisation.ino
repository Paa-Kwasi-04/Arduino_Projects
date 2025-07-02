/#include <Adafruit_ADS1X15.h>

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
    double speed_volts = ads.computeVolts(speed_raw)*100;    //  
   
    
  
  
    rpm = (speed_volts * 14387)/400 - 7135;
    temp = (35*temp_volts)/4.096 + 25.2;
 
       
    Serial.print("Temp_Raw: ");Serial.print(temp_raw );Serial.print(" ");
    Serial.print("Temp_Volts: ");Serial.print(temp_volts);Serial.print(" ");
    Serial.print("Temperature: ");Serial.println(temp);
    Serial.println(" ");
  
    Serial.print("Speed_Raw: ");Serial.print(speed_raw);Serial.print(" ");
    Serial.print("Speed_Volts: ");Serial.print(speed_volts,4);Serial.print(" ");
    Serial.print("Rpm: ");Serial.println(rpm);

}
