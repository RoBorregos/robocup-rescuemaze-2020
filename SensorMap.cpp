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

double SensorMap::getPwmUltrasonicLeft() { // Positive.
    double pwm_right = 0;
    double pwm_left = 0;
    const double desireUltrasonic = 15;
    double pwm_right_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_down = 0;
    double pwm_right_ultrasonic_right_down = 0;
    double pwm_left_ultrasonic_left_up = 0;
    double pwm_right_ultrasonic_left_up = 0;
    double pwm_left_ultrasonic_left_down = 0;
    double pwm_right_ultrasonic_left_down = 0; 
    const double current_distance_right_down = sensor.getDistanceRightDown();
    const double current_distance_left_up = sensor.getDistanceLeftUp();
    const double current_distance_left_down = sensor.getDistanceLeftDown();
    const double current_distance_right_up = sensor.getDistanceRightUp();

    if (current_distance_right_up < kDistanceWall) {
        const double error_right_up = control.getErrorUltrasonic(current_distance_right_up, desireUltrasonic);
        if (error_right_up > 0) {
          pwm_right = motors.kLimit_inf_pwm;
          pwm_left_ultrasonic_right_up = motors.kPAdvance * error_right_up;
        }

        else {
          pwm_left = motors.kLimit_inf_pwm;
          pwm_right_ultrasonic_right_up = motors.kPAdvance * error_right_up;
        }
    }

    if (current_distance_right_down < kDistanceWall) {
        const double error_right_down = control.getErrorUltrasonic(current_distance_right_down, desireUltrasonic);
        if (error_right_down > 0) {
            pwm_left = motors.kLimit_inf_pwm;
            pwm_right_ultrasonic_right_down = motors.kPAdvance * error_right_down;
            pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
        }

        else {
            pwm_right = motors.kLimit_inf_pwm;
            pwm_left_ultrasonic_right_down = motors.kPAdvance * error_right_down;
            pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
        }
    }

    if (current_distance_left_up < kDistanceWall) {
        const double error_left_up = control.getErrorUltrasonic(current_distance_left_up, desireUltrasonic);
        if (error_left_up > 0) {
            pwm_left = motors.kLimit_inf_pwm;
            pwm_right_ultrasonic_left_up = motors.kPAdvance * error_left_up;
            pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
        }

        else {
            pwm_right = motors.kLimit_inf_pwm;
            pwm_left_ultrasonic_left_up = motors.kPAdvance * error_left_up;
            pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
        }
    }

    if (current_distance_left_down < kDistanceWall) {
        const double error_left_down = control.getErrorUltrasonic(current_distance_left_down, desireUltrasonic);
        if (error_left_down > 0) {
            pwm_right = motors.kLimit_inf_pwm;
            pwm_left_ultrasonic_left_down = motors.kPAdvance * error_left_down;
            pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
        }

        else {
            pwm_left = motors.kLimit_inf_pwm;
            pwm_right_ultrasonic_left_down = motors.kPAdvance * error_left_down;
            pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
        }
  }
  return pwm_left_ultrasonic_left_down;
}

