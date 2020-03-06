// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// This file contains functions that help to make virtual tests of the algorythm without the robot.
// It cointains a char array simulating a physical map.
// 'W' = wall.
// 'B = black Tile.
// 'R' = Robot's current position.
// ' ' = Empty tile.
// '.' = Just to fill spaces.
// '1' = Low tile's difficulty.
// '2' = Medium tile's difficulty.
// '3' = High tile's difficulty.

#include "Map.h"
#include "Arduino.h"

namespace VirtualFunctions {
  // Function that prints the virtual map.
  void printVirtualMap(uint8_t zone);
  // Moves up the position of the robot on the virtual map.
  void moveMapNorth(uint8_t zone);
  // Moves the position of the robot on the virtual map to the right.
  void moveMapEast(uint8_t zone);
  // Moves down the position of the robot on the virtual map.
  void moveMapSouth(uint8_t zone);
  // Moves the position of the robot on the virtual map to the left.
  void moveMapWest(uint8_t zone);
  // Function that prints the robot's internal map.
  void printMap(Map tiles_map);
  // Function that moves the position of the robot in the virtual map according to a char vector recieved and returns the resulting tiles map.
  Map followPathVirtual(TVector<char> path, Map tiles_map, uint8_t zone);
  // Function that updates the values of the first tile recieved according to the virtual map.
  Tile updateFirstTileVirtual(Tile tile, uint8_t zone, const uint8_t x, const uint8_t y);
  // Function that updates the tiles map according to the virtual map and returns a tiles_map.
  Map updateTilesVirtual(Map tiles_map, const uint8_t zone);
}