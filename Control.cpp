/* Roborregos 2020.
 * This Control class has all the fuctions to get
 * the angle, desired angle and sensors error.
 * This class is so necessary to move the robot to
 * The correct direction of the robot.
 * To get more information, go to Control.h file.
*/
#include "Control.h"

Control::Control() {}

double Control::getDesiredAngle(double desire) {
  double initial_difference = bno_.getDifferenceWithZero(); 
  double current_angle_x = bno_.getAngleX();
  
  if (current_angle_x > kDegrees180) {
    desire = desire - initial_difference;
    if (desire < 0) {
      desire += kDegrees360;
    }
    
    else{
      desire = desire;
    }
  }

  else {
    desire = desire - initial_difference;
  }
  
  return desire;
}

double Control::getAngleError(const double current_angle_x, const double desire){
  double error = desire - current_angle_x;
  
  if (error < -kDegrees180) {
     error += kDegrees360;
   }
    
  else if (error > kDegrees180) {
    error -= kDegrees360;
  }
  
  return error;
}

double Control::getErrorUltrasonic(const double current_distance, const double desireUltrasonic) {
  double error = current_distance - desireUltrasonic;
  return error;
}

void Control::getPwm(double &speed) { 
  if (speed < kLimit_inf_pwm) {
    speed = kLimit_inf_pwm;
  }
  
  else if (speed > kLimit_sup_pwm) {
    speed = kLimit_sup_pwm;
  }
}

double Control::getNewDesireLeft(double new_desire) {
  new_desire = new_desire - kDegrees90;
  if (new_desire < 0) {
    new_desire = new_desire + kDegrees360;
  }
  return new_desire;
}

double Control::getNewDesireRight(double new_desire) {
  new_desire = new_desire + kDegrees90;
  if (new_desire > kDegrees360) {
    new_desire = new_desire - kDegrees360;
  }
  return new_desire;
}

bool Control::detectRamp() {
  return (bno_.getAngleY() < -kLimitInfDegrees && bno_.getAngleY() > -kLimitSupDegrees && bno_.getAngleZ() < kRangeAngleZ && bno_.getAngleZ() > -kRangeAngleZ);
}

bool Control::bumperLevel1() {
  return (bno_.getAngleY() < -kLimitInfBumper1 && bno_.getAngleY() > -kLimitSupBumper1 && bno_.getAngleZ() > kRangeAngleZ || bno_.getAngleZ() < -kRangeAngleZ);
}

bool Control::bumperLevel2() {
  return (bno_.getAngleY() < -kLimitSupBumper1 && bno_.getAngleY() > -kLimitSupBumper2 && bno_.getAngleZ() > kRangeAngleZ || bno_.getAngleZ() < -kRangeAngleZ);
}

bool Control::bumperLevel3() {
  return (bno_.getAngleY() < -kLimitSupBumper2 && bno_.getAngleY() > -kLimitSupBumper3 && bno_.getAngleZ() > kRangeAngleZ || bno_.getAngleZ() < -kRangeAngleZ);
}