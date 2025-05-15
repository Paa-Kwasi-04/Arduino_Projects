#define redPin 9
#define greenPin 10
#define bluePin 11

int r;int g;int b;
void setup() {
  // put your setup code here, to run once:
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  
}

void loop() {
//   put your main code here, to run repeatedly:
//
//   for(r=0;r<256;r++){
//        setColor(r,g,b);
//        delay(10);
//   }
//   for(g=0;g<256;g++){
//        setColor(r,g,b);
//        delay(10);
//   }
//   for(b =0;b<256;b++){
//       setColor(r,g,b);
//       delay(10);
//   }
  setColor(255,0,0);
  delay(1000);
  setColor(0,255,0);
  delay(1000);
  setColor(0,0,255);
  delay(1000);
  setColor(255,255,0);
  delay(1000);
  setColor(255,0,255);
  delay(1000);
  setColor(0,255,255);
  delay(1000);
  setColor(255,255,255);
  delay(1000);
    setColor(0,0,0);
  delay(1000);
 

}

void setColor(int red,int green,int blue){
  analogWrite(redPin,red);
  analogWrite(greenPin,green);
  analogWrite(bluePin,blue);
  
}
