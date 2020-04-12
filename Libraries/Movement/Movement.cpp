/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement(BNO *bno, Control *control, Motors *motors, SensorMap *sensor, DropKit *dropkit) {
  dispenser_ = dropkit;
  maps_ = sensor;
  bno_ = bno;
  control_ = control;
  motors_ = motors;
}

// TODO(MarlonB500): Include ultrasonic pwm.
void Movement::advancePID(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;

  do {
    dropKitHeatVictimRight();
    dropKitHeatVictimLeft();
    const double errorBNO = control_->getAngleError(bno_->getAngleX(), desire);
    control_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    control_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);
    if (errorBNO > 0) {
      pwm_right_final_bno += pwm_right_final_ultrasonic; 
      control_->getPwm(pwm_right_final_bno);
    } else {
      pwm_left_final_bno += pwm_left_final_ultrasonic;
      control_->getPwm(pwm_left_final_bno);
    }
    motors_->forwardPwm(pwm_right_final_bno, pwm_left_final_bno);
  } while (encoder_count_right_ < kUnitLimit && encoder_count_left_ < kUnitLimit);
    motors_->stopEngines();
}

// TODO(MarlonB500): Include ultrasonic pwm.
void Movement::advancePIDSwitches(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;

  do {
    dropKitHeatVictimRight();
    dropKitHeatVictimLeft();
    const double errorBNO = control_->getAngleError(bno_->getAngleX(), desire);
    control_->getPwmBNOSwitch(desire, pwm_left_final_bno, pwm_right_final_bno); 

    if (errorBNO > 0) {
      //pwm_right_final_bno += pwm_right_final_ultrasonic; 
      control_->getPwm(pwm_right_final_bno);
    } else {
     // pwm_left_final_bno += pwm_left_final_ultrasonic;
      control_->getPwm(pwm_left_final_bno);
    }
    motors_->forwardPwm(pwm_right_final_bno, pwm_left_final_bno);
  } while (encoder_count_right_ < kUnitLimitSwitches && encoder_count_left_ < kUnitLimitSwitches);
  motors_->stopEngines();
}

// TODO(MarlonB500): Include ultrasonic pwm.
void Movement::moveBackPIDSwitches(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;

  do {
    dropKitHeatVictimRight();
    dropKitHeatVictimLeft();
    const double errorBNO = control_->getAngleError(bno_->getAngleX(), desire);
    control_->getPwmBNOSwitch(desire, pwm_left_final_bno, pwm_right_final_bno); 

    if (errorBNO > 0) {
      //pwm_right_final_bno += pwm_right_final_ultrasonic; 
      control_->getPwm(pwm_right_final_bno);
    } else {
     // pwm_left_final_bno += pwm_left_final_ultrasonic;
      control_->getPwm(pwm_left_final_bno);
    }
    motors_->backwardPwm(pwm_right_final_bno, pwm_left_final_bno);
  } while (encoder_count_right_ < kUnitLimitSwitches && encoder_count_left_ < kUnitLimitSwitches);
  motors_->stopEngines();
}

// TODO(MarlonB500): Include a ultrasonic pwm.
void Movement::moveBackPID(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;

  do {
    dropKitHeatVictimRight();
    dropKitHeatVictimLeft();
    const double errorBNO = control_->getAngleError(bno_->getAngleX(), desire);
    control_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    // control_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);

    // double pwm_right_enginees = pwm_right_final_bno; // + pwm_right_final_ultrasonic; // Negative.
    // double pwm_left_enginees = pwm_left_final_bno; // + pwm_left_final_ultrasonic;    // Positive.
    if (errorBNO > 0) {
       control_->getPwm(pwm_right_final_bno);
    } else {
      control_->getPwm(pwm_left_final_bno);
    }
    motors_->backwardPwm(pwm_right_final_bno, pwm_left_final_bno);
  } while (encoder_count_right_ < kUnitLimit && encoder_count_left_ < kUnitLimit);
    motors_->stopEngines();
}

void Movement::turnDegrees(double desire) {
  double pwm = 0;
  double error = 0;
    do {
      dropKitHeatVictimRight();
      dropKitHeatVictimLeft();
      error = control_->getAngleError(bno_->getAngleX(), desire);
      Serial.println(error);
      pwm = kPTurns * error;
      control_->getPwm(pwm); // Verify that the pwm stays in the range.
      if (error < 0) { 
        motors_->turnLeft(pwm);
      } else {
        motors_->turnRight(pwm);
      }
    } while (error < -(kRange_error) || error > kRange_error);
    motors_->stopEngines();
}

bool Movement::dropKitHeatVictimRight() {
  if (maps_->heatVictimRight()) {
    dispenser_->turnLED();
    turnDegrees(90);
    dispenser_->dropOneKitLeft();
    return true;
  }
  return false;
}

bool Movement::dropKitHeatVictimLeft() {
  if (maps_->heatVictimLeft()) {
    dispenser_->turnLED();
    turnDegrees(270);
    dispenser_->dropOneKitLeft();
    return true;
  }
  return false;
}

// TODO:(MarlonB500) In process to get the correct values to detect the victim.
bool Movement::dropKitVisualVictimRight() {
  
}

// TODO:(MarlonB500) In process to get the correct values to detect the victim.
bool Movement::dropKitVisualVictimLeft() {
  
}

// TODO:(MarlonB500) In process to get the correct values to detect the victim.
bool Movement::dropKitColouredVictimRight() {
  
}

// TODO:(MarlonB500) In process to get the correct values to detect the victim.
bool Movement::dropKitColouredVictimLeft() {
  
}

void Movement::encoderCountLeft() {
  ++encoder_count_left_;
}

void Movement::encoderCountRight() {
  ++encoder_count_right_;
}

void Movement::initializePinEconders() {
  pinMode(CANAL_A, INPUT);
  pinMode(CANAL_B,INPUT);
}

bool Movement::passRamp() {
  bool ramp_detected = control_->detectRamp();
  while (ramp_detected) {
    motors_->fastForward();
    ramp_detected = control_->detectRamp();
  }
}