#include <Arduino.h>
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Multiplexor.h"
#include "DropKit.h"
#include "BNO.h"
#include "Control.h"

void setup() {
  Serial.begin(9600);
  SensorMap *maps;
  BNO *bno;
  Control *control;
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
}

void loop() {
}
