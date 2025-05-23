#include <DIYables_IRcontroller.h> // DIYables_IRcontroller library
#define IR_RECEIVER_PIN 4 // The Arduino pin connected to IR controller
DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200);

#define redPin 9
#define greenPin 10
#define bluePin 11

int rVal = 255;
int gVal = 255;
int bVal = 255;
int val = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irController.begin();
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  
}

void loop() {
  Key21 command = irController.getKey(),color;
  if(command == Key21::KEY_1 || command == Key21::KEY_2 || command == Key21::KEY_3){
    color = command;
  }
  if (command != Key21::NONE) {
    switch (command) {
      case Key21::KEY_VOL_MINUS:  // to decrease the intensity of the led
        switch (color){
          case Key21::KEY_1:
            rVal -= val ;
            setColor(rVal,0,0);
            break;
          case Key21::KEY_2:
            bVal -= val;
            setColor(0,bVal,0);
            break;
          case Key21::KEY_3:
            gVal -= val;
            setColor(0,0,gVal); 
            break;           
        }
        break;

      case Key21::KEY_VOL_PLUS:  // to increase the intensity of the led
          switch (color){
            case Key21::KEY_1:
              rVal += val;
              setColor(rVal,0,0);
              break;
            case Key21::KEY_2:
              bVal += val;
              setColor(0,bVal,0);
              break;
            case Key21::KEY_3:
              gVal += val;
              setColor(0,0,gVal);
              break;            
        }
        break;

      case Key21::KEY_1:
        Serial.println("Red");
        setColor(rVal,0,0);
        break;

      case Key21::KEY_2:
        Serial.println("Blue");
        setColor(0,bVal,0);
        break;

      case Key21::KEY_3:
        Serial.println("Green");
        setColor(0,0,gVal);
        break;

      default:
        Serial.println("WARNING: undefined command:");
        break;
    }
  }
}

void setColor(int red,int green,int blue){
  analogWrite(redPin,red);
  analogWrite(greenPin,green);
  analogWrite(bluePin,blue);
}
