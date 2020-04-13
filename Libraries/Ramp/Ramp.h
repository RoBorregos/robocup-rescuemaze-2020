// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// This class is intended to stock the coordinates of the ramps of the maze.
// (Not tested).

#ifndef Ramp_h
#define Ranp_h

#include "Coord.h"

class Ramp {
    private:
        uint8_t zone1, row1, column1;
        uint8_t zone2, row2, column2;
    public:
        // Constructor with parameters (only the necessary ones).
        Ramp(const uint8_t zone1, const uint8_t row1, const uint8_t column1, const uint8_t zone2);
        // Returns Zone1. 
        uint8_t getZone1();
        // Returns Row1.
        uint8_t getRow1();
        // Returns Column1.
        uint8_t getColumn1();
        // Returns Zone2. 
        uint8_t getZone2();
        // Returns Row2.
        uint8_t getRow2();
        // Returns Column2.
        uint8_t getColumn2();
        // Updates coords of the ramp according to the movement of the robot in the maze.
        void moveCoords(const uint8_t zone, const char row_or_column);
};

#endif