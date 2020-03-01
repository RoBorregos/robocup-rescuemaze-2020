/* ROBORREGOS MAZE 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
 * To get more information, go to Movement.h file.
*/
#include "Movement.h"

Movement::Movement() {}

Movement::Movement(BNO *bno, Control *system, Motors *robot)
{
  bno_ = bno;
  system_ = system;
  robot_ = robot;
}

void Movement::advancePID(const double desire)
{
  encoder_count_left = 0;
  encoder_count_right = 0;

  do
  {
    double pwm_right_enginees = system_->getPwmBNORight(desire) + system_->getPwmUltrasonicRight(); // Negative.
    double pwm_left_enginees = system_->getPwmBNOLeft(desire) + system_->getPwmUltrasonicLeft();    // Positive.
    if (pwm_left_enginees > 1)
    {
      pwm_right_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_left_enginees);
    }
    else if (pwm_right_enginees < 0)
    {
      pwm_left_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_right_enginees);
    }
    robot_->forwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left < kUnitLimit && encoder_count_right < kUnitLimit);
}

void Movement::moveBackPID(const double desire)
{
  encoder_count_left = 0;
  encoder_count_right = 0;

  do
  {
    double pwm_right_enginees = system_->getPwmBNORight(desire); // Negative.
    double pwm_left_enginees = system_->getPwmBNOLeft(desire);   // Positive.
    if (pwm_left_enginees > 1)
    {
      pwm_left_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_left_enginees);
    }
    else if (pwm_right_enginees < 0)
    {
      pwm_right_enginees = Common::kLimitInfPwm;
      system_->getPwm(pwm_right_enginees);
    }
    robot_->backwardPwm(pwm_right_enginees, pwm_left_enginees);
  } while (encoder_count_left < kUnitLimit && encoder_count_right < kUnitLimit);
}

void Movement::turnDegrees(double desire)
{
  double speed = 0;
  double error = 0;
  desire = system_->getDesiredAngle(desire);

  do
  {
    error = system_->getAngleError(bno_->getAngleX(), desire);
    Serial.println(error);
    speed = kPTurns * error;
    system_->getPwm(speed); // Verify to the pwm stay in the range.
    if (error < 0)
    {
      robot_->turnLeft(speed);
    }
    else
    {
      robot_->turnRight(speed);
    }
  } while (error < -(kRange_error) || error > kRange_error); // Asigne a range to stop the robot.
  robot_->stopEngines();
}