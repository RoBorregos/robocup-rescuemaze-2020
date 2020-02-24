/* Roborregos 2020.
 * This Control class has all the fuctions to get
 * The angle, desired angle and sensors error.
 * This class is so necessary to move the robot to
 * The correct direction of the robot.
*/
#ifndef CONTROL_H
#define CONTROL_H

#include <Wire.h>
#include "arduino.h"
#include "Calibration.h"

class Control {
  
  public:
    Control();
    Adafruit_BNO055 bno; 

    // Get the difference of the current angle with the 0, and return a new error.
    double getDifferenceWithZero();
    // Get the current angle, return the event.orientation.x through a function.
    double getAngleBNOX();
    // Get the current angle, return the event.orientation.Y through a function.
    double getAngleBNOY();
    // Get the current angle, return the event.orientation.Z through a function.
    double getAngleBNOZ();
    // Get the new desired angle respect to the difference achieved.
    double getDesiredAngle(double desire);
    // Get the difference with the desired angle to the current angle, return error.
    double getAngleError(const double angulo_actual, const double desire);
    // Get the difference with the desired distance to the current distance, return error.
    double getErrorUltrasonic(const double current_distance, const double desire); 
    // Verify if the pwm is in the range (kLimit_inf_pwm - kLimit_sup_pwm).
    void getPwm(double &vel);
    // Get a new desire to drop a kit to the right.
    double getNewDesireLeft(double new_desire);
    // Get a new desire to drop a kit to the left.
    double getNewDesireRight(double new_desire);

    const uint8_t kLimit_sup_pwm = 255; 
    const uint8_t kLimit_inf_pwm = 145;
};
#endif
