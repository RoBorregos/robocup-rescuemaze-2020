/* Roborregos 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement() {}

void Movement::advanceP(const double desire) {
  encouder_count_left = 0;
  encouder_count_right = 0;

  do {
      double pwm_right_enginees = bno_.getPwmBNORight(desire); // Negative.
      double pwm_left_enginees = bno_.getPwmBNOLeft(desire); // Positive. 
      if (pwm_left_enginees > 1) {
          pwm_left_enginees = kLimit_inf_pwm;
          control.getPwm(pwm_left_enginees);
      }

      else if (pwm_right_enginees < 0) {
          pwm_right_enginees = kLimit_inf_pwm;
          control.getPwm(pwm_right_enginees);
      }
      forwardPwm(pwm_right_enginees, pwm_left_enginees);
    }
    while (encouder_count_left < kUnitLimit and encouder_count_right < kUnitLimit);
}

void Movement::moveBackP(const double desire) {
  encouder_count_left = 0;
  encouder_count_right = 0;

  do {
      double pwm_right_enginees = bno_.getPwmBNORight(desire); // Negative.
      double pwm_left_enginees = bno_.getPwmBNOLeft(desire); // Positive. 
      if (pwm_left_enginees > 1) {
          pwm_left_enginees = kLimit_inf_pwm;
          control.getPwm(pwm_left_enginees);
      }

      else if (pwm_right_enginees < 0) {
          pwm_right_enginees = kLimit_inf_pwm;
          control.getPwm(pwm_right_enginees);
      }
      backwardPwm(pwm_right_enginees, pwm_left_enginees);
    }
    while (encouder_count_left < kUnitLimit and encouder_count_right < kUnitLimit);
}

void Movement::turnLeft(const uint8_t speed) { 
    digitalWrite(kMotorLeftForward2, HIGH);
    analogWrite(kMotorLeftForward1, speed);
    digitalWrite(kMotorLeftBack1, HIGH);
    analogWrite(kMotorLeftBack2, speed);
    digitalWrite(kMotorRightForward2, HIGH);
    analogWrite(kMotorRightForward1, speed);
    digitalWrite(kMotorRightBack2, HIGH);
    analogWrite(kMotorRightBack1, speed);
}

void Movement::turnRight(const uint8_t speed) { 
    digitalWrite(kMotorLeftForward2, LOW);
    analogWrite(kMotorLeftForward1, speed);
    digitalWrite(kMotorLeftBack1, LOW);
    analogWrite(kMotorLeftBack2, speed);
    digitalWrite(kMotorRightForward2, LOW);
    analogWrite(kMotorRightForward1, speed);
    digitalWrite(kMotorRightBack2, LOW);
    analogWrite(kMotorRightBack1, speed);  
}

void Movement::turnDegrees(double desire) {
  double speed = 0;
  double error = 0;
  double current_angle_x = bno_.getAngleX();
  desire = control.getDesiredAngle(desire);
  
  do{
    error = control.getAngleError(current_angle_x, desire);
    Serial.println(error);
    speed = kPTurns * error;
    
    control.getPwm(speed); // Verify to the pwm stay in the range.
    if (error < 0) { 
      turnLeft(speed);
    }   
    else {
      turnRight(speed);
    } 
  }
  while ( error < -(kRange_error) || error > kRange_error); // Asigne a range to stop the robot.
  stopEngines();
}

void Movement::stopEngines() { 
    digitalWrite(kMotorLeftForward1, HIGH);
    digitalWrite(kMotorLeftForward2, HIGH);
    digitalWrite(kMotorLeftBack1, HIGH);
    digitalWrite(kMotorLeftBack2, HIGH);
    digitalWrite(kMotorRightForward1, HIGH);
    digitalWrite(kMotorRightForward2, HIGH);
    digitalWrite(kMotorRightBack1, HIGH);
    digitalWrite(kMotorRightBack2, HIGH);

    delay(kTimeToStop);

    digitalWrite(kMotorLeftForward1, LOW);
    digitalWrite(kMotorLeftForward2, LOW);
    digitalWrite(kMotorLeftBack1, LOW);
    digitalWrite(kMotorLeftBack2, LOW);
    digitalWrite(kMotorRightForward1, LOW);
    digitalWrite(kMotorRightForward2, LOW);
    digitalWrite(kMotorRightBack1, LOW);
    digitalWrite(kMotorRightBack2, LOW); 
}

void Movement::fastForward() {
  forwardPwm(kLimit_sup_pwm, kLimit_sup_pwm);
}

void Movement::fastBackward() {
    backwardPwm(kLimit_sup_pwm, kLimit_sup_pwm);
}

void Movement::forwardPwm(const uint8_t pwm_right, const uint8_t pwm_left) {
    digitalWrite(kMotorLeftForward2, LOW);
    analogWrite(kMotorLeftForward2, pwm_left);
    digitalWrite(kMotorLeftBack1, LOW);
    analogWrite(kMotorLeftBack2, pwm_left);
    digitalWrite(kMotorRightForward1, LOW);
    analogWrite(kMotorRightForward2, pwm_right);
    digitalWrite(kMotorRightBack1, LOW);
    analogWrite(kMotorRightBack2, pwm_right);
}

void Movement::backwardPwm(const uint8_t pwm_right, const uint8_t pwm_left) {
    digitalWrite(kMotorLeftForward2, HIGH);
    analogWrite(kMotorLeftForward2, pwm_left);
    digitalWrite(kMotorLeftBack1, HIGH);
    analogWrite(kMotorLeftBack2, pwm_left);
    digitalWrite(kMotorRightForward1, HIGH);
    analogWrite(kMotorRightForward2, pwm_right);
    digitalWrite(kMotorRightBack1, HIGH);
    analogWrite(kMotorRightBack2, pwm_right);
}

void Movement::moveBack() {
    digitalWrite(kMotorLeftForward1, LOW);
    analogWrite(kMotorLeftForward2, kLimit_sup_pwm);
    digitalWrite(kMotorLeftBack2, LOW);
    analogWrite(kMotorLeftBack1, kLimit_sup_pwm);
    digitalWrite(kMotorRightForward2, LOW);
    analogWrite(kMotorRightForward1, kLimit_sup_pwm);
    digitalWrite(kMotorRightBack2, LOW);
    analogWrite(kMotorRightBack1, kLimit_sup_pwm);
}