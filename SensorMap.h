/* ROBORREGOS MAZE 2020.
 * This SensorMap class has all the functions
 * To identify anything in the Map, this class
 * Works with all the sensors of the robot.
*/
#ifndef SENSORMAP_H
#define SENSORMAP_H

#include "arduino.h"
#include "Wire.h"
#include <i2cmaster.h>
#include <Adafruit_TCS34725.h>
#include <Ultrasonic.h>

extern "C"
{
#include "utility/twi.h"
}

#define TCAADDR 0x70          // Multiplexor numbers.

class SensorMap
{

public:
    SensorMap();
    // Get the Ultrasonic Distance Right Up.
    int getDistanceRightUp();
    // Get the Ultrasonic Distance Right Down.
    int getDistanceRightDown();
    // Get the Ultrasonic Distance Left Up.
    int getDistanceLeftUp();
    // Get the Ultrasonic Distance Left Down.
    int getDistanceLeftDown();
    // Get the Ultrasonic Distance Front Left.
    int getDistanceFrontLeft();
    // Get the Ultrasonic Distance Front Right.
    int getDistanceFrontRight();
    // Check if the right wall is complete.
    bool checkWallsRight();
    // Check if the left wall is complete.
    bool checkWallsLeft();
    // Check in the right wall if there is a heat victim.
    bool heatVictimRight();
    // Check in the left wall if there is a heat victim.
    bool heatVictimLeft();
    // Check in the walls if there are letters.
    bool visualVictim();
    // Check in the walls if there are coloured victims(red, green, yellow).
    bool colouredVictim();
    // Temperature return in degrees celcius.
    float temperatureCelcius(int mlx);
    // Detect a black tile.
    bool blackTile();
    // Give a multiplexor ID to each sensor.
    void tcaselect(int number);

    const uint8_t kWaitBetweenUltrasonic = 50;
    const int kWaitFiveSeconds = 5000;
    const int kWaitBetweenDropKit = 2000;
    const uint8_t kMaxWallDistance = 15;
    const uint8_t kMinimumTemperature = 28;
    const uint8_t kMaximumTemperature = 40;

    const uint8_t kWaitToSend = 20;

    const uint8_t kDistanceWall = 20;

    const int temperature_sensor_right = 0x50 << 1; // Sensor adress 1
    const int temperature_sensor_left = 0x55 << 1;  // Sensor adress 2

private:
    /*const uint8_t kSonarLeftFrontTrigger = 4;
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
        const uint8_t kSonarLeftDownEcho = 15; */

    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);
};
#endif