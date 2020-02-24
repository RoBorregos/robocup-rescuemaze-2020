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

class Movement {
    
  public:
    Movement();
    Control control;
    SensorMap sensor;

    // Move the robot to the forward.   
    void advance(const double desire, const double desireUltrasonic);
    // Turn the robot to 90 degrees to the left.
    void turnLeft(const uint8_t vel);
    // Turn the robot to 90 degrees to the right.
    void turnRight(const uint8_t vel);
    // Turn left or right depending on the desired angle.
    void turnDegrees(double desire);
    // Stop the robot.
    void stopEngines();
    // Go fast to the ramp.
    void fastForward();
    // Move the robot to the back.
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

    const uint8_t kPwm_max = 255;
    const uint8_t kLimit_sup_pwm = 255; 
    const uint8_t kLimit_inf_pwm = 145;

    // Turns.
    const double kP = 1.07; 
    const double kI = 2.91; 
    const double kD = 3.33;

    // Advance.
    const double kP2 = 4.52; 
    const double kI2 = 3.45; 
    const double kD2 = 2.05;

    const uint8_t kRange_error = 2;

    const uint8_t N = 0;
    const uint8_t E = 90;
    const uint8_t S = 180;
    const int W = 270;  

    const uint8_t kTimeToStop = 10; 
};
#endif