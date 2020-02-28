/* Roborregos 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement(){}

Movement::Movement(BNO *b, Control *s, Motors *r) {
    bno_ = b;
    system_ = s;
    robot_ = r;
}

void Movement::advancePID(const double desire) {
  encoder_count_left = 0;
  encoder_count_right = 0;

  do {
      double pwm_right_enginees = system_->getPwmBNORight(desire); // Negative.
      double pwm_left_enginees = system_->getPwmBNOLeft(desire); // Positive. 
      if (pwm_left_enginees > 1) {
          pwm_left_enginees = Common::kLimit_inf_pwm;
          system_->getPwm(pwm_left_enginees);
      }

      else if (pwm_right_enginees < 0) {
          pwm_right_enginees = Common::kLimit_inf_pwm;
          system_->getPwm(pwm_right_enginees);
      }
      robot_->forwardPwm(pwm_right_enginees, pwm_left_enginees);
    }
    while (encoder_count_left < kUnitLimit and encoder_count_right < kUnitLimit);
}

void Movement::moveBackPID(const double desire) {
  encoder_count_left = 0;
  encoder_count_right = 0;

  do {
      double pwm_right_enginees = system_->getPwmBNORight(desire); // Negative.
      double pwm_left_enginees = system_->getPwmBNOLeft(desire); // Positive. 
      if (pwm_left_enginees > 1) {
          pwm_left_enginees = Common::kLimit_inf_pwm;
          system_->getPwm(pwm_left_enginees);
      }

      else if (pwm_right_enginees < 0) {
          pwm_right_enginees = Common::kLimit_inf_pwm;
          system_->getPwm(pwm_right_enginees);
      }
      robot_->backwardPwm(pwm_right_enginees, pwm_left_enginees);
    }
    while (encoder_count_left < kUnitLimit and encoder_count_right < kUnitLimit);
}

void Movement::turnDegrees(double desire) {
  double speed = 0;
  double error = 0;
  double current_angle_x = bno_->getAngleX();
  desire = system_->getDesiredAngle(desire);
  
  do{
    error = system_->getAngleError(current_angle_x, desire);
    Serial.println(error);
    speed = kPTurns * error;
    
    system_->getPwm(speed); // Verify to the pwm stay in the range.
    if (error < 0) { 
      robot_->turnLeft(speed);
    }   
    else {
      robot_->turnRight(speed);
    } 
  }
  while ( error < -(kRange_error) || error > kRange_error); // Asigne a range to stop the robot.
  robot_->stopEngines();
}