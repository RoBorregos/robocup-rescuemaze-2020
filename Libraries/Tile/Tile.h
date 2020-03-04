// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// This class is intended to stock values of each part of the maze in "tiles".
// For example: Location of walls, if the tile is visited, if it is black, etc.

#ifndef Tile_h
#define Tile_h

#include "Arduino.h"

class Tile{
  private:
    char data1_, data2_;

  public:
    Tile();

    // Getters.
    // Data1.
    // It returns true if the tile has already been visited, false otherwise.
    bool isVisited();
    // It returns true if the tile is the one on the initial position, false otherwise.
    bool getStart();
    // It returns true if the tile is a checkpoint, false otherwise.
    bool isCheckpoint();
    // It returns true if the tile is black, false otoherwise.
    bool isBlack();
    // It returns true if the tile has access to the next tile to the North of the map, false otherwise.
    bool ableToGoNorth();
    // It returns true if the tile has access to the next tile to the East of the map, false otherwise.
    bool ableToGoEast();
    // It returns true if the tile has access to the next tile to the South of the map, false otherwise.
    bool ableToGoSouth();
    // It returns true if the tile has access to the next tile to the West of the map, false otherwise.
    bool ableToGoWest();
    // Data2.
    // It returns true if the tile is next to a ramp that goes up, false otherwise.
    bool isRampUp();
    // It returns true if the tile is next to a ramp that goes down, false otherwise.
    bool isRampDown();
    // It returns true if the tile is accessible, false otherwise.
    bool isAccessible();
    // It returns true if a kit has been deployed on the tile, false otherwise.
    bool getDeployedKit();
    // It returns an uint8_t value representing the "weight" that costs passing the tile.
    uint8_t getWeight();

    // Setters.
    // Data1.
    // This value is stored on data1_.
    void setVisited();
    // This value is stored on data1_.
    void setStart();
    // This value is stored on data1_.
    void setCheckpoint();
    // This value is stored on data1_.
    void setBlack();
    // This value is stored on data1_.
    void setNorth();
    // This value is stored on data1_.
    void setEast();
    // This value is stored on data1_.
    void setSouth();
    // This value is stored on data1_.
    void setWest();
    // This value is stored on data1_.
    // Data2.
    // This value is stored on data2_.
    void setRampUp();
    // This value is stored on data2_.
    void setRampDown();
    // This value is stored on data2_.
    void setAccessible();
    // This value is stored on data2_.
    void setUnaccessible();
    // This value is stored on data2_.
    void setDeployedKit();
    // Recieves a const int representing the "weight" that costs to pass the tile and stores it on data2.
    void setWeight(const int weight);

    // Allows to use the operator = between two tiles.
    void operator=(Tile newTile);
};

#endif