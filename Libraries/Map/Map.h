// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// This class is intended to create an expandable map using a very simple simulation of vectors for Ardunio.
// It helps the robot to get track of the maze and stock important information to be able to move through it.

#ifndef Map_h
#define Map_h

#include "Arduino.h"
#include "TVector.h"

class Map {
  private:
    uint8_t current_row_;
    uint8_t current_column_;
    uint8_t number_of_rows_;
    uint8_t number_of_columns_;
    uint8_t orientation_;
    uint8_t unvisited_tiles_;
    TVector<TVector<Tile> > map_;
    
  public:
    // Constructor
    Map();

    // Returns a uint8_t with the number of rows of the map.
    uint8_t numberOfRows();
    // Returns a uint8_t with the number of columns of the map.
    uint8_t numberOfColumns();
    // Returns a uint8_t representing the row in which the robot is positioned.
    uint8_t currentRow();
    // Returns a uint8_t representing the column in which the robot is positioned.
    uint8_t currentColumn();
    // Returns a uint8_t representing the orientation the robot is looking at (1=North, 2=East, 3=South, 4=West).
    uint8_t getOrientation();
    // Recieves an array of maps and returns a uint8_t with number of tiles that are accessible and the robot has not visited.
    uint8_t getUnvisitedTiles(TVector<Map> tiles_map);

    // Returns the tile ubicated on the specified row and column.
    Tile getTile(const uint8_t row, const uint8_t column);
    // Returns the tile in which the robot is placed at the time the function is called.
    Tile currentTile();
    // Returns the next tile at the North of the one the robot is placed at the time the function is called.
    Tile northTile();
    // Returns the next tile at the East of the one the robot is placed at the time the function is called.
    Tile eastTile();
    // Returns the next tile at the South of the one the robot is placed at the time the function is called.
    Tile southTile();
    // Returns the next tile at the West of the one the robot is placed at the time the function is called.
    Tile westTile();

    // Adds the initial tile to the map.
    void setInitialTile(Tile initial_tile);
    // Receives a tile and places it at the position specified ('N'=North, 'E'=East, 'S'=South, 'W'=West).
    void setTile(Tile tile, char position);

    // Creates a new row containing the tile recieved as a parameter and places that row at the begining of the map.
    void addRowFirst(Tile newTile);
    // Creates a new row containing the tile recieved as a parameter and places that row at the end of the map.
    void addRowLast(Tile newTile);
    // Creates a new column containing the tile recieved as a parameter and places that column at the begining of the map.
    void addColumnFirst(Tile newTile);
    // Creates a new column containing the tile recieved as a parameter and places that column at the end of the map.
    void addColumnLast(Tile newTile);

    // Reduces by one current_row_.
    void moveNorth();
    // Increases by one current_column_.
    void moveEast();
    // Increases by one current_row_.
    void moveSouth();
    // Reduces by one current_column_.
    void moveWest();

    // Returns true if that tile is a candidate to visit.
    bool tileCandidateToVisit(const uint8_t row, const uint8_t column);
};

#endif