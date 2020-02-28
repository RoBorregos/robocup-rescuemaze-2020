/* Roborregos 2020.
 * This Control class has all the fuctions to get
 * the angle, desired angle and sensors error.
 * This class is so necessary to move the robot to
 * The correct direction of the robot.
 * To get more information, go to Control.h file.
*/
#include "Control.h"

Control::Control(){}

Control::Control(BNO *c, SensorMap *s) {
  bno_ = c;
  map_ = s;
}

double Control::getDesiredAngle(double desire) {
  double initial_difference = bno_->getDifferenceWithZero(); 
  double current_angle_x = bno_->getAngleX();
  
  if (current_angle_x > kDegrees180) {
    desire -= initial_difference;
    if (desire < 0) {
      desire += kDegrees360;
    }
    
    else{
      desire = desire;
    }
  }

  else {
    desire -= initial_difference;
  }
  
  return desire;
}

double Control::getAngleError(const double current_angle_x, const double desire){
  double error = desire - current_angle_x;
  
  if (error < -kDegrees180) {
     error += kDegrees360;
   }
    
  else if (error > kDegrees180) {
    error -= kDegrees360;
  }
  
  return error;
}

double Control::getErrorUltrasonic(const double current_distance, const double desire_ultrasonic) {
  return(current_distance - desire_ultrasonic);
}

void Control::getPwm(double &speed) { 
  if (speed < Common::kLimit_inf_pwm) {
    speed = Common::kLimit_inf_pwm;
  }
  
  else if (speed > Common::kLimit_sup_pwm) {
    speed = Common::kLimit_sup_pwm;
  }
}

double Control::getNewDesireLeft(double new_desire) {
  new_desire = new_desire - kDegrees90;
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
  return (bno_->getAngleY() < -kLimitInfDegrees 
  && bno_->getAngleY() > -kLimitSupDegrees 
  && bno_->getAngleZ() < kRangeAngleZ 
  && bno_->getAngleZ() > -kRangeAngleZ);
}

bool Control::bumperLevel1() {
  if (bno_->getAngleY() < -kLimitInfBumper1 && bno_->getAngleY() > -kLimitSupBumper1) {
    if (bno_->getAngleZ() > kRangeAngleZ || bno_->getAngleZ() < -kRangeAngleZ) {
      return true; // It's a bumper level 1.
    }
    else {
      return false; // It's a ramp.
    }
  }
  else {
    return false; // It's another bumper level.
  }
}

bool Control::bumperLevel2() {
  if(bno_->getAngleY() < -kLimitSupBumper1 && bno_->getAngleY() > -kLimitSupBumper2) {
    if(bno_->getAngleZ() > kRangeAngleZ || bno_->getAngleZ() < -kRangeAngleZ) {
      return true; // It's a bumper level 2.
    }
    else {
    return false; // It's a ramp.
    }
  }
  else {
  return false; // It's another bumper level.
  }
}

bool Control::bumperLevel3() {
  if(bno_->getAngleY() < -kLimitSupBumper2 && bno_->getAngleY() > -kLimitSupBumper3) {
    if (bno_->getAngleZ() > kRangeAngleZ || bno_->getAngleZ() < -kRangeAngleZ) {
      return true; // It's a bumper level 3.
    }
    return false; //It's a ramp.
  } 
  return false; // It's another bumper level.
}

double Control::getPwmBNOLeft(const double desire) { // Positive.
    double pwm_left = 0;
    double pwm_right = 0;
    double pwm_left_final = 0;
    double pwm_right_final = 0;
    double pwm_right_BNO = 0;
    double pwm_left_BNO = 0;
    double current_angle_x = bno_->getAngleX(); 
    const double errorBNO = getAngleError(current_angle_x, desire);

    if (errorBNO > 0) {
        pwm_right = Common::kLimit_inf_pwm;
        pwm_left_BNO = kPAdvance * errorBNO;
        pwm_left_final = pwm_left_BNO + getPwmUltrasonicLeft();
        }
    else {
        pwm_left = Common::kLimit_inf_pwm;
        pwm_right_BNO = kPAdvance * errorBNO;
        pwm_right_final = pwm_right_BNO + getPwmUltrasonicRight();;
    }
    return pwm_left_final;
}

double Control::getPwmBNORight(const double desire) { // Negative.
    double pwm_left = 0;
    double pwm_right = 0;
    double pwm_left_final = 0;
    double pwm_right_final = 0;
    double pwm_right_BNO = 0;
    double pwm_left_BNO = 0;
    double current_angle_x = bno_->getAngleX(); 
    const double errorBNO = getAngleError(current_angle_x, desire);

    if (errorBNO > 0) {
        pwm_right = Common::kLimit_inf_pwm;
        pwm_left_BNO = kPAdvance * errorBNO;
        pwm_left_final = pwm_left_BNO + getPwmUltrasonicLeft();
        }
    else {
        pwm_left = Common::kLimit_inf_pwm;
        pwm_right_BNO = kPAdvance * errorBNO;
        pwm_right_final = pwm_right_BNO + getPwmUltrasonicRight();;  
    }
    return pwm_right_final;
}

