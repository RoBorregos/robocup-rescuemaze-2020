/* ROBORREGOS MAZE 2020.
 * This Control class has all the fuctions to get
 * the angle, desired angle and sensors error.
 * This class is so necessary to move the robot to
 * The correct direction of the robot.
 * To get more information, go to Control.h file.
*/
#include "Control.h"

Control::Control() {}

Control::Control(BNO *bno, SensorMap *map)
{
  bno_ = bno;
  map_ = map;
}

double Control::getDesiredAngle(double desire)
{
  if (bno_->getAngleX() > kDegrees180)
  {
    desire -= bno_->getDifferenceWithZero();
    if (desire < 0)
    {
      desire += kDegrees360;
    }
    else
    {
      desire = desire;
    }
  }
  else
  {
    desire -= bno_->getDifferenceWithZero();
  }
  return desire;
}

double Control::getAngleError(const double current_angle_x, const double desire)
{
  double error = desire - current_angle_x;

  if (error < -kDegrees180)
  {
    error += kDegrees360;
  }
  else if (error > kDegrees180)
  {
    error -= kDegrees360;
  }
  return error;
}

double Control::getErrorUltrasonic(const double current_distance, const double desire_ultrasonic)
{
  return (current_distance - desire_ultrasonic);
}

void Control::getPwm(double &speed)
{
  if (speed < Common::kLimitInfPwm)
  {
    speed = Common::kLimitInfPwm;
  }
  else if (speed > Common::kLimitSupPwm)
  {
    speed = Common::kLimitSupPwm;
  }
}

double Control::getNewDesireLeft(double new_desire)
{
  new_desire -= kDegrees90;
  if (new_desire < 0)
  {
    new_desire += kDegrees360;
  }
  return new_desire;
}

double Control::getNewDesireRight(double new_desire)
{
  new_desire += kDegrees90;
  if (new_desire > kDegrees360)
  {
    new_desire -= kDegrees360;
  }
  return new_desire;
}

bool Control::detectRamp()
{
  return (bno_->getAngleY() < -kLimitInfDegrees 
  && bno_->getAngleY() > -kLimitSupDegrees 
  && bno_->getAngleZ() < kRangeAngleZ 
  && bno_->getAngleZ() > -kRangeAngleZ);
}

bool Control::bumperLevel1()
{
  return ((bno_->getAngleY() < -kLimitInfBumper1 
  && bno_->getAngleY() > -kLimitSupBumper1) 
  && (bno_->getAngleZ() > kRangeAngleZ 
  || bno_->getAngleZ() < -kRangeAngleZ));
}

bool Control::bumperLevel2()
{
  return ((bno_->getAngleY() < -kLimitSupBumper1 
  && bno_->getAngleY() > -kLimitSupBumper2) 
  && (bno_->getAngleZ() > kRangeAngleZ 
  || bno_->getAngleZ() < -kRangeAngleZ));
}

bool Control::bumperLevel3()
{
  return ((bno_->getAngleY() < -kLimitSupBumper2 
  && bno_->getAngleY() > -kLimitSupBumper3) 
  && (bno_->getAngleZ() > kRangeAngleZ 
  || bno_->getAngleZ() < -kRangeAngleZ));
}

double Control::getPwmBNOLeft(const double desire) // Positive.
{ 
  double pwm_left = 0;
  double pwm_right = 0;
  double pwm_left_final = 0;
  double pwm_right_final = 0;
  double pwm_right_BNO = 0;
  double pwm_left_BNO = 0;
  const double errorBNO = getAngleError(bno_->getAngleX(), desire);

  if (errorBNO > 0)
  {
    pwm_right = Common::kLimitInfPwm;
    pwm_left_BNO = kPAdvance * errorBNO;
    pwm_left_final = pwm_left_BNO;
  }
  else
  {
    pwm_left = Common::kLimitInfPwm;
    pwm_right_BNO = kPAdvance * errorBNO;
    pwm_right_final = pwm_right_BNO;
  }
  return pwm_left_final;
}

double Control::getPwmBNORight(const double desire) // Negative.
{ 
  double pwm_left = 0;
  double pwm_right = 0;
  double pwm_left_final = 0;
  double pwm_right_final = 0;
  double pwm_right_BNO = 0;
  double pwm_left_BNO = 0;
  const double errorBNO = getAngleError(bno_->getAngleX(), desire);

  if (errorBNO > 0)
  {
    pwm_right = Common::kLimitInfPwm;
    pwm_left_BNO = kPAdvance * errorBNO;
    pwm_left_final = pwm_left_BNO;
  }
  else
  {
    pwm_left = Common::kLimitInfPwm;
    pwm_right_BNO = kPAdvance * errorBNO;
    pwm_right_final = pwm_right_BNO;
  }
  return pwm_right_final;
}

