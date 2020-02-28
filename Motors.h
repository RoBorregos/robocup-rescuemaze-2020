#ifndef MOTORS_H
#define MOTORS_H

#include "arduino.h"
#include "Common.h"

class Motors {

    public:
      Motors();
      // Turn the robot 90 degrees to the left.
      void turnLeft(const uint8_t speed);
      // Turn the robot 90 degrees to the right.
      void turnRight(const uint8_t speed);
      // Stop the robot.
      void stopEngines();
      // Go fast to the ramp.
      void fastForward();
      // Go back fast.
      void fastBackward();
      // Move the robot backwards.
      void moveBack();
      // Move the robot forward through the pwm assigned in each side.
      void forwardPwm(const uint8_t pwm_right, const uint8_t pwm_left);
      // Move the robot backward through the pwm assigned in each side.
      void backwardPwm(const uint8_t pwm_right, const uint8_t pwm_left);

      const uint8_t kMotorLeftForward1 = 9;  
      const uint8_t kMotorLeftForward2 = 8;  
      const uint8_t kMotorLeftBack1 = 10;
      const uint8_t kMotorLeftBack2 = 11;
      const uint8_t kMotorRightForward1 = 5;
      const uint8_t kMotorRightForward2 = 4;
      const uint8_t kMotorRightBack1 = 7;
      const uint8_t kMotorRightBack2 = 6;   

      const uint8_t kTimeToStop = 10;  
};
#endif