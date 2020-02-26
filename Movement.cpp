/* Roborregos 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement() {}

void Movement::advance(const double desire) {
  eCount1 = 0;
  eCount2 = 0;

  do {
    double pwm_left_final = 0;
    double pwm_right_final = 0;
    double pwm_right_BNO = 0;
    double pwm_left_BNO = 0;
    double pwm_right_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_up = 0;
    double pwm_left_ultrasonic_right_down = 0;
    double pwm_right_ultrasonic_right_down = 0;
    double pwm_left_ultrasonic_left_up = 0;
    double pwm_right_ultrasonic_left_up = 0;
    double pwm_left_ultrasonic_left_down = 0;
    double pwm_right_ultrasonic_left_down = 0;
    double current_angle = logic.getAngleBNOX();  
    const double current_distance_right_down = sensor.getDistanceRightDown();
    const double current_distance_left_up = sensor.getDistanceLeftUp();
    const double current_distance_left_down = sensor.getDistanceLeftDown();
    const double current_distance_right_up = sensor.getDistanceRightUp();

    if (current_distance_right_up < 20) {
        double error_right_up = control.getErrorUltrasonic(current_distance_right_up, desireUltrasonic);
        if (error_right_up > 0) {
          pwm_right_final = kLimit_inf_pwm;
          pwm_left_ultrasonic_right_up = kPAdvance * error_right_up;
        }
        else {
          pwm_left_final = kLimit_inf_pwm;
          pwm_right_ultrasonic_right_up = kPAdvance * error_right_up;
        }
    }
    else {}

    if (current_distance_right_down < 20) {
        double error_right_down = control.getErrorUltrasonic(current_distance_right_down, desireUltrasonic);
        if (error_right_down > 0) {
            pwm_left_final = kLimit_inf_pwm;
            pwm_right_ultrasonic_right_down = kPAdvance * error_right_down;
            pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
        }
        else {
            pwm_right_final = kLimit_inf_pwm;
            pwm_left_ultrasonic_right_down = kPAdvance * error_right_down;
            pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
        }
    }
    else{}

    if (current_distance_left_up < 20) {
        double error_left_up = control.getErrorUltrasonic(current_distance_left_up, desireUltrasonic);
        if (error_left_up > 0) {
            pwm_left_final = kLimit_inf_pwm;
            pwm_right_ultrasonic_left_up = kPAdvance * error_left_up;
            pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
        }
        else {
            pwm_right_final = kLimit_inf_pwm;
            pwm_left_ultrasonic_left_up = kPAdvance * error_left_up;
            pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
        }
    }
    else {}

    if (current_distance_left_down < 20) {
        double error_left_down = control.getErrorUltrasonic(current_distance_left_down, desireUltrasonic);
        if (error_left_down > 0) {
            pwm_right_final = kLimit_inf_pwm;
            pwm_left_ultrasonic_left_down = kPAdvance * error_left_down;
            pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
        }
        else {
            pwm_left_final = kLimit_inf_pwm;
            pwm_right_ultrasonic_left_down = kPAdvance * error_left_down;
            pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
        }
  }
  else {}
    double errorBNO = control.getAngleError(current_angle, desire);
    if (errorBNO > 0) {
        pwm_right_final = kLimit_inf_pwm;
        pwm_left_BNO = kPAdvance * errorBNO;
        pwm_left_final = pwm_left_BNO + pwm_left_ultrasonic_left_down;
        control.getPwm(pwm_left_final);
        }
    else {
        pwm_left_final = kLimit_inf_pwm;
        pwm_right_BNO = kPAdvance * errorBNO;
        pwm_right_final = pwm_right_BNO + pwm_right_ultrasonic_left_down;
        control.getPwm(pwm_right_final);  
    }
    forwardPwm(pwm_right_final, pwm_left_final);
    }
  while (eCount1 < 500 and eCount2 < 500);
  }

double Movement::errorUltrasonicAdvance(const double desireUltrasonic) {
}

void Movement::turnLeft(const uint8_t vel) { 
    digitalWrite(kMotorLeftForward2, HIGH);
    analogWrite(kMotorLeftForward1, vel);
    digitalWrite(kMotorLeftBack1, HIGH);
    analogWrite(kMotorLeftBack2, vel);
    digitalWrite(kMotorRightForward2, HIGH);
    analogWrite(kMotorRightForward1, vel);
    digitalWrite(kMotorRightBack2, HIGH);
    analogWrite(kMotorRightBack1, vel);
}

void Movement::turnRight(const uint8_t vel) { 
    digitalWrite(kMotorLeftForward2, LOW);
    analogWrite(kMotorLeftForward1, vel);
    digitalWrite(kMotorLeftBack1, LOW);
    analogWrite(kMotorLeftBack2, vel);
    digitalWrite(kMotorRightForward2, LOW);
    analogWrite(kMotorRightForward1, vel);
    digitalWrite(kMotorRightBack2, LOW);
    analogWrite(kMotorRightBack1, vel);  
}

void Movement::turnDegrees(double desire) {
  double vel = 0;
  double error = 0;
  double current_angle = logic.getAngleBNOX();
  desire = control.getDesiredAngle(desire);
  
  do{
    error = control.getAngleError(current_angle, desire);
    Serial.println(error);
    vel = kPTurns * error;
    
    control.getPwm(vel); // Verify to the pwm stay in the range.
    if (error < 0) { 
      turnLeft(vel);
    }   
    else {
      turnRight(vel);
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