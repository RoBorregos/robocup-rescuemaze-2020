#ifndef SCREEN_H
#define SCREEN_H

#include "Movement.h"
#include <LiquidCrystal_I2C.h>
#include "Movement.h"

class Screen {

    public:
      Screen();
      // Initialize LCD.
      void LCDCalibration();
      // Write a number.      
      void writeNumLCD(const int num);
      // Write a letter.
      void writeLyricsLCD(const char letter);
      // Write a sentence.
      void writeLCD(const String sE1,const String sE2);
      // Write a sentence down.
      void writeLCDdown(const String sE1);
      // Print the location of the robot.
      void printLocation(const double x, const double y, const double z);

      const uint8_t kTimeSeeLocation = 100;
      const uint8_t kTimeToPrintLCD = 100; 
};
#endif