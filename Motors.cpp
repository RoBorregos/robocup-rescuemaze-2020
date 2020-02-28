#include "Motors.h"

Motors::Motors() {}

void Motors::turnLeft(const uint8_t speed) { 
    digitalWrite(kMotorLeftForward2, HIGH);
    analogWrite(kMotorLeftForward1, speed);
    digitalWrite(kMotorLeftBack1, HIGH);
    analogWrite(kMotorLeftBack2, speed);
    digitalWrite(kMotorRightForward2, HIGH);
    analogWrite(kMotorRightForward1, speed);
    digitalWrite(kMotorRightBack2, HIGH);
    analogWrite(kMotorRightBack1, speed);
}

void Motors::turnRight(const uint8_t speed) { 
    digitalWrite(kMotorLeftForward2, LOW);
    analogWrite(kMotorLeftForward1, speed);
    digitalWrite(kMotorLeftBack1, LOW);
    analogWrite(kMotorLeftBack2, speed);
    digitalWrite(kMotorRightForward2, LOW);
    analogWrite(kMotorRightForward1, speed);
    digitalWrite(kMotorRightBack2, LOW);
    analogWrite(kMotorRightBack1, speed);  
}

void Motors::stopEngines() { 
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

void Motors::fastForward() {
  forwardPwm(Common::kLimit_sup_pwm, Common::kLimit_sup_pwm);
}

void Motors::fastBackward() {
    backwardPwm(Common::kLimit_sup_pwm, Common::kLimit_sup_pwm);
}

void Motors::forwardPwm(const uint8_t pwm_right, const uint8_t pwm_left) {
    digitalWrite(kMotorLeftForward2, LOW);
    analogWrite(kMotorLeftForward2, pwm_left);
    digitalWrite(kMotorLeftBack1, LOW);
    analogWrite(kMotorLeftBack2, pwm_left);
    digitalWrite(kMotorRightForward1, LOW);
    analogWrite(kMotorRightForward2, pwm_right);
    digitalWrite(kMotorRightBack1, LOW);
    analogWrite(kMotorRightBack2, pwm_right);
}

void Motors::backwardPwm(const uint8_t pwm_right, const uint8_t pwm_left) {
    digitalWrite(kMotorLeftForward2, HIGH);
    analogWrite(kMotorLeftForward2, pwm_left);
    digitalWrite(kMotorLeftBack1, HIGH);
    analogWrite(kMotorLeftBack2, pwm_left);
    digitalWrite(kMotorRightForward1, HIGH);
    analogWrite(kMotorRightForward2, pwm_right);
    digitalWrite(kMotorRightBack1, HIGH);
    analogWrite(kMotorRightBack2, pwm_right);
}

void Motors::moveBack() {
    digitalWrite(kMotorLeftForward1, LOW);
    analogWrite(kMotorLeftForward2, Common::kLimit_sup_pwm);
    digitalWrite(kMotorLeftBack2, LOW);
    analogWrite(kMotorLeftBack1, Common::kLimit_sup_pwm);
    digitalWrite(kMotorRightForward2, LOW);
    analogWrite(kMotorRightForward1, Common::kLimit_sup_pwm);
    digitalWrite(kMotorRightBack2, LOW);
    analogWrite(kMotorRightBack1, Common::kLimit_sup_pwm);
}

