/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
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
#include "SensorMap.h"
#include "DropKit.h"

class Movement {

  public:
    Movement(BNO *bno, Control *control, Motors *robot, SensorMap *sensor, DropKit *dropkit);
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
    // Drop a Kit if there is a Heat Victim.
    bool dropKitHeatVictimRight();
    // Drop Kit if there is a Heat Victim.
    bool dropKitHeatVictimLeft();
    // Drop Kit if there is a Visual Victim.
    bool dropKitVisualVictimRight();
    // Drop Kit if there is a Visual Victim.
    bool dropKitVisualVictimLeft();
    // Drop Kit if there is a Coloured Victim.
    bool dropKitColouredVictimRight();
    // Drop Kit if there is a Coloured Victim.
    bool dropKitColouredVictimLeft();
    // Initialize the two encoders.
    void initializePinEconders();
    // Plus one to encoder left.
    void encoderCountLeft();
    // Plus one to encoder right.
    void encoderCountRight();

    const int kUnitLimitSwitches = 630; // 630;
    const int kUnitLimit = 10000;

    // Turns.
    const double kPTurns = 2.65;
    const double kITurns = 2.91;
    const double kDTurns = 3.33;

    const uint8_t kRange_error = 3;

    const uint8_t N = 0;
    const uint8_t E = 90;
    const uint8_t S = 180;
    const int W = 270;

    const uint8_t CANAL_A = 2;
    const uint8_t CANAL_B = 3;

  private:
    DropKit *dispenser_;
    SensorMap *maps_;
    BNO *bno_;
    Control *control_;
    Motors *robot_;
    volatile uint16_t encoder_count_left_;
    volatile uint16_t encoder_count_right_;
};
#endif