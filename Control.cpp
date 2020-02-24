/* Roborregos 2020.
 * This Control class has all the fuctions to get
 * the angle, desired angle and sensors error.
 * This class is so necessary to move the robot to
 * The correct direction of the robot.
 * To get more information, go to Control.h file.
*/
#include "Control.h"

Control::Control() {}

double Control::getDifferenceWithZero() { 
  double error_generated = 0;
  
  double current_angle = getAngleBNOX();
  if (current_angle >= 180) {
    error_generated = (360 - current_angle);
  }
  
  else {
    error_generated = current_angle;
    error_generated = -(error_generated);
  }
  
  return error_generated;
}

double Control::getAngleBNOX() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.x;
}

double Control::getAngleBNOY() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.y;
}

double Control::getAngleBNOZ() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.z;
}

double Control::getDesiredAngle(double desire) {
  double initial_difference = getDifferenceWithZero(); 
  double current_angle = getAngleBNOX();
  
  if (current_angle > 180) {
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

double Control::getAngleError(const double current_angle, const double desire){
  double error = desire - current_angle;
  
  if (error < -180) {
     error += 360;
   }
    
  else if (error > 180) {
    error -= 360;
  }
  
  return error;
}

double Control::getErrorUltrasonic(const double current_distance, const double desire) {
  double error = current_distance - desire;
  return error;
}

void Control::getPwm(double &vel) { 
  if (vel < kLimit_inf_pwm) {
    vel = kLimit_inf_pwm;
  }
  
  else if (vel > kLimit_sup_pwm) {
    vel = kLimit_sup_pwm;
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