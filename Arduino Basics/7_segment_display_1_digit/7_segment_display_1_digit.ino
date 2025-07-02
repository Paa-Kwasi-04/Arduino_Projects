
#define a 2
#define b 3
#define c 4
#define d 5
#define e 6
#define f 7
#define g 8
#define dp 9

int tim = 1000;



void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<10;i++){
    pinMode(i,OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // Displaying all decimal numbers
  display0();delay(tim);clearDisplay();
  display1();delay(tim);clearDisplay();
  display2();delay(tim);clearDisplay();
  display3();delay(tim);clearDisplay();
  display4();delay(tim);clearDisplay();
  display5();delay(tim);clearDisplay();
  display6();delay(tim);clearDisplay();
  display7();delay(tim);clearDisplay();
  display8();delay(tim);clearDisplay();
  display9();delay(tim);clearDisplay();

}



void clearDisplay(){
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
  digitalWrite(dp,LOW);
}
void display0(void){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
}
void display1(void){
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
}
void display2(void){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(d,HIGH);
}
void display3(void){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
}
void display4(void){
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
}
void display5(void){
  digitalWrite(a,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
}
void display6(void){
  digitalWrite(a,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
}
void display7(void){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
}
void display8(void){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}
void display9(void){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
}
