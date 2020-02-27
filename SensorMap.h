/* Roborregos Maze 2020.
 * This SensorMap class has all the functions
 * To identify anything in the Map, this class
 * Works with all the sensors of the robot.
*/
#ifndef SENSORMAP_H
#define SENSORMAP_H

#include "arduino.h"
#include <NewPing.h>
#include <i2cmaster.h>
#include "Movement.h"
#include "DropKit.h"
#include "BNO.h"
#include "Control.h"

#define SONAR_NUM 6      // Number of sensors.
#define kSonarMaxDistance 200 // Maximum distance (in cm) to ping.

class SensorMap {

   public:
    SensorMap();
    Control control;
    Movement motors;
    DropKit dispenser;
    BNO bno_;

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
    // Get pwm through error(Positive).
    double getPwmUltrasonicLeft();
    // Get pwm through error(Negative).
    double getPwmUltrasonicRight();
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

    const uint8_t kWaitBetweenUltrasonic = 50;
    const int kWaitFiveSeconds = 5000;
    const int kWaitBetweenDropKit = 2000;
    const uint8_t kMaxWallDistance = 15;
    const uint8_t kMinimumTemperature = 28;
    const uint8_t kMaximumTemperature = 40;

    const uint8_t kDistanceWall = 20;

    const int temperature_sensor_right = 0x50<<1;   // Sensor adress 1
    const int temperature_sensor_left = 0x55<<1;    // Sensor adress 2

   private:
    const uint8_t kSonarLeftFrontTrigger = 4;
    const uint8_t kSonarLeftFrontEcho = 5;
    const uint8_t kSonarRightFrontTrigger = 6;
    const uint8_t kSonarRightFrontEcho = 7;
    const uint8_t kSonarRightUpTrigger = 8;
    const uint8_t kSonarRightUpEcho = 9;
    const uint8_t kSonarRightDownTrigger = 10;
    const uint8_t kSonarRightDownEcho = 11;
    const uint8_t kSonarLeftUpTrigger = 12;
    const uint8_t kSonarLeftUpEcho = 13;
    const uint8_t kSonarLeftDownTrigger = 14;
    const uint8_t kSonarLeftDownEcho = 15;

    NewPing sonar[SONAR_NUM] = {   // Sensor object array.
    NewPing(kSonarLeftFrontTrigger, kSonarLeftFrontEcho, kSonarMaxDistance), // Each sensor's trigger pin, echo pin, and max distance to ping. 
    NewPing(kSonarRightFrontTrigger, kSonarRightFrontEcho, kSonarMaxDistance), 
    NewPing(kSonarRightUpTrigger, kSonarRightUpEcho, kSonarMaxDistance), 
    NewPing(kSonarRightDownTrigger, kSonarRightDownEcho, kSonarMaxDistance), 
    NewPing(kSonarLeftUpTrigger, kSonarLeftUpEcho, kSonarMaxDistance), 
    NewPing(kSonarLeftDownTrigger, kSonarLeftDownEcho, kSonarMaxDistance)
    };
};
#endif