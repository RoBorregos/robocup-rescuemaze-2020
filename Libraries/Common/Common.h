/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This file has all the variables that you can use
 * in all the files.
*/
#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include "arduino.h"

namespace Common {
    extern const uint8_t kLimitSupPwm;
    extern const uint8_t kLimitInfPwm;
    extern const double kPAdvance;
    extern const double kIAdvance;
    extern const double kDAdvance;
} // namespace Common
#endif