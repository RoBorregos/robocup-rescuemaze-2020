#ifndef Robot_h
#define Robot_h

#include <Arduino.h>
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Multiplexor.h"
#include "DropKit.h"
#include "BNO.h"
#include "Control.h"

class Robot {
    private:
    SensorMap *maps_;
    BNO *bno_;
    Movement *movement_;
    Screen *screen_;
    DropKit *dispenser_;
    Multiplexor *i2c_;
    Control *control_;
      
    public:
        Robot();
        SensorMap* getMap();
        BNO* getBNO();
        Movement* getMovement();
        Screen* getScreen();
        DropKit* getDropKit();
        Multiplexor* getMultiplexor();
};

#endif