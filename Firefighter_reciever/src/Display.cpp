#include <LiquidCrystal_I2C.h>
#include"Display.h"

LiquidCrystal_I2C myLCD(0X3F,LCD_COLOUMN, LCD_ROW);
void init_display() 
  {
  myLCD.init();// initialize the myLCD
  myLCD.backlight();
  myLCD.setCursor(0, 0);
  myLCD.print("CH4 : ");//iniialize static display 
  myLCD.setCursor(15, 0);
  myLCD.print("%");
  myLCD.setCursor(0, 1);
  myLCD.print("IBUT: ");
  myLCD.setCursor(15, 1);
  myLCD.print("ppm");
  myLCD.setCursor(0, 2);
  myLCD.print("O2  : ");
  myLCD.setCursor(15, 2);
  myLCD.print("%");
  myLCD.setCursor(0, 3);
  myLCD.print("CO  : ");
  myLCD.setCursor(15, 3);
  myLCD.print("ppm");
}


void updateDisplayLine (float val, int line)//update the value that is to be displayed and print on LCD 
{
  char gas [6];
  myLCD.setCursor(6, line);
  dtostrf(val, 5, 2, gas);
  myLCD.print(gas);
}