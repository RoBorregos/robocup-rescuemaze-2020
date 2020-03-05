/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This motors class has all the functions to move 
 * the robot.
 * To get more information, go to Motors.h file.
*/
#include "Motors.h"

Motors::Motors() {}

void Motors::turnLeft(const uint8_t speed) {
    digitalWrite(kMotorLeftForward2, speed);
    digitalWrite(kMotorLeftForward1, LOW);
    digitalWrite(kMotorLeftBack1, LOW);
    digitalWrite(kMotorLeftBack2, speed);
    digitalWrite(kMotorRightForward2, speed);
    digitalWrite(kMotorRightForward1, LOW);
    digitalWrite(kMotorRightBack2, LOW);
    digitalWrite(kMotorRightBack1, speed);
}

void Motors::turnRight(const uint8_t speed) {
    digitalWrite(kMotorLeftForward2, LOW);
    digitalWrite(kMotorLeftForward1, speed);
    digitalWrite(kMotorLeftBack1, speed);
    digitalWrite(kMotorLeftBack2, LOW);
    digitalWrite(kMotorRightForward2, LOW);
    digitalWrite(kMotorRightForward1, speed);
    digitalWrite(kMotorRightBack2, speed);
    digitalWrite(kMotorRightBack1, LOW);
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
    forwardPwm(Common::kLimitSupPwm, Common::kLimitSupPwm);
}

void Motors::fastBackward() {
    backwardPwm(Common::kLimitSupPwm, Common::kLimitSupPwm);
}

void Motors::forwardPwm(const uint8_t pwm_right, const uint8_t pwm_left) {
    digitalWrite(kMotorLeftForward2, LOW);
    digitalWrite(kMotorLeftForward1, pwm_left);
    digitalWrite(kMotorLeftBack1, pwm_left);
    digitalWrite(kMotorLeftBack2, LOW);
    digitalWrite(kMotorRightForward2, pwm_right);
    digitalWrite(kMotorRightForward1, LOW);
    digitalWrite(kMotorRightBack2, LOW);
    digitalWrite(kMotorRightBack1, pwm_right);
}

void Motors::backwardPwm(const uint8_t pwm_right, const uint8_t pwm_left) {
    digitalWrite(kMotorLeftForward2, pwm_left);
    digitalWrite(kMotorLeftForward1, LOW);
    digitalWrite(kMotorLeftBack1, LOW);
    digitalWrite(kMotorLeftBack2, pwm_left);
    digitalWrite(kMotorRightForward2, LOW);
    digitalWrite(kMotorRightForward1, pwm_right);
    digitalWrite(kMotorRightBack2, pwm_right);
    digitalWrite(kMotorRightBack1, LOW);
}

void Motors::initializeMotors() {
  pinMode(kMotorLeftForward1, OUTPUT);
  pinMode(kMotorLeftForward2, OUTPUT);
  pinMode(kMotorLeftBack1, OUTPUT);
  pinMode(kMotorLeftBack2, OUTPUT);
  pinMode(kMotorRightForward1, OUTPUT);
  pinMode(kMotorRightForward2, OUTPUT);
  pinMode(kMotorRightBack1, OUTPUT);
  pinMode(kMotorRightBack2, OUTPUT);
}
