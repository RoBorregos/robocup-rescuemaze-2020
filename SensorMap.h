#ifndef SENSORMAP_H
#define SENSORMAP_H

#include "arduino.h"
#include <NewPing.h>
#include <i2cmaster.h>
#include "Movement.h"
#include "DropKit.h"
#include "Calibration.h"
#include "Control.h"

#define SONAR_NUM 6      // Number of sensors.
#define kSonarMaxDistance 200 // Maximum distance (in cm) to ping.

class SensorMap {

   public:
    SensorMap();
    Control control;
    Movement motors;
    DropKit dispenser;

    // Get the Ultrasonic Distance Right Up.
    double getDistanceRightUp();
    // Get the Ultrasonic Distance Right Down.
    double getDistanceRightDown();
    // Get the Ultrasonic Distance Left Up.
    double getDistanceLeftUp();
    // Get the Ultrasonic Distance Left Down.
    double getDistanceLeftDown();
    // Get the Ultrasonic Distance Front Left.
    double getDistanceFrontLeft();
    // Get the Ultrasonic Distance Front Right.
    double getDistanceFrontRight();
    // Check if the right wall is complete.
    bool checkWallsRight();
    // Check if the left wall is complete.
    bool checkWallsLeft();
    // Check in the walls if there are heat victims.
    bool heatVictim(double desire);
    // Check in the walls if there are letters.
    bool visualVictim();
    // Check in the walls if there are coloured victims(red, green, yellow).
    bool colouredVictim(); 
    // Temperature return in degrees celcius.
    float temperatureCelcius(int mlx);
    // Turn on a LED for 5 seconds.
    void turnLED();

    int LED = 4;

    const uint8_t kWaitBetweenUltrasonic = 50;

    int temperature_sensor_right = 0x50<<1;   // Sensor adress 1
    int temperature_sensor_left = 0x55<<1;    // Sensor adress 2
};
#endif