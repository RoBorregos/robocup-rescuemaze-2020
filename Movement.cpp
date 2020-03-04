/* ROBORREGOS MAZE 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement(BNO *bno, Control *system, Motors *robot) {
  bno_ = bno;
  system_ = system;
  robot_ = robot;
}

void Movement::advancePID(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left = 0;
  encoder_count_right = 0;

  do {
    system_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    system_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);
    double pwm_right_enginees = pwm_right_final_bno + pwm_right_final_ultrasonic; // Negative.
    double pwm_left_enginees = pwm_left_final_bno + pwm_left_final_ultrasonic;    // Positive.

    if (pwm_left_enginees > 0) {
      pwm_right_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_left_enginees);
    }
    else if (pwm_right_enginees < 0) {
      pwm_right_enginees = -(pwm_right_enginees);
      pwm_left_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_right_enginees);
    }
    robot_->forwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left < kUnitLimit && encoder_count_right < kUnitLimit);
}

void Movement::advancePIDSwitches(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left = 0;
  encoder_count_right = 0;

  do {
    system_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    system_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);
    double pwm_right_enginees = pwm_right_final_bno + pwm_right_final_ultrasonic; // Negative.
    double pwm_left_enginees = pwm_left_final_bno + pwm_left_final_ultrasonic;    // Positive.

    if (pwm_left_enginees > 0) {
      pwm_right_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_left_enginees);
    }
    else if (pwm_right_enginees < 0) {
      pwm_right_enginees = -(pwm_right_enginees);
      pwm_left_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_right_enginees);
    }
    robot_->forwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left < kUnitLimitSwitch && encoder_count_right < kUnitLimitSwitch);
}

void Movement::moveBackPIDSwitches(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left = 0;
  encoder_count_right = 0;

  do {
    system_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    system_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);
    double pwm_right_enginees = pwm_right_final_bno + pwm_right_final_ultrasonic; // Negative.
    double pwm_left_enginees = pwm_left_final_bno + pwm_left_final_ultrasonic;    // Positive.

    if (pwm_left_enginees > 0) {
      system_->getPwm(pwm_left_enginees);
    }
    else if (pwm_right_enginees < 0) {
      pwm_right_enginees = -(pwm_right_enginees);
      system_->getPwm(pwm_right_enginees);
    }
    robot_->backwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left < kUnitLimitSwitch && encoder_count_right < kUnitLimitSwitch);
}

void Movement::moveBackPID(const double desire) {
  double pwm_left_final_bno;
  double pwm_right_final_bno;
  double pwm_left_final_ultrasonic;
  double pwm_right_final_ultrasonic;
  encoder_count_left = 0;
  encoder_count_right = 0;

  do {
    system_->getPwmBNO(desire, pwm_left_final_bno, pwm_right_final_bno); 
    system_->getPwmUltrasonic(pwm_left_final_ultrasonic, pwm_right_final_ultrasonic);
    double pwm_right_enginees = pwm_right_final_bno + pwm_right_final_ultrasonic; // Negative.
    double pwm_left_enginees = pwm_left_final_bno + pwm_left_final_ultrasonic;    // Positive.

    if (pwm_left_enginees > 0) {
      pwm_right_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_left_enginees);
    }
    else if (pwm_right_enginees < 0) {
      pwm_right_enginees = -(pwm_right_enginees);
      pwm_left_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_right_enginees);
    }
    robot_->backwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left < kUnitLimitSwitch && encoder_count_right < kUnitLimitSwitch);
}

void Movement::turnDegrees(double desire) {
  double speed = 0;
  double error = 0;
  desire = system_->getDesiredAngle(desire);

  do {
    error = system_->getAngleError(bno_->getAngleX(), desire);
    Serial.println(error);
    speed = kPTurns * error;
    system_->getPwm(speed); // Verify to the pwm stay in the range.
    if (error < 0) {
      robot_->turnLeft(speed);
    }
    else {
      robot_->turnRight(speed);
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