double SensorMap::getPwmUltrasonicRight() { // Negative.
    double pwm_left = 0;
    double pwm_right = 0;
    const double desireUltrasonic = 15;
    double pwm_right_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_down = 0;
    double pwm_right_ultrasonic_right_down = 0;
    double pwm_left_ultrasonic_left_up = 0;
    double pwm_right_ultrasonic_left_up = 0;
    double pwm_left_ultrasonic_left_down = 0;
    double pwm_right_ultrasonic_left_down = 0; 
    const double current_distance_right_down = sensor.getDistanceRightDown();
    const double current_distance_left_up = sensor.getDistanceLeftUp();
    const double current_distance_left_down = sensor.getDistanceLeftDown();
    const double current_distance_right_up = sensor.getDistanceRightUp();

    if (current_distance_right_up < kDistanceWall) {
        const double error_right_up = control.getErrorUltrasonic(current_distance_right_up, desireUltrasonic);
        if (error_right_up > 0) {
          pwm_right = motors.kLimit_inf_pwm;
          pwm_left_ultrasonic_right_up = motors.kPAdvance * error_right_up;
        }

        else {
          pwm_left = motors.kLimit_inf_pwm;
          pwm_right_ultrasonic_right_up = mototrs.kPAdvance * error_right_up;
        }
    }

    if (current_distance_right_down < kDistanceWall) {
        const double error_right_down = control.getErrorUltrasonic(current_distance_right_down, desireUltrasonic);
        if (error_right_down > 0) {
            pwm_left = motors.kLimit_inf_pwm;
            pwm_right_ultrasonic_right_down = motors.kPAdvance * error_right_down;
            pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
        }

        else {
            pwm_right = motors.kLimit_inf_pwm;
            pwm_left_ultrasonic_right_down = motors.kPAdvance * error_right_down;
            pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
        }
    }

    if (current_distance_left_up < kDistanceWall) {
        const double error_left_up = control.getErrorUltrasonic(current_distance_left_up, desireUltrasonic);
        if (error_left_up > 0) {
            pwm_left = motors.kLimit_inf_pwm;
            pwm_right_ultrasonic_left_up = motors.kPAdvance * error_left_up;
            pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
        }

        else {
            pwm_right = motors.kLimit_inf_pwm;
            pwm_left_ultrasonic_left_up = motors.kPAdvance * error_left_up;
            pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
        }
    }

    if (current_distance_left_down < kDistanceWall) {
        const double error_left_down = control.getErrorUltrasonic(current_distance_left_down, desireUltrasonic);
        if (error_left_down > 0) {
            pwm_right = motors.kLimit_inf_pwm;
            pwm_left_ultrasonic_left_down = motors.kPAdvance * error_left_down;
            pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
        }

        else {
            pwm_left = motors.kLimit_inf_pwm;
            pwm_right_ultrasonic_left_down = motors.kPAdvance * error_left_down;
            pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
        }
  }
  return pwm_right_ultrasonic_left_down;
}

bool SensorMap::checkWallsRight() {
    return (getDistanceRightUp() < kMaxWallDistance || getDistanceRightDown() < kMaxWallDistance);
}

bool SensorMap::checkWallsLeft() {
  return (getDistanceLeftUp() < kMaxWallDistance || getDistanceLeftDown() < kMaxWallDistance);
}

bool SensorMap::heatVictim(double desire) {
    double current_angle_x = bno_.getAngleX();
    desire = control.getDesiredAngle(desire);
    double new_desire_left = 0;
    double new_desire_right = 0;

    if (temperatureCelcius(temperature_sensor_right) > kMinimumTemperature and temperatureCelcius(temperature_sensor_right) < kMaximumTemperature) {
        motors.stopEngines();
        bno_.turnLED();
        delay(kWaitFiveSeconds);
        new_desire_left = control.getNewDesireLeft(desire);
        motors.turnDegrees(new_desire_left);
        delay(kWaitBetweenDropKit);
        dispenser.dropOneKitRight();
        delay(kWaitBetweenDropKit);
        new_desire_right = control.getNewDesireRight(new_desire_left);
        motors.turnDegrees(new_desire_right);
        return 1; // Victim Right
    }

    else if (temperatureCelcius(temperature_sensor_left) > kMinimumTemperature and temperatureCelcius(temperature_sensor_left) < kMaximumTemperature) {
            motors.stopEngines();
            bno_.turnLED();
            delay(kWaitFiveSeconds);
            new_desire_right = control.getNewDesireRight(desire);
            motors.turnDegrees(new_desire_right);
            delay(kWaitBetweenDropKit);
            dispenser.dropOneKitLeft();
            delay(kWaitBetweenDropKit);
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