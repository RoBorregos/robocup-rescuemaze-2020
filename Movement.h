/* Roborregos 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
*/
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "SensorMap.h"
#include "Control.h"
#include "DropKit.h"
#include "arduino.h"
#include "BNO.h"

class Movement {
    
  public:
    Movement();
    Control control;
    SensorMap sensor;
    BNO logic;

    // Move the robot forward.   
    void advance(const double desire, const double desireUltrasonic);
    // Turn the robot 90 degrees to the left.
    void turnLeft(const uint8_t vel);
    // Turn the robot 90 degrees to the right.
    void turnRight(const uint8_t vel);
    // Turn left or right depending on the desired angle.
    void turnDegrees(double desire);
    // Stop the robot.
    void stopEngines();
    // Go fast to the ramp.
    void fastForward();
    // Move the robot backwards.
    void moveBack();
    // Move the robot forward through the pwm asigned in each side.
    void forwardPwm(const uint8_t pwm_right, const uint8_t pwm_left);

    const uint8_t kMotorLeftForward1 = 9;  
    const uint8_t kMotorLeftForward2 = 8;  
    const uint8_t kMotorLeftBack1 = 10;
    const uint8_t kMotorLeftBack2 = 11;
    const uint8_t kMotorRightForward1 = 5;
    const uint8_t kMotorRightForward2 = 4;
    const uint8_t kMotorRightBack1 = 7;
    const uint8_t kMotorRightBack2 = 6;  

    const uint8_t kLimit_sup_pwm = 255; 
    const uint8_t kLimit_inf_pwm = 145;

    // Turns.
    const double kPTurns = 1.07; 
    const double kITurns = 2.91; 
    const double kDTurns = 3.33;

    // Advance.
    const double kPAdvance = 4.52; 
    const double kIAdvance = 3.45; 
    const double kDAdvance = 2.05;

    const uint8_t kRange_error = 2;

    const uint8_t N = 0;
    const uint8_t E = 90;
    const uint8_t S = 180;
    const int W = 270;  

    volatile uint16_t eCount1;
    volatile uint16_t eCount2;

    const uint8_t kTimeToStop = 10; 
};
#endif