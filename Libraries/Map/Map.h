#ifndef Map_h
#define Map_h

#include "Arduino.h"
#include "TVector.h"

class Map {
  private:
    uint8_t currRow;
    uint8_t currColumn;
    uint8_t numRows;
    uint8_t numColumns;
    uint8_t orientation;
    uint8_t unvisitedTiles;
    TVector<TVector<Tile> > map;
    
  public:
    Map(Tile initialTile);

    uint8_t getRows();
    uint8_t getColumns();
    uint8_t getCurrRow();
    uint8_t getCurrColumn();
    uint8_t getOrientation();
    uint8_t getUnvisitedTiles();

    Tile getTile(const uint8_t row, const uint8_t column);
    Tile currTile();
    Tile northTile();
    Tile eastTile();
    Tile southTile();
    Tile westTile();

    void setTile(Tile tile, char position);
  
    void addRowFirst(Tile newTile);
    void addRowLast(Tile newTile);
    void addColumnFirst(Tile newTile);
    void addColumnLast(Tile newTile);

    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();
};

#endif