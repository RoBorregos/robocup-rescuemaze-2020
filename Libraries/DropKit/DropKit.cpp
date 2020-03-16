/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This DropKit class has all the functions to drop
 * A kit if the robot detect a Victim on the map.
 * This class works with the robot dispenser.
 * To get more information, go to DropKit.h file.
*/
#include "DropKit.h"

DropKit::DropKit() {}

void DropKit::setup() {
  dispenser_.attach(kPin); // Servo Pin
  dispenser_.write(kDispenserDegrees90); // Initialize the dispenser in 90 degrees(in the middle).
}

void DropKit::dropOneKitLeft() {
  dispenser_.write(kDispenserDegrees0);
  delay(kTime_1sec);
  dispenser_.write(kDispenserDegrees100);
  delay(kTime_1sec);
  dispenser_.write(kDispenserDegrees90);
  delay(kTime_2ms);
}

void DropKit::dropOneKitRight() {
  dispenser_.write(kDispenserDegrees180);
  delay(kTime_1sec);
  dispenser_.write(kDispenserDegrees80);
  delay(kTime_1sec);
  dispenser_.write(kDispenserDegrees90);
  delay(kTime_2ms);
}

void DropKit::dropTwoKitsRight() {
  dropOneKitRight();
  dropOneKitRight();
}

void DropKit::dropTwoKitsLeft(){
  dropOneKitLeft();
  dropOneKitLeft();
}

void DropKit::turnLED() {
  for(int i = 0; i < 5; ++i) {
    blinkLED();
  }
}

void DropKit::blinkLED() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(kTime200ms);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(kTime200ms);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(kTime200ms);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(kTime200ms);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(kTime200ms);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}