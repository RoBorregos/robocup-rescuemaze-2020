/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This Control class has all the fuctions to get
 * the angle, desired angle and sensors error.
 * This class is so necessary to move the robot to
 * The correct direction of the robot.
 * To get more information, go to Control.h file.
*/
#include "Control.h"

Control::Control(BNO *bno, SensorMap *map) {
  bno_ = bno;
  map_ = map;
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
}

double Control::getDesiredAngle(double desire) {
  if (bno_->getAngleX() > kDegrees180) {
  }
    if (desire < 0) {
      desire += kDegrees360;
    } else {
    desire -= bno_->getDifferenceWithZero();
  }
  return desire;
}

double Control::getAngleError(const double current_angle_x, const double desire) {
  double error = desire - current_angle_x;

  if (error < -kDegrees180) {
    error += kDegrees360;
  } else if (error > kDegrees180) {
    error -= kDegrees360;
  }
  return error;
}

double Control::getErrorUltrasonic(const double current_distance, const double desire_ultrasonic) {
  return (current_distance - desire_ultrasonic);
}

void Control::getPwm(double &pwm) {
  if (pwm < Common::kLimitInfPwmTurns) {
    pwm = Common::kLimitInfPwmTurns;
  } else if (pwm > Common::kLimitSupPwmTurns) {
    pwm = Common::kLimitSupPwmTurns;
  }
}

double Control::getNewDesireLeft(double new_desire) {
  new_desire -= kDegrees90;
  if (new_desire < 0) {
    new_desire += kDegrees360;
  }
  return new_desire;
}

double Control::getNewDesireRight(double new_desire) {
  new_desire += kDegrees90;
  if (new_desire > kDegrees360) {
    new_desire -= kDegrees360;
  }
  return new_desire;
}

bool Control::detectRamp() {
  const double current_angle_z = bno_->getAngleZ();

  return (current_angle_z < -(kLimitInfDegrees));
}

bool Control::bumperLevel1() {
  const double current_angle_y = bno_->getAngleY();
  const double current_angle_z = bno_->getAngleZ();

  return ((current_angle_y < -kLimitInfBumper1 
  && current_angle_y > -kLimitSupBumper1) 
  && (current_angle_z > kRangeAngleZ 
  || current_angle_z < -kRangeAngleZ));
}

bool Control::bumperLevel2() {
  const double current_angle_y = bno_->getAngleY();
  const double current_angle_z = bno_->getAngleZ();

  return ((current_angle_y < -kLimitSupBumper1 
  && current_angle_y > -kLimitSupBumper2) 
  && (current_angle_z > kRangeAngleZ 
  || current_angle_z < -kRangeAngleZ));
}

bool Control::bumperLevel3() {
  const double current_angle_y = bno_->getAngleY();
  const double current_angle_z = bno_->getAngleZ();

  return ((current_angle_y < -kLimitSupBumper2 
  && current_angle_y > -kLimitSupBumper3)
  && (current_angle_z > kRangeAngleZ 
  || current_angle_z < -kRangeAngleZ));
}

double Control::getPwmBNO(const double desire, double &pwm_left_final, double &pwm_right_final) {
  const double errorBNO = getAngleError(bno_->getAngleX(), desire);

  if (errorBNO > 0) {
    pwm_left_final = Common::kLimitInfPwmAdvance;
    pwm_right_final = Common::kLimitInfPwmAdvance + Common::kPAdvance * errorBNO;
  } else {
    pwm_right_final = Common::kLimitInfPwmAdvance;
    pwm_left_final = Common::kLimitInfPwmAdvance + Common::kPAdvance * (-(errorBNO));
  }
}

