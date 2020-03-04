/* ROBORREGOS MAZE 2020.
 * This Movement class has all the functions
 * To move the robot to anywhere on the map.
 * This class works with all robot enginees.
*/
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "arduino.h"
#include "BNO.h"
#include "Control.h"
#include "Motors.h"
#include "Common.h"

class Movement {

  public:
    Movement(BNO *bno, Control *system, Motors *robot);
    // Move the robot forward with PID.
    void advancePID(const double desire);
    // Move the robot forward with PID until get out of the obstacle.
    void advancePIDSwitches(const double desire);
    // Move the robot backwards with PID.
    void moveBackPID(const double desire);
    // Move the robot backward with PID until get out of the obstacle.
    void moveBackPIDSwitches(const double desire);
    // Turn left or right depending on the desired angle.
    void turnDegrees(const double desire);
    // Left corner switch on, the robot straightnes.
    void leftCornerCrash(const double desire, uint8_t straighten_angle);
    // Right corner switch on, the robot straightens.
    void rightCornerCrash(const double desire, uint8_t straighten_angle); 
    // Left switch on, the robot straightens.
    void leftCrash(const double desire, uint8_t straighten_angle);
    // Right switch on, the robot straightens.
    void rightCrash(const double desire, uint8_t straighten_angle);

    const int kUnitLimit = 500;
    const int kUnitLimitSwitch = 200;

    // Turns.
    const double kPTurns = 1.07;
    const double kITurns = 2.91;
    const double kDTurns = 3.33;

    const uint8_t kRange_error = 2;

    const uint8_t N = 0;
    const uint8_t E = 90;
    const uint8_t S = 180;
    const int W = 270;

    volatile uint16_t encoder_count_left;
    volatile uint16_t encoder_count_right;

  private:
    BNO *bno_;
    Control *system_;
    Motors *robot_;
};
#endif