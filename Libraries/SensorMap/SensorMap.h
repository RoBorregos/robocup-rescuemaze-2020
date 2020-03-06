/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This SensorMap class has all the functions
 * To identify anything in the Map, this class
 * Works with all the sensors of the robot.
*/
#ifndef SENSORMAP_H
#define SENSORMAP_H

#include "arduino.h"
#include "Wire.h"
#include <Adafruit_TCS34725.h>
#include "Multiplexor.h"
#include <Ultrasonic.h>

class SensorMap {

public:
    SensorMap(Multiplexor *multi);
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
    // Get the Ultrasonic Distance Back.
    int getDistanceBack();
    // Check if the right wall is complete.
    bool checkWallsRight();
    // Check if the left wall is complete.
    bool checkWallsLeft();
    // Check if the front wall is complete.
    bool checkWallsFront();
    // Check if the back wall is complete.
    bool checkWallsBack();
    // Check in the right wall if there is a heat victim.
    bool heatVictimRight();
    // Check in the left wall if there is a heat victim.
    bool heatVictimLeft();
    // Check in the walls if there are letters.
    bool visualVictim();
    // Check in the walls if there are coloured victims(red, green, yellow).
    bool colouredVictim();
    // Temperature return in degrees celcius.
    float temperatureCelcius(const int mlx);
    // Detect a black tile.
    bool blackTile();
    // Detect a silver tile.
    bool silverTile();

    const uint8_t kWaitBetweenUltrasonic = 50;
    const int kWaitFiveSeconds = 5000;
    const int kWaitBetweenDropKit = 2000;
    const uint8_t kMaxWallDistance = 7;
    const uint8_t kMinimumTemperature = 28;
    const uint8_t kMaximumTemperature = 40;

    const uint8_t kWaitToSend = 20;
    const int kTimeToPrint = 1000;

    const uint8_t kRangeBlackTile = 115;

    const uint8_t kColoSensorID = 3;

    const uint8_t kDistanceWall = 20;

    const int temperature_sensor_right = 0x50 << 1; // Sensor adress 1
    const int temperature_sensor_left = 0x55 << 1;  // Sensor adress 2
        
    Multiplexor *i2c_;
    Adafruit_TCS34725 tcs_ = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);
};
#endif