/* ROBORREGOS MAZE 2020
 * This screen file has all the functions to
 * print in the screen.
 * To get more information, go to Screen.h file.
*/
#include "Screen.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

Screen::Screen() {}

void Screen::writeNumLCD(const int num)
{
  lcd.clear();
  lcd.print(num);
}

void Screen::writeLyricsLCD(const char letter)
{
  lcd.clear();
  lcd.print(letter);
}

void Screen::writeLCD(const String sE1, const String sE2)
{
  lcd.clear();
  lcd.print(sE1);
  lcd.setCursor(0, 1);
  lcd.print(sE2);
}

void Screen::writeLCDdown(const String sE1)
{
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(sE1);
}

void Screen::printLocation(const double x, const double y, const double z)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.setCursor(2, 0);
  lcd.print(x);

  lcd.setCursor(7, 0);
  lcd.print("Y:");
  lcd.setCursor(9, 0);
  lcd.print(y);

  lcd.setCursor(11, 0);
  lcd.print("Z:");
  lcd.setCursor(13, 0);
  lcd.print(z);

  delay(kTimeSeeLocation);
}

void Screen::LCDCalibration()
{
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.print("Hola Mundo");
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  lcd.print(" Segundos");
  delay(kTimeToPrintLCD);
}