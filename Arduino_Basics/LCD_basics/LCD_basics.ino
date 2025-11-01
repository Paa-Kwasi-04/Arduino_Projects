#include <LiquidCrystal.h>// include the library code

char array1[]="Name: Paa Kwasi ";
char array2[] = "Kesse Manfo-Owusu";

int tim = 5000;  //the value of delay time



const int rs = 5, en = 6, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
}

void loop() 
{
    lcd.setCursor(0,0);  // set the cursor to column 0, line 0
    for ( int positionCounter1 = 0; positionCounter1 < 17; positionCounter1++)
    {
      lcd.print(array1[positionCounter1]);  // Print a message to the LCD.
      delay(tim);  //wait for 250 ms
    }


    lcd.setCursor(0,1);
    for(int pos2 = 0;pos2 <17;pos2++){
          lcd.print(array2[pos2]);
          delay(tim);
 }
    
    

    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
    delay(tim);  //wait for 250 
}
