/* Roborregos Maze 2020.
 * This SensorMap class has all the functions
 * To identify anything in the Map, this class
 * Works with all the sensors of the robot.
 * To get more information, go to SensorMap.h file.
*/
#include "SensorMap.h"

SensorMap::SensorMap() {}

double SensorMap::getDistanceFrontLeft() {
  delay(kWaitBetweenUltrasonic);
  return sonar[0].ping_cm();
}

double SensorMap::getDistanceFrontRight() {
  delay(kWaitBetweenUltrasonic);
  return sonar[1].ping_cm();
}

double SensorMap::getDistanceRightUp() {
  delay(kWaitBetweenUltrasonic);
  return sonar[2].ping_cm();
}

double SensorMap::getDistanceRightDown() {
  delay(kWaitBetweenUltrasonic);
  return sonar[3].ping_cm();
}

double SensorMap::getDistanceLeftUp() {
  delay(kWaitBetweenUltrasonic);
  return sonar[4].ping_cm();
}

double SensorMap::getDistanceLeftDown() {
  delay(kWaitBetweenUltrasonic);
  return sonar[5].ping_cm(); 
}

bool SensorMap::checkWallsRight() {
    return (getDistanceRightUp() < 15 || getDistanceRightDown() < 15);
}

bool SensorMap::checkWallsLeft() {
  return (getDistanceLeftUp() < 15 || getDistanceLeftDown() < 15);
}

bool SensorMap::heatVictim(double desire) {
    double current_angle_x = logic.getAngleBNOX();
    desire = control.getDesiredAngle(desire);
    double new_desire_left = 0;
    double new_desire_right = 0;

    if (temperatureCelcius(temperature_sensor_right) > 28 and temperatureCelcius(temperature_sensor_right) < 40) {
        motors.stopEngines();
        logic.turnLED();
        delay(5000);
        new_desire_left = control.getNewDesireLeft(desire);
        motors.turnDegrees(new_desire_left);
        delay(2000);
        dispenser.dropOneKitRight();
        delay(2000);
        new_desire_right = control.getNewDesireRight(new_desire_left);
        motors.turnDegrees(new_desire_right);
        return 1; // Victim Right
    }
    else if (temperatureCelcius(temperature_sensor_left) > 28 and temperatureCelcius(temperature_sensor_left) < 40) {
            motors.stopEngines();
            logic.turnLED();
            delay(5000);
            new_desire_right = control.getNewDesireRight(desire);
            motors.turnDegrees(new_desire_right);
            delay(2000);
            dispenser.dropOneKitLeft();
            delay(2000);
            new_desire_left = control.getNewDesireLeft(new_desire_right);
            motors.turnDegrees(new_desire_left);
            return 2; // Victim Left
    }
}

/*bool SensorMap::visualVictim() {
  
}

bool SensorMap::colouredVictim() {
}
*/

float SensorMap::temperatureCelcius(int mlx) {
  int dev = mlx;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;
  
  i2c_start_wait(dev+I2C_WRITE);
  i2c_write(0x07);
  
  i2c_rep_start(dev+I2C_READ);
  data_low = i2c_readAck();
  data_high = i2c_readAck();
  pec = i2c_readNak();
  i2c_stop();
  
  double tempFactor = 0.02;
  double tempData = 0x0000;
  int frac;
  
  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor)-0.01;
  float celcius = tempData - 273.15;
  
  return celcius;
}