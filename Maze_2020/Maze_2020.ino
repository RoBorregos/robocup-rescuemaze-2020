#include "arduino.h"
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Control.h"
#include "Multiplexor.h"
#include "DropKit.h"
#include "BNO.h"

int encoder_1 = 2;
int encoder_2 = 3;
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
  Control *control;
  BNO *bno;
  SensorMap *maps;

  DropKit dropkit;
  DropKit *const dispenser = &dropkit;

  Multiplexor multiplexor;
  Multiplexor *const i2c = &multiplexor;

  Motors motors;
  Motors *const robot = &motors;

  BNO direct(i2c);
  bno = &direct;

  SensorMap sensorr(i2c);
  maps = &sensorr;

  Control controll(bno, maps);
  control = &controll;

  Movement robocup(bno, control, robot, maps, dispenser);
  movement = &robocup;
  
  while (bno->orientationStatus() != 3) {
    screen.writeLCDdown("I'm not ready");
  }
  screen.writeLCDdown("LET'S GO MAZE");
  attachInterrupt(digitalPinToInterrupt(encoder_1), encoderCountLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder_2), encoderCountRight, RISING);
}
void loop() {
}
