#include "DropKit.h"
#include "BNO.h"
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Control.h"
#include "Multiplexor.h"

/*void calibrationAll() {
  const int kDelayAfterBNO = 2700; 
  const int LED = 4;
  bno.begin();
  bno.setExtCrystalUse(true);
  lcd.init();
  lcd.backlight();
  sensor->writeLCDdown("LCD ready");
  lcd.clear();
  lcd.setCursor(0,0);
  
  while(bno_->orientationStatus() != 3) {
    lcd.setCursor(6,0);
    lcd.print("I´m not ready");
  }
  lcd.setCursor(6,1);
  lcd.print("I´m ready");

  delay(kDelayAfterBNO);

  pinMode(LED, INPUT); 
  digitalWrite(LED, LOW);
  
  pinMode(move->kMotorLeftForward1, OUTPUT);
  pinMode(move->kMotorLeftForward2, OUTPUT);
  pinMode(move->kMotorLeftBack1, OUTPUT);
  pinMode(move->kMotorLeftBack2, OUTPUT);
  pinMode(move->kMotorRightForward1, OUTPUT);
  pinMode(move->kMotorRightForward2, OUTPUT);
  pinMode(move->kMotorRightBack1, OUTPUT);
  pinMode(move->kMotorRightBack2, OUTPUT);

  sensors_event_t event;
  bno.getEvent(&event);
}
*/

void setup()
{
  Serial.begin(9600);
  Multiplexor multi;
  Multiplexor *const i2c = &multi;

  SensorMap sensorr;
  SensorMap *const sensor = &sensorr;

  Screen Lcd;
  Screen const screen = Lcd;

  Movement motors;
  Movement const motor = motors;

  DropKit kit;
  DropKit const dispenser = kit;

  Control controll;
  Control const control = controll;

  BNO degrees;
  BNO *const bno = &degrees;

  Motors robo;
  Motors *const robot = &robo;
  //robot.orientationStatus();
  //robot.calibrationAll();
}

void loop()
{
  //robot.turnDegrees(robot.E);
}