double Control::getPwmUltrasonicLeft() // Positive.
{ 
  double pwm_right = 0;
  double pwm_left = 0;
  const double desire_ultrasonic = 5;
  double pwm_right_ultrasonic_right_up = 0;
  double pwm_left_ultrasonic_right_up = 0;
  double pwm_left_ultrasonic_right_down = 0;
  double pwm_right_ultrasonic_right_down = 0;
  double pwm_left_ultrasonic_left_up = 0;
  double pwm_right_ultrasonic_left_up = 0;
  double pwm_left_ultrasonic_left_down = 0;
  double pwm_right_ultrasonic_left_down = 0;

  if (map_->getDistanceRightUp() < map_->kDistanceWall)
  {
    const double error_right_up = getErrorUltrasonic(map_->getDistanceRightUp(), desire_ultrasonic);
    if (error_right_up > 0)
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_right_up = kPAdvance * error_right_up;
    }
    else
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_right_up = kPAdvance * error_right_up;
    }
  }

  if (map_->getDistanceRightDown() < map_->kDistanceWall)
  {
    const double error_right_down = getErrorUltrasonic(map_->getDistanceRightDown(), desire_ultrasonic);
    if (error_right_down > 0)
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_right_down = kPAdvance * error_right_down;
      pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
    }
    else
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_right_down = kPAdvance * error_right_down;
      pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
    }
  }

  if (map_->getDistanceLeftUp() < map_->kDistanceWall)
  {
    const double error_left_up = getErrorUltrasonic(map_->getDistanceLeftUp(), desire_ultrasonic);
    if (error_left_up > 0)
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_left_up = kPAdvance * error_left_up;
      pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
    }
    else
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_left_up = kPAdvance * error_left_up;
      pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
    }
  }

  if (map_->getDistanceLeftDown() < map_->kDistanceWall)
  {
    const double error_left_down = getErrorUltrasonic(map_->getDistanceLeftDown(), desire_ultrasonic);
    if (error_left_down > 0)
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_left_down = kPAdvance * error_left_down;
      pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
    }
    else
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_left_down = kPAdvance * error_left_down;
      pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
    }
  }
  return pwm_left_ultrasonic_left_down;
}

double Control::getPwmUltrasonicRight() // Negative.
{ 
  double pwm_left = 0;
  double pwm_right = 0;
  const double desire_ultrasonic = 5;
  double pwm_right_ultrasonic_right_up = 0;
  double pwm_left_ultrasonic_right_up = 0;
  double pwm_left_ultrasonic_right_down = 0;
  double pwm_right_ultrasonic_right_down = 0;
  double pwm_left_ultrasonic_left_up = 0;
  double pwm_right_ultrasonic_left_up = 0;
  double pwm_left_ultrasonic_left_down = 0;
  double pwm_right_ultrasonic_left_down = 0;

  if (map_->getDistanceRightUp() < map_->kDistanceWall)
  {
    const double error_right_up = getErrorUltrasonic(map_->getDistanceRightUp(), desire_ultrasonic);
    if (error_right_up > 0)
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_right_up = kPAdvance * error_right_up;
    }
    else
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_right_up = kPAdvance * error_right_up;
    }
  }

  if (map_->getDistanceRightDown() < map_->kDistanceWall)
  {
    const double error_right_down = getErrorUltrasonic(map_->getDistanceRightDown(), desire_ultrasonic);
    if (error_right_down > 0)
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_right_down = kPAdvance * error_right_down;
      pwm_right_ultrasonic_right_down += pwm_right_ultrasonic_right_up;
    }
    else
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_right_down = kPAdvance * error_right_down;
      pwm_left_ultrasonic_right_down += pwm_left_ultrasonic_right_up;
    }
  }

  if (map_->getDistanceLeftUp() < map_->kDistanceWall)
  {
    const double error_left_up = getErrorUltrasonic(map_->getDistanceLeftUp(), desire_ultrasonic);
    if (error_left_up > 0)
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_left_up = kPAdvance * error_left_up;
      pwm_right_ultrasonic_left_up += pwm_right_ultrasonic_right_down;
    }
    else
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_left_up = kPAdvance * error_left_up;
      pwm_left_ultrasonic_left_up += pwm_left_ultrasonic_right_down;
    }
  }

  if (map_->getDistanceLeftDown() < map_->kDistanceWall)
  {
    const double error_left_down = getErrorUltrasonic(map_->getDistanceLeftDown(), desire_ultrasonic);
    if (error_left_down > 0)
    {
      pwm_right = Common::kLimitInfPwm;
      pwm_left_ultrasonic_left_down = kPAdvance * error_left_down;
      pwm_left_ultrasonic_left_down += pwm_left_ultrasonic_left_up;
    }
    else
    {
      pwm_left = Common::kLimitInfPwm;
      pwm_right_ultrasonic_left_down = kPAdvance * error_left_down;
      pwm_right_ultrasonic_left_down += pwm_right_ultrasonic_left_up;
    }
  }
  return pwm_right_ultrasonic_left_down;
}

void Control::turnLED()
{
  digitalWrite(LED, HIGH);
  delay(kTime100ms);
  digitalWrite(LED, LOW);
  delay(kTime100ms);
}