double Control::getPwmUltrasonic(double &pwm_left_final, double &pwm_right_final) {
  const double desire_ultrasonic = 5;
  double pwm_right_ultrasonic_right_up = 0;
  double pwm_left_ultrasonic_right_up = 0;
  double pwm_left_ultrasonic_right_down = 0;
  double pwm_right_ultrasonic_right_down = 0;
  double pwm_left_ultrasonic_left_up = 0;
  double pwm_right_ultrasonic_left_up = 0;
  double pwm_left_ultrasonic_left_down = 0;
  double pwm_right_ultrasonic_left_down = 0;
  const double get_distance_right_up = map_->getDistanceRightUp();
  const double get_distance_right_down = map_->getDistanceRightDown();
  const double get_distance_left_up = map_->getDistanceLeftUp();
  const double get_distance_left_down = map_->getDistanceLeftDown();

  
  if (get_distance_right_up < map_->kDistanceWall) {
    const double error_right_up = getErrorUltrasonic(get_distance_right_up, desire_ultrasonic);
    if (error_right_up > 0) {
      pwm_right_ultrasonic_right_up = Common::kLimitInfPwmAdvance;
      pwm_left_ultrasonic_right_up = Common::kPAdvance * error_right_up; // Positive.
    } else {
      pwm_left_ultrasonic_right_up = Common::kLimitInfPwmAdvance;
      pwm_right_ultrasonic_right_up = Common::kPAdvance * error_right_up; // Negative.
    }
  }

  if (get_distance_right_down < map_->kDistanceWall) {
    const double error_right_down = getErrorUltrasonic(get_distance_right_down, desire_ultrasonic);
    if (error_right_down > 0) {
      pwm_left_ultrasonic_right_down = Common::kLimitInfPwmAdvance;
      pwm_right_ultrasonic_right_down = Common::kPAdvance * error_right_down;
      if (get_distance_right_up < map_->kDistanceWall) {
        pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up; // Positive.
        pwm_right_final = pwm_right_ultrasonic_right_down;
      }
    } else {
      pwm_right_ultrasonic_right_down = Common::kLimitInfPwmAdvance;
      pwm_left_ultrasonic_right_down = Common::kPAdvance * error_right_down;
      
      if (get_distance_right_up < map_->kDistanceWall) {
        pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up; // Negative.
        pwm_left_final = pwm_left_ultrasonic_right_down;
      }
    }
  }

  if (get_distance_left_up < map_->kDistanceWall) {
    const double error_left_up = getErrorUltrasonic(get_distance_left_up, desire_ultrasonic);
    if (error_left_up > 0) {
      pwm_left_ultrasonic_left_up = Common::kLimitInfPwmAdvance;
      pwm_right_ultrasonic_left_up = Common::kPAdvance * error_left_up; 
      if (get_distance_right_down < map_->kDistanceWall) {
        pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down; // Positive.
        pwm_right_final = pwm_right_ultrasonic_left_up;
      } else if (get_distance_right_up < map_->kDistanceWall) {
        pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_up;
        pwm_right_final = pwm_left_ultrasonic_left_up;
      }
    } else {
      pwm_right_ultrasonic_left_up = Common::kLimitInfPwmAdvance;
      pwm_left_ultrasonic_left_up = Common::kPAdvance * error_left_up;
      
      if (get_distance_right_down < map_->kDistanceWall) {
        pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
        pwm_left_final = pwm_left_ultrasonic_left_up;
      } else if (get_distance_right_up < map_->kDistanceWall) {
        pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_up;
        pwm_left_final = pwm_left_ultrasonic_left_up;
      }
    }
  }

  if (get_distance_left_down < map_->kDistanceWall) {
    const double error_left_down = getErrorUltrasonic(get_distance_left_down, desire_ultrasonic);
    if (error_left_down > 0) {
      pwm_right_ultrasonic_left_down = Common::kLimitInfPwmAdvance;
      pwm_left_ultrasonic_left_down = Common::kPAdvance * error_left_down;
      if (get_distance_left_up < map_->kDistanceWall) {
        pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
        pwm_left_final = pwm_left_ultrasonic_left_down;
      } else if (get_distance_right_down < map_->kDistanceWall) {
        pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_right_down;
        pwm_left_final = pwm_left_ultrasonic_left_down;
      } else if (get_distance_right_up < map_->kDistanceWall) {
        pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_right_up;
        pwm_left_final = pwm_left_ultrasonic_left_down;
      }
    } else {
      pwm_left_ultrasonic_left_down = Common::kLimitInfPwmAdvance;
      pwm_right_ultrasonic_left_down = Common::kPAdvance * error_left_down;
      if (get_distance_left_up < map_->kDistanceWall) {
        pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
        pwm_right_final = pwm_right_ultrasonic_left_down;
      } else if (get_distance_right_down < map_->kDistanceWall) {
        pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_right_down;
        pwm_right_final = pwm_right_ultrasonic_left_down;
      } else if (get_distance_right_up <map_->kDistanceWall) {
        pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_right_up;
        pwm_right_final = pwm_right_ultrasonic_left_down;
      }
    }
  }
  if (get_distance_left_up > map_->kDistanceWall && get_distance_right_down > map_->kDistanceWall && get_distance_right_up > map_->kDistanceWall && get_distance_left_down) {
    pwm_right_final = 0;
    pwm_left_final = 0;
  }
}