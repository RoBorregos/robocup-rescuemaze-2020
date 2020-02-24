#ifndef DROPKIT_H
#define DROPKIT_H

#include "arduino.h"
#include <Servo.h>

class DropKit {
    
  public:
    DropKit();
    // Initialize the dispenser.
    void setup();
    // Drop one kit for Heated Victims and Coloured Victims(red and yellow).
    void dropOneKitRight();
    // Drop one kit for Heated Victims and Coloured Victims(red and yellow).
    void dropOneKitLeft();
    // Drop two kits for Visual Victims(Stable).
    void dropTwoKitsRight();
    // Drop two kits for Visual Victims(Stable).
    void dropTwoKitsLeft();

    const uint8_t dispenserDegrees_0 = 0;
    const uint8_t dispenserDegrees_80 = 80;
    const uint8_t dispenserDegrees_90 = 90;
    const uint8_t dispenserDegrees_100 = 100;
    const uint8_t dispenserDegrees_180 = 180;

    const int kTime_1sec = 1000;
    const uint8_t kTime_2ms = 200;

  private:
     Servo dispenser; 
};
#endif