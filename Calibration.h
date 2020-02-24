#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <LiquidCrystal_I2C.h>
#include "arduino.h"
#include "Movement.h"
#include "SensorMap.h"

class Calibration {

  public:
    Calibration();
    Movement motors;
    Adafruit_BNO055 bno; 
    SensorMap sensor;

    // Initialize LCD.
    void LCDCalibration();
    // Initialize BNO.
    void BNOCalibration();
    // Return the Orientation Status of the BNO, the numbers to return are 1, 2, and 3, if the number returned is not 3, it means that it´s not calibrated.
    uint8_t orientationStatus();
    // Initialize all the sensors.
    void calibrationAll();
    // Write a number.      
    void writeNumLCD(const int num);
    // Write a letter.
    void writeLyricsLCD(const char letra);
    // Write a sentence.
    void writeLCD(const String sE1,const String sE2);
    // Write a sentence down.
    void writeLCDdown(const String sE1); 
    // Print the location of the robot.
    void printLocation(const double x, const double y, const double z);

    const uint8_t kTimeSeeLocation = 100;
    const uint8_t kTimeToPrint = 100;
    const int kTimeToPrintLCD = 1000;
    const uint8_t kRepose = 250;
    const int kDelayAfterBNO = 2700;  
};
#endif