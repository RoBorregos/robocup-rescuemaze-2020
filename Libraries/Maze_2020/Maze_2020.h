#include <Arduino.h>
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Multiplexor.h"
#include "DropKit.h"
#include "BNO.h"
#include "Control.h"
#include "DropKit.h"

Screen screen;
DropKit dispenser;

Control *control;
SensorMap *maps;
BNO *bno;
Movement *move;

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
move = &robocup;