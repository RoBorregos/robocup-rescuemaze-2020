/* This DropKit class has all the functions to drop
 * A kit if the robot detect a Victim on the map.
 * This class works with the robot dispenser.
 * To get more information, go to DropKit.h file.
*/
#include "DropKit.h"

DropKit::DropKit() {}

void DropKit::setup() {
  dispenser.attach(42);
  dispenser.write(kDispenserDegrees90);   // Initialize the dispenser in 90 degrees(in the middle).
}

void DropKit::dropOneKitLeft() {
  dispenser.write(kDispenserDegrees0);
  delay(kTime_1sec);
  dispenser.write(kDispenserDegrees100);
  delay(kTime_1sec);
  dispenser.write(kDispenserDegrees90);
  delay(kTime_2ms);
}

void DropKit::dropOneKitRight() {
  dispenser.write(kDispenserDegrees180);
  delay(kTime_1sec);
  dispenser.write(kDispenserDegrees80);
  delay(kTime_1sec);
  dispenser.write(kDispenserDegrees90);
  delay(kTime_2ms);
}

void DropKit::dropTwoKitsRight() {
    dropOneKitRight();
    dropOneKitRight();
}

void DropKit::dropTwoKitsLeft() {
    dropOneKitLeft();
    dropOneKitLeft();
}