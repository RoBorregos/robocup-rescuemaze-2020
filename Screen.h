#ifndef SCREEN_H
#define SCREEN_H

#include "BNO.h"
#include <LiquidCrystal_I2C.h>

class Screen {

    public:
      Screen();
      Movement motors;
      Adafruit_BNO055 bno; 
      BNO bno_;
      // Initialize LCD.
      void LCDCalibration();
      // Write a number.      
      void writeNumLCD(const int num);
      // Write a letter.
      void writeLyricsLCD(const char letra);
      // Write a sentence.
      void writeLCD(const String sE1,const String sE2);
      // Write a sentence down.
      void writeLCDdown(const String sE1);
      // Print the location of the robot.
      void printLocation(const double x, const double y, const double z);
      // Initialize all the sensors.
      void calibrationAll(); 
      // Turn on a LED for 5 seconds.
      void turnLED();

      const int LED = 4;

      const uint8_t kTimeSeeLocation = 100;
      const uint8_t kTimeToPrintLCD = 100;
      const int kDelayAfterBNO = 2700;  

      const uint8_t kTime100ms = 100;
};
#endif