/* Roborregos Maze 2020
 * This BNO class has all functions to get
 * the robot angle, write on screen, and
 * calibrate all sensors.
 * To get more information, go to BNO.h file.
*/
#include "BNO.h"

BNO::BNO(){
    bno = Adafruit_BNO055();
}

double BNO::getDifferenceWithZero() { 
  double error_generated = 0;
  
  double current_angle_x = getAngleX();
  if (current_angle_x >= 180) {
    error_generated = (360 - current_angle_x);
  }
  
  else {
    error_generated = -current_angle_x;
  }
  
  return error_generated;
}

double BNO::getAngleX() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.x;
}

double BNO::getAngleY() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.y;
}

double BNO::getAngleZ() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.z;
}

double BNO::getPwmBNOLeft(const double desire) { // Positive.
    double pwm_left = 0;
    double pwm_right = 0;
    double pwm_left_final = 0;
    double pwm_right_final = 0;
    double pwm_right_BNO = 0;
    double pwm_left_BNO = 0;
    double current_angle_x = getAngleX(); 
    const double errorBNO = control.getAngleError(current_angle_x, desire);

    if (errorBNO > 0) {
        pwm_right = motors.kLimit_inf_pwm;
        pwm_left_BNO = motors.kPAdvance * errorBNO;
        pwm_left_final = pwm_left_BNO + sensor.getPwmUltrasonicLeft();
        }
    else {
        pwm_left = 145;
        pwm_right_BNO = motors.kPAdvance * errorBNO;
        pwm_right_final = pwm_right_BNO + sensor.getPwmUltrasonicRight();;
    }
    return pwm_left_final;
}

double BNO::getPwmBNORight(const double desire) { // Negative.
    double pwm_left = 0;
    double pwm_right = 0;
    double pwm_left_final = 0;
    double pwm_right_final = 0;
    double pwm_right_BNO = 0;
    double pwm_left_BNO = 0;
    double current_angle_x = getAngleX(); 
    const double errorBNO = control.getAngleError(current_angle_x, desire);

    if (errorBNO > 0) {
        pwm_right = motors.kLimit_inf_pwm;
        pwm_left_BNO = motors.kPAdvance * errorBNO;
        pwm_left_final = pwm_left_BNO + sensor.getPwmUltrasonicLeft();
        }
    else {
        pwm_left = motors.kLimit_inf_pwm;
        pwm_right_BNO = motors.kPAdvance * errorBNO;
        pwm_right_final = pwm_right_BNO + sensor.getPwmUltrasonicRight();;  
    }
    return pwm_right_final;
}

void BNO::BNOCalibration() {
  Serial.println("Orientation Sensor Test"); Serial.println("");   
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(kTimeToPrintBNO); 
  
  bno.setExtCrystalUse(true);
  sensors_event_t event; 
  bno.getEvent(&event);
  
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  
  delay(kRepose);

  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
 
  Serial.print("\t");
  if (!system)
  {
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
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  return mag;
}