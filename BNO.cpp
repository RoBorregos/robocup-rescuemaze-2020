/* Roborregos Maze 2020
 * This BNO class has all functions to get
 * the robot angle, write on screen, and
 * calibrate all sensors.
 * To get more information, go to BNO.h file.
*/
#include "BNO.h"

LiquidCrystal_I2C lcd(0x27,20,4);

BNO::BNO(){
    bno = Adafruit_BNO055();
}

double BNO::getDifferenceWithZero() { 
  double error_generated = 0;
  
  double current_angle_x = getAngleBNOX();
  if (current_angle_x >= 180) {
    error_generated = (360 - current_angle_x);
  }
  
  else {
    error_generated = current_angle;
    error_generated = -(error_generated);
  }
  
  return error_generated;
}

double BNO::getAngleBNOX() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.x;
}

double BNO::getAngleBNOY() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.y;
}

double BNO::getAngleBNOZ() { 
  sensors_event_t event;
  bno.getEvent(&event);
  
  return event.orientation.z;
}

void BNO::LCDCalibration() {
  lcd.init(); 
  lcd.backlight();
  lcd.print("Hola Mundo");
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(kTimeToPrint);
}

void BNO::BNOCalibration() {
  Serial.println("Orientation Sensor Test"); Serial.println("");   
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(kTimeToPrintLCD); 
  
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

void BNO::calibrationAll() {
  bno.begin();
  bno.setExtCrystalUse(true);
  lcd.init();
  lcd.backlight();
  writeLCDdown("LCD ready");
  lcd.clear();
  lcd.setCursor(0,0);
  
  while(orientationStatus() != 3) {
    lcd.setCursor(6,0);
    lcd.print("I´m not ready");
  }
  lcd.setCursor(6,1);
  lcd.print("I´m ready");

  delay(kDelayAfterBNO);

  pinMode(LED, INPUT); 
  digitalWrite(LED, LOW);
  
  pinMode(motors.kMotorLeftForward1, OUTPUT);
  pinMode(motors.kMotorLeftForward2, OUTPUT);
  pinMode(motors.kMotorLeftBack1, OUTPUT);
  pinMode(motors.kMotorLeftBack2, OUTPUT);
  pinMode(motors.kMotorRightForward1, OUTPUT);
  pinMode(motors.kMotorRightForward2, OUTPUT);
  pinMode(motors.kMotorRightBack1, OUTPUT);
  pinMode(motors.kMotorRightBack2, OUTPUT);

  sensors_event_t event;
  bno.getEvent(&event);
}

void BNO::writeNumLCD(const int num) {
  lcd.clear();
  lcd.print(num);
}

void BNO::writeLyricsLCD(const char letra) {
  lcd.print(letra);
}

void BNO::writeLCD(const String sE1, const String sE2) {
  lcd.clear();
  lcd.print(sE1);
  lcd.setCursor(0, 1);
  lcd.print(sE2);
}

void BNO::writeLCDdown(const String sE1) {
  lcd.setCursor(0, 1);
  lcd.print(sE1);
}

void BNO::printLocation(const double x, const double y, const double z) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.setCursor(2,0);
  lcd.print(x);

   lcd.setCursor(7,0);
  lcd.print("Y:");
  lcd.setCursor(9,0);
  lcd.print(y);

  lcd.setCursor(11,0);
  lcd.print("Z:");
  lcd.setCursor(13,0);
  lcd.print(z);

delay(kTimeSeeLocation);
}

void BNO::turnLED() {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
}