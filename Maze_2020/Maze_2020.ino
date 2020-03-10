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
  Screen screen;
  Control *control;
  SensorMap *maps;
  BNO *bno;
  Movement *movement;


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
  movement = &robocup;

  // screen.writeLCD("Hello, World", "Que");

  robot->turnRight(255);
  
  while (bno->orientationStatus() != 3) {
    screen.writeLCDdown("I'm not ready");
  }
  screen.writeLCDdown("I'm ready");
}

void loop() {
}