double Control::getPwmUltrasonicLeft() { // Positive.
    double pwm_right = 0;
    double pwm_left = 0;
    const double desire_ultrasonic = 15;
    double pwm_right_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_down = 0;
    double pwm_right_ultrasonic_right_down = 0;
    double pwm_left_ultrasonic_left_up = 0;
    double pwm_right_ultrasonic_left_up = 0;
    double pwm_left_ultrasonic_left_down = 0;
    double pwm_right_ultrasonic_left_down = 0; 
    const double current_distance_right_down = map_->getDistanceRightDown();
    const double current_distance_left_up = map_->getDistanceLeftUp();
    const double current_distance_left_down = map_->getDistanceLeftDown();
    const double current_distance_right_up = map_->getDistanceRightUp();

    if (current_distance_right_up < map_->kDistanceWall) {
        const double error_right_up = getErrorUltrasonic(current_distance_right_up, desire_ultrasonic);
        if (error_right_up > 0) {
          pwm_right = Common::kLimit_inf_pwm;
          pwm_left_ultrasonic_right_up = kPAdvance * error_right_up;
        }

        else {
          pwm_left = Common::kLimit_inf_pwm;
          pwm_right_ultrasonic_right_up = kPAdvance * error_right_up;
        }
    }

    if (current_distance_right_down < map_->kDistanceWall) {
        const double error_right_down = getErrorUltrasonic(current_distance_right_down, desire_ultrasonic);
        if (error_right_down > 0) {
            pwm_left = Common::kLimit_inf_pwm;
            pwm_right_ultrasonic_right_down = kPAdvance * error_right_down;
            pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
        }

        else {
            pwm_right = Common::kLimit_inf_pwm;
            pwm_left_ultrasonic_right_down = kPAdvance * error_right_down;
            pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
        }
    }

    if (current_distance_left_up < map_->kDistanceWall) {
        const double error_left_up = getErrorUltrasonic(current_distance_left_up, desire_ultrasonic);
        if (error_left_up > 0) {
            pwm_left = Common::kLimit_inf_pwm;
            pwm_right_ultrasonic_left_up = kPAdvance * error_left_up;
            pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
        }

        else {
            pwm_right = Common::kLimit_inf_pwm;
            pwm_left_ultrasonic_left_up = kPAdvance * error_left_up;
            pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
        }
    }

    if (current_distance_left_down < map_->kDistanceWall) {
        const double error_left_down = getErrorUltrasonic(current_distance_left_down, desire_ultrasonic);
        if (error_left_down > 0) {
            pwm_right = Common::kLimit_inf_pwm;
            pwm_left_ultrasonic_left_down = kPAdvance * error_left_down;
            pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
        }

        else {
            pwm_left = Common::kLimit_inf_pwm;
            pwm_right_ultrasonic_left_down = kPAdvance * error_left_down;
            pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
        }
  }
  return pwm_left_ultrasonic_left_down;
}

double Control::getPwmUltrasonicRight() { // Negative.
    double pwm_left = 0;
    double pwm_right = 0;
    const double desire_ultrasonic = 15;
    double pwm_right_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_down = 0;
    double pwm_right_ultrasonic_right_down = 0;
    double pwm_left_ultrasonic_left_up = 0;
    double pwm_right_ultrasonic_left_up = 0;
    double pwm_left_ultrasonic_left_down = 0;
    double pwm_right_ultrasonic_left_down = 0; 
    const double current_distance_right_down = map_->getDistanceRightDown();
    const double current_distance_left_up = map_->getDistanceLeftUp();
    const double current_distance_left_down = map_->getDistanceLeftDown();
    const double current_distance_right_up = map_->getDistanceRightUp();

    if (current_distance_right_up < map_->kDistanceWall) {
        const double error_right_up = getErrorUltrasonic(current_distance_right_up, desire_ultrasonic);
        if (error_right_up > 0) {
          pwm_right = Common::kLimit_inf_pwm;
          pwm_left_ultrasonic_right_up = kPAdvance * error_right_up;
        }

        else {
          pwm_left = Common::kLimit_inf_pwm;
          pwm_right_ultrasonic_right_up = kPAdvance * error_right_up;
        }
    }

    if (current_distance_right_down < map_->kDistanceWall) {
        const double error_right_down = getErrorUltrasonic(current_distance_right_down, desire_ultrasonic);
        if (error_right_down > 0) {
            pwm_left = Common::kLimit_inf_pwm;
            pwm_right_ultrasonic_right_down = kPAdvance * error_right_down;
            pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
        }

        else {
            pwm_right = Common::kLimit_inf_pwm;
            pwm_left_ultrasonic_right_down = kPAdvance * error_right_down;
            pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
        }
    }

    if (current_distance_left_up < map_->kDistanceWall) {
        const double error_left_up = getErrorUltrasonic(current_distance_left_up, desire_ultrasonic);
        if (error_left_up > 0) {
            pwm_left = Common::kLimit_inf_pwm;
            pwm_right_ultrasonic_left_up = kPAdvance * error_left_up;
            pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
        }

        else {
            pwm_right = Common::kLimit_inf_pwm;
            pwm_left_ultrasonic_left_up = kPAdvance * error_left_up;
            pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
        }
    }

    if (current_distance_left_down < map_->kDistanceWall) {
        const double error_left_down = getErrorUltrasonic(current_distance_left_down, desire_ultrasonic);
        if (error_left_down > 0) {
            pwm_right = Common::kLimit_inf_pwm;
            pwm_left_ultrasonic_left_down = kPAdvance * error_left_down;
            pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
        }

        else {
            pwm_left = Common::kLimit_inf_pwm;
            pwm_right_ultrasonic_left_down = kPAdvance * error_left_down;
            pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
        }
  }
  return pwm_right_ultrasonic_left_down;
}

void Control::turnLED() {
    digitalWrite(LED, HIGH);
    delay(kTime100ms);
    digitalWrite(LED, LOW);
    delay(kTime100ms);
}