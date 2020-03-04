/* ROBORREGOS MAZE 2020.
 * This BNO class has all functions to get
 * the robot angle, write on screen, and
 * calibrate all sensors.
 * To get more information, go to BNO.h file.
*/
#include "BNO.h"

BNO::BNO() {
  bno_ = Adafruit_BNO055();
  Serial.println("Orientation Sensor Test");
  Serial.println("");
  bno_.begin();
  if (!bno_.begin()) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  delay(kTimeToPrintBNO);

  bno_.setExtCrystalUse(true);
  sensors_event_t event;
  bno_.getEvent(&event);

  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  delay(kRepose);
}

double BNO::getDifferenceWithZero() {
  double error_generated = 0;
  double current_angle_x = getAngleX();

  if (current_angle_x >= 180) {
    error_generated = (360 - current_angle_x);
  }
  else {
    error_generated = -(current_angle_x);
  }
  return error_generated;
}

double BNO::getAngleX() {
  sensors_event_t event;
  bno_.getEvent(&event);

  return event.orientation.x;
}

double BNO::getAngleY() {
  sensors_event_t event;
  bno_.getEvent(&event);

  return event.orientation.y;
}

double BNO::getAngleZ() {
  sensors_event_t event;
  bno_.getEvent(&event);

  return event.orientation.z;
}

void BNO::BNOCalibration() {
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno_.getCalibration(&system, &gyro, &accel, &mag);

  Serial.print("\t");
  if (!system) {
    Serial.print("! ");
  }

  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.println(mag, DEC);
}

uint8_t BNO::orientationStatus() {
  imu::Vector<3> euler = bno_.getVector(Adafruit_BNO055::VECTOR_EULER);
  uint8_t system, gyro, accel, mag = 0;
  bno_.getCalibration(&system, &gyro, &accel, &mag);

  return mag;
}