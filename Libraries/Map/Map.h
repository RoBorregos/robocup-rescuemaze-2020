#ifndef Map_h
#define Map_h
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

    void print();
};

Map::Map(Tile initialTile) {
  currRow = 0;
  currColumn = 0;
  numRows = 1;
  numColumns = 1;
  orientation = 1;
  TVector<Tile> row;

  row.pushTop(initialTile);
  map.pushTop(row);
}

uint8_t Map::getRows() {
  return numRows;
}

uint8_t Map::getColumns() {
  return numColumns;
}

uint8_t Map::getCurrRow() {
  return currRow;
}

uint8_t Map::getCurrColumn() {
  return currColumn;
}

uint8_t Map::getOrientation() {
  return orientation;
}

uint8_t Map::getUnvisitedTiles() {
  unvisitedTiles = 0;
  for (int row = 0 ; row < numRows ; row++) {
    for (int column = 0 ; column < numColumns ; column++) {
      if (map[row][column].getVisited() == false && map[row][column].getAccessible() == true && map[row][column].getBlack() == false) {
        unvisitedTiles++;
      }
    }
  }
  return unvisitedTiles;
}

Tile Map::getTile(const uint8_t row, const uint8_t column) {
  return map[row][column];
}

Tile Map::currTile() {
  return map[currRow][currColumn];
}

Tile Map::northTile() {
  return map[currRow - 1][currColumn];
}

Tile Map::eastTile() {
  return map[currRow][currColumn + 1];
}

Tile Map::southTile() {
  return map[currRow + 1][currColumn];
}

Tile Map::westTile() {
  return map[currRow][currColumn - 1];
}

void Map::setTile(Tile tile, char position) {
  if (position == '0') map[currRow][currColumn] = tile;
  else if (position == 'N') map[currRow - 1][currColumn] = tile;
  else if (position == 'E') map[currRow][currColumn + 1] = tile;
  else if (position == 'S') map[currRow + 1][currColumn] = tile;
  else if (position == 'W') map[currRow][currColumn - 1] = tile;
}

void Map::addRowFirst(Tile newTile) {
  TVector<Tile> newRow;
  Tile emptyTile;
  
  for(int column = 0 ; column < numColumns ; column++) {
    newRow.pushTop(emptyTile);
  }

  map.pushTop(newRow);
  currRow++;
  numRows++;

  for(int row = numRows - 1 ; row > 0 ; row--) {
    map[row] = map[row - 1];
  }

  newRow[currColumn] = newTile;
  map[0] = newRow;
}

void Map::addRowLast(Tile newTile) {
  TVector<Tile> newRow;
  Tile emptyTile;
  
  for(int i = 0 ; i < numColumns ; i++) {
    newRow.pushTop(emptyTile);
  }

  newRow[currColumn] = newTile;
  map.pushTop(newRow);

  numRows++;
}

void Map::addColumnFirst(Tile newTile) {
  Tile emptyTile;

  for (int row = 0 ; row < numRows ; row++) {
    map[row].pushTop(emptyTile);

    for (int column = numColumns ; column > 0 ; column--) {
      map[row][column] = map[row][column - 1];
    }

    map[row][0] = emptyTile;
  }

  map[currRow][0] = newTile;

  currColumn++;
  numColumns++;
}

void Map::addColumnLast(Tile newTile) {
  Tile emptyTile;

  for (int i = 0 ; i < numRows ; i++) {
    map[i].pushTop(emptyTile);
  }

  map[currRow][currColumn + 1] = newTile;

  numColumns++;
}

void Map::moveNorth() {
  orientation = 1;
  currRow--;
}

void Map::moveEast() {
  orientation = 2;
  currColumn++;
}

void Map::moveSouth() {
  orientation = 3;
  currRow++;
}

void Map::moveWest() {
  orientation = 4;
  currColumn--;
}

void Map::print() {
  for (int row = 0 ; row < numRows ; row++) {
    for (int column = 0 ; column < numColumns ; column++) {
      map[row][column].print();
      //cout << " ";
      Serial.print(" ");
    }
    //cout << endl;
    Serial.println("");
  }
}

#endif