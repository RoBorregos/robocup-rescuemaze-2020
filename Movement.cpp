/* Roborregos 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement() {}

void Movement::advance(const double desire, const double desireUltrasonic) {
  double encoder1 = 0;
  double encoder2 = 0;
  double pwm_left_final = 0;
  double pwm_right_final = 0;
  double pwm_left = 0;
  double pwm_right = 0;
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
  const double current_distance_right_up = sensor.getDistanceRightUp();
  const double current_distance_right_down = sensor.getDistanceRightDown();
  const double current_distance_left_up = sensor.getDistanceLeftUp();
  const double current_distance_left_down = sensor.getDistanceLeftDown();
  double error_right_up = control.getErrorUltrasonic(current_distance_right_up, desireUltrasonic);
  double error_right_down = control.getErrorUltrasonic(current_distance_right_down, desireUltrasonic);
  double error_left_up = control.getErrorUltrasonic(current_distance_left_up, desireUltrasonic);
  double error_left_down = control.getErrorUltrasonic(current_distance_left_down, desireUltrasonic);
  double current_angle = control.getAngleBNOX();
  double errorBNO = control.getAngleError(current_angle, desire);

  do {
    if (current_distance_right_up < 20) {
        if (error_right_up > 0) {
        pwm_right = kLimit_inf_pwm;
        pwm_left_ultrasonic_right_up = kP2 * error_right_up;
        }
        else {
        pwm_left = kLimit_inf_pwm;
        pwm_right_ultrasonic_right_up = kP2 * error_right_up;
        }
    }
    else {}

    if (current_distance_right_down < 20) {
        if (error_right_down > 0) {
            pwm_left = kLimit_inf_pwm;
            pwm_right_ultrasonic_right_down = kP2 * error_right_down;
            pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
        }
        else {
            pwm_right = kLimit_inf_pwm;
            pwm_left_ultrasonic_right_down = kP2 * error_right_down;
            pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
        }
    }
    else{}

    if (current_distance_left_up) {
        if (error_left_up > 0) {
            pwm_left = kLimit_inf_pwm;
            pwm_right_ultrasonic_left_up = kP2 * error_left_up;
            pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
        }
        else {
            pwm_right = kLimit_inf_pwm;
            pwm_left_ultrasonic_left_up = kP2 * error_left_up;
            pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
        }
    }
    else {}

    if (current_distance_left_down) {
        if (error_left_down > 0) {
            pwm_right = kLimit_inf_pwm;
            pwm_left_ultrasonic_left_down = kP2 * error_left_down;
            pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
        }
        else {
            pwm_left = kLimit_inf_pwm;
            pwm_right_ultrasonic_left_down = kP2 * error_left_down;
            pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
        }
  }
  else {}

    if (errorBNO > 0) {
        pwm_right_final = kLimit_inf_pwm;
        pwm_left_BNO = kP2 * errorBNO;
        pwm_left_final = pwm_left_BNO + pwm_left_ultrasonic_left_down;
        control.getPwm(pwm_left_final);
        }
    else {
        pwm_left_final = kLimit_inf_pwm;
        pwm_right_BNO = kP2 * errorBNO;
        pwm_right_final = pwm_right_BNO + pwm_right_ultrasonic_left_down;
        control.getPwm(pwm_right_final);  
    }
    forwardPwm(pwm_right_final, pwm_left_final);
    }
  while (encoder1 < 500 and encoder2 < 500);
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
  double current_angle = control.getAngleBNOX();
  desire = control.getDesiredAngle(desire);
  
  do{
    error = control.getAngleError(current_angle, desire);
    Serial.println(error);
    vel = kP * error;
    
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
  forwardPwm(kPwm_max, kPwm_max);
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
    analogWrite(kMotorLeftForward2, kPwm_max);
    digitalWrite(kMotorLeftBack2, LOW);
    analogWrite(kMotorLeftBack1, kPwm_max);
    digitalWrite(kMotorRightForward2, LOW);
    analogWrite(kMotorRightForward1, kPwm_max);
    digitalWrite(kMotorRightBack2, LOW);
    analogWrite(kMotorRightBack1, kPwm_max);
}