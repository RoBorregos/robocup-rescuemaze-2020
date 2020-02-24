/* This DropKit class has all the functions to drop
 * A kit if the robot detect a Victim on the map.
 * This class works with the robot dispenser.
 * To get more information, go to DropKit.h file.
*/
#include "DropKit.h"

DropKit::DropKit() {}

void DropKit::setup() {
  dispenser.attach(42);
  dispenser.write(90);   // Initialize the dispenser in 90 degrees(in the middle).
}

void DropKit::dropOneKitLeft() {
  dispenser.write(dispenserDegrees_0);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_100);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_90);
  delay(kTime_2ms);
}

void DropKit::dropOneKitRight() {
  dispenser.write(dispenserDegrees_180);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_80);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_90);
  delay(kTime_2ms);
}

void DropKit::dropTwoKitsRight() {
  dispenser.write(dispenserDegrees_180);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_80);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_90);
  delay(kTime_2ms);
  dispenser.write(dispenserDegrees_180);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_80);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_90);
  delay(kTime_2ms);
}

void DropKit::dropTwoKitsLeft() {
  dispenser.write(dispenserDegrees_0);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_100);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_90);
  delay(kTime_2ms);
  dispenser.write(dispenserDegrees_0);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_100);
  delay(kTime_1sec);
  dispenser.write(dispenserDegrees_90);
  delay(kTime_2ms);
}