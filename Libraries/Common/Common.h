/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This file has all the variables that you can use
 * in all the files.
*/
#ifndef COMMON_H
#define COMMON_H

#include "arduino.h"

namespace Common {
    extern const uint8_t kLimitSupPwmTurns;
    extern const uint8_t kLimitInfPwmTurns;
    
    extern const uint8_t kLimitSupPwmAdvance;
    extern const uint8_t kLimitInfPwmAdvance;

    extern const uint8_t kLimitInfPwmAdvanceSwitch; 
    
    extern const double kPAdvance;
    extern const double kIAdvance;
    extern const double kDAdvance;
    
    extern const double kPUltrasonic;
    extern const double kIUltrasonic;
    extern const double kDUltrasonic;
} // namespace Common
#endif