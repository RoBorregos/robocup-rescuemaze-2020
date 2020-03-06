#include <Arduino.h>
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Control.h"
#include "Multiplexor.h"
#include "DropKit.h"
#include "BNO.h"



void setup() {
  Serial.begin(9600);
  Control *control;
  SensorMap *maps;
  BNO *bno;
  Movement *move;

  Screen screen;
  DropKit dispenser;

  Multiplexor multii;
  Multiplexor *const i2c = &multii;

  Motors robo;
  Motors *const robot = &robo;

  BNO direction(i2c);
  bno = &direction;

  SensorMap sensorr(i2c);
  maps = &sensorr;

  Control controll(bno, maps);
  control = &controll;

  Movement robocup(bno, control, robot);
  move = &robocup;
  

  screen.writeLCDdown("Hola");
  
  /*while (bno->orientationStatus() != 3) {
    screen.writeLCDdown("I'm not ready");
  }
  screen.writeLCDdown("I'm ready");
  control->initializeLED();
  robot->initializeMotors();*/
}

void loop() {
}
