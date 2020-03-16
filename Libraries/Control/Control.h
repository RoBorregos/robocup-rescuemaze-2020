/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This Control class has all the fuctions to get
 * The angle, desired angle and sensors error.
 * This class is so necessary to move the robot to
 * The correct direction of the robot.
*/
#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include <Wire.h>
#include "arduino.h"
#include "SensorMap.h"
#include "BNO.h"
#include "Common.h"

class Control {

  public:
    Control(BNO *bno, SensorMap *map);
    // Get the new desired angle respect to the difference achieved.
    double getDesiredAngle(double desire);
    // Get the difference with the desired angle to the current angle, return error.
    double getAngleError(const double current_angle_x, const double desire);
    // Get the difference with the desired distance to the current distance, return error.
    double getErrorUltrasonic(const double current_distance, const double desire_ultrasonic);
    // Verify if the pwm is in the range (kLimit_inf_pwm - kLimit_sup_pwm).
    void getPwm(double &pwm);
    // Get a new desire to drop a kit to the right.
    double getNewDesireLeft(double new_desire);
    // Get a new desire to drop a kit to the left.
    double getNewDesireRight(double new_desire);
    // Return true if there is a ramp, and false otherwise.
    bool detectRamp();
    // Return true if there is a bumper Level 1.
    bool bumperLevel1();
    // Return true if there is a bumper level 2.
    bool bumperLevel2();
    // Return true if there is a bumper level 3.
    bool bumperLevel3();
    // Get the correct pwm with the BNO.
    double getPwmBNO(const double desire, double &pwm_left_final, double &pwm_right_final);
    // Get the correct pwm with the Ultrasonic sensors.
    double getPwmUltrasonic(double &pwm_left_final_ultrasonic, double &pwm_right_final_ultrasonic);

    const uint8_t kLimitSupDegrees = 35;
    const uint8_t kLimitInfDegrees = 11;
    const uint8_t kRangeAngleZ = 3;
    const uint8_t kLimitInfBumper1 = 2;
    const uint8_t kLimitSupBumper1 = 5;
    const uint8_t kLimitSupBumper2 = 9;
    const uint8_t kLimitSupBumper3 = 15;

    const uint8_t kTime200ms = 200;

    const uint8_t kDegrees90 = 90;
    const int kDegrees360 = 360;
    const uint8_t kDegrees180 = 180;

    const uint8_t LED1 = 42;
    const uint8_t LED2 = 41;


  private:
    BNO *bno_;
    SensorMap *map_;
};
#endif