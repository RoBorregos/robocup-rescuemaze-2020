/* Roborregos 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
*/
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "arduino.h"
#include "BNO.h"
#include "Control.h"
#include "Motors.h"
#include "Common.h"

class Movement {
    
  public:
    Movement();
    Movement(BNO *b, Control *s, Motors *r);
    // Move the robot forward with P.   
    void advancePID(const double desire);
    // Move the robot backwards with P.
    void moveBackPID(const double desire);
    // Turn left or right depending on the desired angle.
    void turnDegrees(double desire);  

    const int kUnitLimit = 500;

    // Turns.
    const double kPTurns = 1.07; 
    const double kITurns = 2.91; 
    const double kDTurns = 3.33;

    const uint8_t kRange_error = 2;

    const uint8_t N = 0;
    const uint8_t E = 90;
    const uint8_t S = 180;
    const int W = 270;  

    volatile uint16_t encoder_count_left;
    volatile uint16_t encoder_count_right;

    private:
      BNO *bno_;
      Control *system_;
      Motors *robot_;
};
#endif