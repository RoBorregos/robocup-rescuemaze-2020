#include "Robot.h"

Robot::Robot() {
  Multiplexor multii;
  Multiplexor *const i2c = &multii;

  Motors robo;
  Motors *const robot = &robo;

  BNO direct(i2c);
  bno_ = &direct;

  SensorMap sensorr(i2c);
  maps_ = &sensorr;

  Control controll(bno_, maps_);
  control_ = &controll;

  Movement robocup(bno_, control_, robot);
  movement_ = &robocup;
}

SensorMap* Robot::getMap() {
    return maps_;
}

BNO* Robot::getBNO() {
    return bno_;
}

Movement* Robot::getMovement() {
    return movement_;
}

Screen* Robot::getScreen() {
    return screen_;
}

DropKit* Robot::getDropKit() {
    return dispenser_;
}

Multiplexor* Robot::getMultiplexor() {
    return i2c_;
}