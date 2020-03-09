/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement(BNO *bno, Control *control, Motors *robot, SensorMap *mapa) {
  bno_ = bno;
  control_ = control;
  robot_ = robot;
  maps_ = mapa;
}

bool Movement::advancePID(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;
  double pwm_left_final = 0;
  double pwm_right_final = 0;
  const double current_angle_x = bno_->getAngleX();
  double errorBNO = 0;

  do {
    control_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    // const double errorBNO = control_->getAngleError(current_angle_x, desire);
    // double pwm_right_enginees = pwm_right_final_bno; // + pwm_right_final_ultrasonic; // Negative.
    // double pwm_left_enginees = pwm_left_final_bno; // + pwm_left_final_ultrasonic;    // Positive.
    control_->getPwm(pwm_right_final_bno);
    control_->getPwm(pwm_left_final_bno); 
    robot_->forwardPwm(pwm_left_final_bno, pwm_right_final_bno);
  } while (encoder_count_right_ < kUnitLimit && encoder_count_left_ < kUnitLimit);
    robot_->stopEngines();

    if (maps_->blackTile()) {
      moveBackPID(desire);
      return true;
    } else {
      return false;
    }
    return false;
  }

// TODO(MarlonB500): Implement the correct values for encoders.
void Movement::advancePIDSwitches(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;

  do {
    control_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    control_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);
    double pwm_right_enginees = pwm_right_final_bno + pwm_right_final_ultrasonic; // Negative.
    double pwm_left_enginees = pwm_left_final_bno + pwm_left_final_ultrasonic;    // Positive.

    if (pwm_left_enginees > 0) {
      pwm_right_enginees = Common::kLimitInfPwm;
      control_->getPwm(pwm_left_enginees);
    } else if (pwm_right_enginees < 0) {
      pwm_right_enginees = -(pwm_right_enginees);
      pwm_left_enginees = Common::kLimitInfPwm;
      control_->getPwm(pwm_right_enginees);
    }
    robot_->forwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left_ < kUnitLimitSwitch && encoder_count_right_ < kUnitLimitSwitch);
}

// TODO(MarlonB500): Implement the correct values for encoders.
void Movement::moveBackPIDSwitches(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;

  do {
    control_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    control_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);
    double pwm_right_enginees = pwm_right_final_bno + pwm_right_final_ultrasonic; // Negative.
    double pwm_left_enginees = pwm_left_final_bno + pwm_left_final_ultrasonic;    // Positive.

    if (pwm_left_enginees > 0) {
      control_->getPwm(pwm_left_enginees);
    } else if (pwm_right_enginees < 0) {
      pwm_right_enginees = -(pwm_right_enginees);
      control_->getPwm(pwm_right_enginees);
    }
    robot_->backwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left_ < kUnitLimitSwitch && encoder_count_right_ < kUnitLimitSwitch);
    robot_->stopEngines();
}

void Movement::moveBackPID(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left_ = 0;
  encoder_count_right_ = 0;
  double pwm_left_final = 0;
  double pwm_right_final = 0;
  const double current_angle_x = bno_->getAngleX();
  double errorBNO = 0;

  do {
    errorBNO = control_->getAngleError(current_angle_x, desire);

    if (errorBNO > 0) {
      pwm_left_final = Common::kLimitInfPwm;
      pwm_right_final = Common::kLimitInfPwm + Common::kPAdvance * errorBNO;
    } else {
      pwm_right_final = Common::kLimitInfPwm;
      pwm_left_final = Common::kLimitInfPwm; + Common::kPAdvance * (-(errorBNO));
  }
    // const double errorBNO = control_->getAngleError(current_angle_x, desire);
    control_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    // control_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);

    // double pwm_right_enginees = pwm_right_final_bno; // + pwm_right_final_ultrasonic; // Negative.
    // double pwm_left_enginees = pwm_left_final_bno; // + pwm_left_final_ultrasonic;    // Positive.
      control_->getPwm(pwm_right_final_bno);
      control_->getPwm(pwm_left_final_bno);
    robot_->backwardPwm(pwm_left_final_bno, pwm_right_final_bno);
  } while (encoder_count_right_ < kUnitLimit && encoder_count_left_ < kUnitLimit);
    robot_->stopEngines();
}

void Movement::turnDegrees(double desire) {
  double pwm = 0;
  double error = 0;
  // desire = control_->getDesiredAngle(desire);

  do {
    error = control_->getAngleError(bno_->getAngleX(), desire);
    pwm = kPTurns * error;
    control_->getPwm(pwm); // Verify to the pwm stay in the range.
    if (error < 0) {
      robot_->turnLeft(pwm);
    } else {
      robot_->turnRight(pwm);
    }
  } while (error < -(kRange_error) || error > kRange_error); // Asigne a range to stop the robot.
    robot_->stopEngines();
}

void Movement::leftCornerCrash(const double desire, uint8_t straighten_angle) {
  double new_desire = desire - straighten_angle;
  if (new_desire > 360) {
    new_desire -= 360;
  }
  moveBackPIDSwitches(new_desire);
  advancePIDSwitches(new_desire);
}

void Movement::rightCornerCrash(const double desire, uint8_t straighten_angle) {
  double new_desire = desire - straighten_angle;
  if (new_desire < 0) {
    new_desire += 360;
  }
  moveBackPIDSwitches(new_desire);
  advancePIDSwitches(new_desire);
}

void Movement::leftCrash(const double desire, uint8_t straighten_angle) {
  double new_desire = desire - straighten_angle;
  if (new_desire > 360) {
    new_desire -= 360;
  }
  moveBackPIDSwitches(new_desire);
  advancePIDSwitches(new_desire);
}

void Movement::rightCrash(const double desire, uint8_t straighten_angle) {
  double new_desire = desire - straighten_angle;
  if (new_desire < 0) {
    new_desire += 360;
  }
  moveBackPIDSwitches(new_desire);
  advancePIDSwitches(new_desire);
}

void Movement::encoderCountLeft() {
  encoder_count_left_++;
}

void Movement::encoderCountRight() {
  encoder_count_right_++;
}

void Movement::initializePinEconders() {
  pinMode(CANAL_A, INPUT);
  pinMode(CANAL_B,INPUT);
}