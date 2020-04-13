/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This SensorMap class has all the functions
 * To identify anything in the Map, this class
 * Works with all the sensors of the robot.
 * To get more information, go to SensorMap.h file.
*/
#include "SensorMap.h"

Ultrasonic ultrasonicFrontLeft(4, 5);   // Trig, Echo.
Ultrasonic ultrasonicFrontRight(6, 7);  // Trig, Echo.
Ultrasonic ultrasonicRightUp(8, 9);     // Trig, Echo.
Ultrasonic ultrasonicRightDown(10, 11); // Trig, Echo.
Ultrasonic ultrasonicLeftUp(12, 13);    // Trig, Echo.
Ultrasonic ultrasonicLeftDown(14, 15);  // Trig, Echo.
Ultrasonic ultrasonicBack(14, 15);  // Trig, Echo.

SensorMap::SensorMap(Multiplexor *multi) {
  i2c_ = multi;

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
  i2c_->tcaselect(0);
  i2c_init();                               // Inicializar  i2c bus.
  PORTC = (1 << PORTC4) | (1 << PORTC5);
}

int SensorMap::getDistanceFrontLeft() {
  return (ultrasonicFrontLeft.read());
}

int SensorMap::getDistanceFrontRight() {
  return (ultrasonicFrontRight.read());
}

int SensorMap::getDistanceRightUp() {
  return (ultrasonicRightUp.read());
}

int SensorMap::getDistanceRightDown() {
  return (ultrasonicRightDown.read());
}

int SensorMap::getDistanceLeftUp() {
  return (ultrasonicLeftUp.read());
}

int SensorMap::getDistanceLeftDown() {
  return (ultrasonicLeftDown.read());
}

bool SensorMap::checkWallsRight() {
  return (getDistanceRightUp() < kMaxWallDistance || getDistanceRightDown() < kMaxWallDistance);
}

bool SensorMap::checkWallsLeft() {
  return (getDistanceLeftUp() < kMaxWallDistance || getDistanceLeftDown() < kMaxWallDistance);
}

bool SensorMap::checkWallsFront() {
  return(getDistanceFrontLeft() < kMaxWallDistance || getDistanceFrontRight() < kMaxWallDistance);
}

void SensorMap::heatVictimRight() {
  tcaselect(0);
  float celcius2 = temperatureCelcius(temperature_sensor_right);
  if (celcius2 > kMinimumTemperature 
  && celcius2 < kMaximumTemperature) {
    return true;
  } |
  else {
    return false;
  }
}

bool SensorMap::heatVictimLeft() {
  tcaselect(0);
  float celcius1 = temperatureCelcius(temperature_sensor_left);
  if (celcius1 > kMinimumTemperature 
  && celcius1 < kMaximumTemperature) {
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
  return (r < kRangeBlackTile && g < kRangeBlackTile && b < kRangeBlackTile);
}

// TODO(MarlonB500): Add the correct values to detect a silver tile and make them constants.
bool SensorMap::silverTile() {  
  i2c_->tcaselect(kColoSensorID);
  uint16_t r, g, b, c;
  tcs_.getRawData(&r, &g, &b, &c);
  return (r > 254 && g > 254 && b > 254);
}