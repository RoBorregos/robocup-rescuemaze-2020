// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// This file contains functions that help to make physical tests of the algorythm using the robot.

#include "Arduino.h"
#include "Map.h"
#include "Control.h"
#include "DropKit.h"
#include "Movement.h"
#include "Screen.h"
#include "SensorMap.h"
//#include "Robot.h"

#ifndef PhysicalFunctions_h
#define PhysicalFunctions_h

class PhysicalFunctions {
  public:
    PhysicalFunctions(Movement *movement, SensorMap *map);
    // Functions that moves the robot to the North.
    void moveRobot(const char orientation);
    // Function that moves the position of the robot according to a char vector recieved and returns the resulting tiles map.
    Map followPath(TVector<char> path, Map tiles_map, uint8_t zone);
    // Function that updates the values of the first tile recieved according to the real map.
    Map updateFirstTile(Map tiles_map, uint8_t zone);
    // Function that updates the tiles map according to the real map and returns a tiles_map.
    Map updateTiles(Map tiles_map, const uint8_t zone);

    private:
    Movement *movement_;
    Control *control_;
    Screen *screen_;
    DropKit *dropkit_;
    SensorMap *map_;
};

#endif
  
