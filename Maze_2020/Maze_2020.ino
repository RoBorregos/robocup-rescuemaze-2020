#include <Arduino.h>
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Control.h"
#include "Multiplexor.h"
#include "DropKit.h"
#include "BNO.h"

const uint8_t kEncoder1 = 2;
const uint8_t kEncoder2 = 3;
Movement *movement;

void encoderCountLeft() {
  movement->encoderCountLeft();
}

void encoderCountRight() {
  movement->encoderCountRight();
}

void setup() {
  Serial.begin(9600);
  Screen screen;
  DropKit dispenser;

  Control *control;

  SensorMap *maps;

  BNO *bno;

  Multiplexor multii;
  Multiplexor *const i2c = &multii;

  Motors robo;
  Motors *const robot = &robo;

  BNO direct(i2c);
  bno = &direct;

  SensorMap sensorr(i2c);
  maps = &sensorr;

  Control controll(bno, maps);
  control = &controll;

  Movement robocup(bno, control, robot);
  movement = &robocup;
  attachInterrupt(digitalPinToInterrupt(kEncoder1), encoderCountLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(kEncoder2), encoderCountRight, RISING);

  
  robot->turnLeft(255);
  


  /*while (bno->orientationStatus() != 3) {
    screen.writeLCDdown("I'm not ready");
  }
  screen.writeLCDdown("I'm ready");
  control->initializeLED();
  robot->initializeMotors();*/
}
void loop() {
}
