#include "Screen.h"

LiquidCrystal_I2C lcd(0x27,20,4);

Screen::Screen(){}

void Screen::calibrationAll() {
  bno.begin();
  bno.setExtCrystalUse(true);
  lcd.init();
  lcd.backlight();
  writeLCDdown("LCD ready");
  lcd.clear();
  lcd.setCursor(0,0);
  
  while(bno_.orientationStatus() != 3) {
    lcd.setCursor(6,0);
    lcd.print("I´m not ready");
  }
  lcd.setCursor(6,1);
  lcd.print("I´m ready");

  delay(kDelayAfterBNO);

  pinMode(LED, INPUT); 
  digitalWrite(LED, LOW);
  
  pinMode(motors.kMotorLeftForward1, OUTPUT);
  pinMode(motors.kMotorLeftForward2, OUTPUT);
  pinMode(motors.kMotorLeftBack1, OUTPUT);
  pinMode(motors.kMotorLeftBack2, OUTPUT);
  pinMode(motors.kMotorRightForward1, OUTPUT);
  pinMode(motors.kMotorRightForward2, OUTPUT);
  pinMode(motors.kMotorRightBack1, OUTPUT);
  pinMode(motors.kMotorRightBack2, OUTPUT);

  sensors_event_t event;
  bno.getEvent(&event);
}

void Screen::writeNumLCD(const int num) {
  lcd.clear();
  lcd.print(num);
}

void Screen::writeLyricsLCD(const char letra) {
  lcd.print(letra);
}

void Screen::writeLCD(const String sE1, const String sE2) {
  lcd.clear();
  lcd.print(sE1);
  lcd.setCursor(0, 1);
  lcd.print(sE2);
}

void Screen::writeLCDdown(const String sE1) {
  lcd.setCursor(0, 1);
  lcd.print(sE1);
}

void Screen::printLocation(const double x, const double y, const double z) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.setCursor(2,0);
  lcd.print(x);

   lcd.setCursor(7,0);
  lcd.print("Y:");
  lcd.setCursor(9,0);
  lcd.print(y);

  lcd.setCursor(11,0);
  lcd.print("Z:");
  lcd.setCursor(13,0);
  lcd.print(z);

delay(kTimeSeeLocation);
}

void Screen::turnLED() {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
}

void Screen::LCDCalibration() {
  lcd.init(); 
  lcd.backlight();
  lcd.print("Hola Mundo");
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(kTimeToPrintLCD);
}