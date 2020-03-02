#ifndef MULTIPLEXOR_H
#define MULTIPLEXOR_H

#include "arduino.h"
#include "Wire.h"
#include <i2cmaster.h>

#define TCAADDR 0x70

extern "C"
{
#include "utility/twi.h" // from Wire library, so we can do bus scanning
}

class Multiplexor
{

public:
    // Give a multiplexor ID to each sensor.
    void tcaselect(uint8_t number);
    //I2C_scanner.
    void setup();
}
