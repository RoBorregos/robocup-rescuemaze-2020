/* ROBORREGOS MAZE 2020.
 * This BNO class has all functions to get
 * the robot angle, write on screen, and
 * calibrate all sensors.
*/
#ifndef BNO_H
#define BNO_H

#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "arduino.h"

class BNO
{

public:
  BNO();
  Adafruit_BNO055 bno_;
  // Get the difference of the current angle with the 0, and return a new error.
  double getDifferenceWithZero();
  // Get the current angle, return the event.orientation.x through a function.
  double getAngleX();
  // Get the current angle, return the event.orientation.Y through a function.
  double getAngleY();
  // Get the current angle, return the event.orientation.Z through a function.
  double getAngleZ();
  // Initialize BNO.
  void BNOCalibration();
  /* Return the Orientation Status of the BNO, the numbers to return are... 
       * 1. This number means that the variable "x" is already calibrated.
       * 2. This number means that the variable "y" is already calibrated
       * 3. This number means that's the BNO is already calibrated.
      */
  uint8_t orientationStatus();

  const int kTimeToPrintBNO = 1000;
  const uint8_t kRepose = 250;
};
#endif
