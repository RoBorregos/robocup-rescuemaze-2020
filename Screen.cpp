/* ROBORREGOS MAZE 2020
 * This screen file has all the functions to
 * print in the screen.
 * To get more information, go to Screen.h file.
 * Marlon Romo (MarlonB500).
*/
#include "Screen.h"

LiquidCrystal_I2C lcd_(0x3F, 16, 2);

Screen::Screen() {}

void Screen::writeNumLCD(const int num) {
  lcd_.clear();
  lcd_.print(num);
}

void Screen::writeLyricsLCD(const char letter) {
  lcd_.clear();
  lcd_.print(letter);
}

void Screen::writeLCD(const String sE1, const String sE2) {
  lcd_.clear();
  lcd_.print(sE1);
  lcd_.setCursor(0, 1);
  lcd_.print(sE2);
}

void Screen::writeLCDdown(const String sE1) {
  lcd_.clear();
  lcd_.setCursor(0, 1);
  lcd_.print(sE1);
}

void Screen::printLocation(const double x, const double y, const double z) {
  lcd_.clear();
  lcd_.setCursor(0, 0);
  lcd_.print("X:");
  lcd_.setCursor(2, 0);
  lcd_.print(x);

  lcd_.setCursor(7, 0);
  lcd_.print("Y:");
  lcd_.setCursor(9, 0);
  lcd_.print(y);

  lcd_.setCursor(11, 0);
  lcd_.print("Z:");
  lcd_.setCursor(13, 0);
  lcd_.print(z);

  delay(kTimeSeeLocation);
}

void Screen::LCDCalibration() {
  lcd_.clear();
  lcd_.init();
  lcd_.backlight();
  lcd_.setCursor(0, 1);
  lcd_.print("LCD ready");
  delay(kTimeToPrintLCD);
}