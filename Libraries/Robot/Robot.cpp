#include "Robot.h"

Robot::Robot() {
    i2c_ = new Multiplexor();

    bno_ = new BNO(i2c_);

    maps_ = new SensorMap(i2c_);

    movement_ = new Movement(bno_, new Control(bno_, maps_), new Motors());
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