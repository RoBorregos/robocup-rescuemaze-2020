#include "SensorMap.h"

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
  double current_distance_right_up = getDistanceRightUp();
  double current_distance_right_down = getDistanceRightDown();
  if (current_distance_right_up < 15 and current_distance_right_down < 15) {
    return true;
  }
  else if (current_distance_right_up > 15 || current_distance_right_down > 15) {
    return false;
  }
}

bool SensorMap::checkWallsLeft() {
  double current_distance_left_up = getDistanceLeftUp();
  double current_distance_left_down = getDistanceLeftDown();
  if (current_distance_left_up < 15 and current_distance_left_down < 15) {
    return true;
  }
  else if (current_distance_left_up > 15 || current_distance_left_down > 15) {
    return false;
  }
}

bool SensorMap::heatVictim(double desire) {
    double current_angle = control.getAngleBNOX();
    desire = control.getDesiredAngle(desire);
    double new_desire_left = 0;
    double new_desire_right = 0;

    if (temperatureCelcius(temperature_sensor_right) > 28 and temperatureCelcius(temperature_sensor_right) < 40) {
        motors.stopEngines();
        turnLED();
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
    else {
        if (temperatureCelcius(temperature_sensor_left) > 28 and temperatureCelcius(temperature_sensor_left) < 40) {
            motors.stopEngines();
            turnLED();
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

void SensorMap::turnLED() {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
}

