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
  
  if (current_angle_x > 180) {
    desire = desire - initial_difference;
    if (desire < 0) {
      desire += 360;
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
  
  if (error < -180) {
     error += 360;
   }
    
  else if (error > 180) {
    error -= 360;
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
  new_desire = new_desire - 90;
  if (new_desire < 0) {
    new_desire = new_desire + 360;
  }
  else {}
  return new_desire;
}

double Control::getNewDesireRight(double new_desire) {
  new_desire = new_desire + 90;
  if (new_desire > 360) {
    new_desire = new_desire - 360;
  }
  else{}
  return new_desire;
}

bool Control::detectRamp() {
  if (bno_.getAngleY() < -4 && bno_.getAngleY() > -35) {
    if (bno_.getAngleZ() < 3 && bno_.getAngleZ() > -3) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

bool Control::bumperLevel1() {
  if (bno_.getAngleY() < -2 && bno_.getAngleY() > -5) {
    if (bno_.getAngleZ() > 3 || bno_.getAngleZ() < -3) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

bool Control::bumperLevel2() {
  if (bno_.getAngleY() < -5 && bno_.getAngleY() > -9) {
    if (bno_.getAngleZ() > 3 || bno_.getAngleZ() < -3) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

bool Control::bumperLevel3() {
  if (bno_.getAngleY() < -9 && bno_.getAngleY() > -15) {
    if (bno_.getAngleZ() > 3 || bno_.getAngleZ() < -3) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}