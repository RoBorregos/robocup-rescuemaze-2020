/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This file has all the variables that you can use
 * in all the files.
*/
#include "Common.h"

namespace Common {
    const uint8_t kLimitSupPwmTurns = 255;
    const uint8_t kLimitInfPwmTurns = 145;
    const uint8_t kLimitSupPwmAdvance = 255;
    const uint8_t kLimitInfPwmAdvance = 185;
    const double kPAdvance = 10.25;
    const double kIAdvance = 3.45;
    const double kDAdvance = 2.05;
    const double kPUltrasonic = 0.67;
    const double kIUltrasonic = 2.21;
    const double kDUltrasonic = 1.98;
}