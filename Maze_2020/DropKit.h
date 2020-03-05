/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This DropKit class has all the functions to drop
 * A kit if the robot detect a Victim on the map.
 * This class works with the robot dispenser.
*/
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

    const uint8_t kDispenserDegrees0 = 0;
    const uint8_t kDispenserDegrees80 = 80;
    const uint8_t kDispenserDegrees90 = 90;
    const uint8_t kDispenserDegrees100 = 100;
    const uint8_t kDispenserDegrees180 = 180;

    const int kTime_1sec = 1000;
    const uint8_t kTime_2ms = 200;

    const uint8_t kPin = 42;

  private:
    Servo dispenser_;
};
#endif
