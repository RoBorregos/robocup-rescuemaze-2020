/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This multiplexor class is to give an ID number
 * to each I2C sensor.
*/
#ifndef MULTIPLEXOR_H
#define MULTIPLEXOR_H

#include "arduino.h"
#include "Wire.h"
#include <i2cmaster.h>

#define TCAADDR 0x70

extern "C" {
#include "utility/twi.h" // From Wire library, so we can do bus scanning
}

class Multiplexor {

    public:
        Multiplexor();
        // Give a multiplexor ID to each sensor.
        void tcaselect(uint8_t number);

        const uint8_t kWaitToSend = 20;
};
#endif