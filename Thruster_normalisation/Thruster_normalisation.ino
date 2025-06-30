//#include <Adafruit_ADS1X15.h>
//
//Adafruit_ADS1015 ads;
//
//#define PWM_pin 15
//#define EN 14
//#define SPEED_PIN A0
//
//float rpm,temp;
//
//
//
//void setup()
//{
//    Serial.begin(9600);
//    
//    pinMode(EN,OUTPUT);
//    pinMode(PWM_pin,OUTPUT);
//    pinMode(SPEED_PIN,INPUT);
//    digitalWrite(EN,HIGH);
//    
//    if (!ads.begin()) {
//    Serial.println("Failed to initialize ADS.");
//    while (1);
//  }
//  
//   ads.setGain(GAIN_ONE); // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
//}
//
//  
//
//void loop() {
//
//    delay(500);      // Wait for ESCON to stabilize
//  
//    int16_t temp_raw = ads.readADC_SingleEnded(1);
//    float temp_volts = ads.computeVolts(temp_raw);  // voltage range is 0 - 4.096V
//    int16_t speed_raw = ads.readADC_SingleEnded(0);
//    double voltage = ads.computeVolts(speed_raw);    // Convert raw ADC reading to voltage (ADS1115 is 16-bit) 
//   
//    
//  
//    // Convert back to original -4V to +4V signal:
//    // signal = (voltage - 2.5) / 0.625
//    double speed_volts = (voltage - 2) / 0.625;
//    
//  
//    temp = (35*temp_volts)/4.096 + 25.2;
// 
//    if( speed_volts >= -3.9243){
//      rpm = 2248.3999*speed_volts + 7174.31008;
//    }else if(speed_volts >= -4.04466 || speed_volts < -3.9243){
//      rpm = 12083.3333*speed_volts + 45760.6667;
//    }else if(speed_volts >= -4.02096 || speed_volts <-4.04466){
//      rpm = -8470.58824*speed_volts -37372.8824;
//    }else if(speed_volts < -4.02096){
//      rpm = (161699.404 * speed_volts +646873.203) ;
//    }
////    rpm_2 = 428.52*pow(speed_volts,5)+ 4278.37*pow(speed_volts,4)+15467.16*pow(speed_volts,3)+ 24606.19*pow(speed_volts,2)+ 18842.05*speed_volts+10829.21;
//
//
//
//    
//    Serial.print("Temp_Raw: ");Serial.print(temp_raw );Serial.print(" ");
//    Serial.print("Temp_Volts: ");Serial.print(temp_volts);Serial.print(" ");
//    Serial.print("Temperature: ");Serial.println(temp);
//    Serial.println(" ");
//  
//    Serial.print("Speed_Raw: ");Serial.print(speed_raw);Serial.print(" ");
//    Serial.print("Speed_Volts: ");Serial.print(speed_volts,6);Serial.print(" ");
//    Serial.print("Rpm: ");Serial.println(rpm);
//
//}




#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads;

#define PWM_pin 15
#define EN 14
#define SPEED_PIN A0

float rpm, temp;

// Lookup table generated from MATLAB (sorted by ADC values)
const int16_t adc_table[] = {-264, -263, -262, -260, -258, -255, -249, -247, -232, -216, 
                            -202, -183, -125, -83, -2, 38, 58, 78, 121, 141, 
                            161, 181, 201, 221, 241, 263, 281, 301, 321, 343, 
                            383, 404, 424, 444, 464, 484, 507, 529, 550, 566, 
                            606, 667, 706, 729, 774, 787, 828, 848, 888, 948, 
                            968, 998};

const float rpm_table[] = {-7137.0f, -6123.0f, -5683.0f, -4527.0f, -3790.0f, -3210.0f, -2621.0f, -2493.0f, -1897.0f, -1610.0f, 
                          -1409.0f, -1317.0f, -890.0f, -580.0f, 0.1f, 290.0f, 433.0f, 581.0f, 880.0f, 1026.0f, 
                          1072.0f, 1310.0f, 1457.0f, 1600.0f, 1748.0f, 1910.0f, 2034.0f, 2180.0f, 2325.0f, 2489.0f, 
                          2767.0f, 2918.0f, 3061.0f, 3202.0f, 3352.0f, 3497.0f, 3639.0f, 3799.0f, 3943.0f, 4089.0f, 
                          4377.0f, 4813.0f, 5099.0f, 5242.0f, 5547.0f, 5679.0f, 5973.0f, 6117.0f, 6403.0f, 6837.0f, 
                          6984.0f, 7250.0f};

const int TABLE_SIZE = sizeof(adc_table)/sizeof(adc_table[0]);

float adcToRPM(int16_t raw_adc) {
  // Handle out-of-range values
  if (raw_adc <= adc_table[0]) return rpm_table[0];
  if (raw_adc >= adc_table[TABLE_SIZE-1]) return rpm_table[TABLE_SIZE-1];
  
  // Binary search to find the interval
  uint16_t low = 0;
  uint16_t high = TABLE_SIZE - 1;
  
  while (high - low > 1) {
    uint16_t mid = (low + high) / 2;
    if (raw_adc < adc_table[mid]) {
      high = mid;
    } else {
      low = mid;
    }
  }
  
  // Linear interpolation
  float adc_low = adc_table[low];
  float adc_high = adc_table[high];
  float rpm_low = rpm_table[low];
  float rpm_high = rpm_table[high];
  
  return rpm_low + (rpm_high - rpm_low) * (raw_adc - adc_low) / (adc_high - adc_low);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(EN, OUTPUT);
  pinMode(PWM_pin, OUTPUT);
  pinMode(SPEED_PIN, INPUT);
  digitalWrite(EN, HIGH);
  
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  
  ads.setGain(GAIN_ONE); // ±4.096V
}

void loop() {
  delay(100); // Reduced delay for faster sampling
  
  int16_t temp_raw = ads.readADC_SingleEnded(1);
  float temp_volts = ads.computeVolts(temp_raw);
  temp = (35.0 * temp_volts) / 4.096 + 25.2;
  
  int16_t speed_raw = ads.readADC_SingleEnded(0);
  rpm = adcToRPM(speed_raw);
  
  // Diagnostic output
  Serial.print("ADC: ");
  Serial.print(speed_raw);
  Serial.print(" Temp: ");
  Serial.print(temp, 1);
  Serial.print("°C RPM: ");
  Serial.println(rpm, 1);
}
