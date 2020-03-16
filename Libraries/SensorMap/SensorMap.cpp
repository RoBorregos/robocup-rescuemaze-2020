/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This SensorMap class has all the functions
 * To identify anything in the Map, this class
 * Works with all the sensors of the robot.
 * To get more information, go to SensorMap.h file.
*/
#include "SensorMap.h"

Ultrasonic ultrasonicFront(39, 38);   // Trig, Echo.
Ultrasonic ultrasonicRight(48, 47);     // Trig, Echo.
Ultrasonic ultrasonicLeft(29, 28);    // Trig, Echo..
Ultrasonic ultrasonicBack(27, 26);

SensorMap::SensorMap(Multiplexor *multi) {
  i2c_ = multi;
  Serial.println("Color Sensor Orientation");
  i2c_->tcaselect(3);
  tcs_.begin();
  i2c_->tcaselect(3);
  if (!tcs_.begin())
  {
    Serial.println("Does not work TCS34725 or check your I2C...");
    while (1) {
      delay(kTimeToPrint);
    }
  }
}

int SensorMap::getDistanceFront() {
  return (ultrasonicFront.read());
}

int SensorMap::getDistanceRight() {
  return (ultrasonicRight.read());
}

int SensorMap::getDistanceLeft() {
  return (ultrasonicLeft.read());
}

int SensorMap::getDistanceBack() {
  return (ultrasonicBack.read());
}

bool SensorMap::checkWallsFront() {
  return (getDistanceFront() < kMaxWallDistance);
}

bool SensorMap::checkWallsLeft() {
  return (getDistanceLeft() < kMaxWallDistance);
}

bool SensorMap::checkWallsRight() {
  return (getDistanceRight() < kMaxWallDistance);
}

bool SensorMap::checkWallsBack() {
  return (getDistanceBack() < kMaxWallDistance);
}

bool SensorMap::heatVictimRight() {
  if (temperatureCelcius(temperature_sensor_right) > kMinimumTemperature 
  && temperatureCelcius(temperature_sensor_right) < kMaximumTemperature) {
    return true;
  } else {
    return false;
  }
}

bool SensorMap::heatVictimLeft() {
  if (temperatureCelcius(temperature_sensor_left) > kMinimumTemperature 
  && temperatureCelcius(temperature_sensor_left) < kMaximumTemperature) {
    return true;
  } else {
    return false;
  }
}
/*bool SensorMap::visualVictim() {
  
}

bool SensorMap::colouredVictim() {
}
*/

float SensorMap::temperatureCelcius(const int mlx) {
  int dev = mlx;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;

  i2c_start_wait(dev + I2C_WRITE);
  i2c_write(0x07);

  i2c_rep_start(dev + I2C_READ);
  data_low = i2c_readAck();
  data_high = i2c_readAck();
  pec = i2c_readNak();
  i2c_stop();

  double tempFactor = 0.02;
  double tempData = 0x0000;
  int frac;

  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor) - 0.01;
  float celcius = tempData - 273.15;

  return celcius;
}

bool SensorMap::blackTile() {
  i2c_->tcaselect(kColoSensorID);
  uint16_t r, g, b, c;
  tcs_.getRawData(&r, &g, &b, &c);
  return (r < 0 && g < 0 && b < 0 && c < 0);
}

// TODO(MarlonB500): Add the correct values to detect a silver tile and make them constants.
bool SensorMap::silverTile() {  
  i2c_->tcaselect(kColoSensorID);
  uint16_t r, g, b, c;
  tcs_.getRawData(&r, &g, &b, &c);
  return (r > 254 && g > 254 && b > 254);
}