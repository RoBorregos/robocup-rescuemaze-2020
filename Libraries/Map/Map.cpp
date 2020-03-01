#include <Map.h>
#include "TVector.h"

Map::Map(Tile initialTile) {
  current_row_ = 0;
  current_column_ = 0;
  number_of_rows_ = 1;
  number_of_columns_ = 1;
  orientation_ = 1;
  TVector<Tile> row;

  row.pushAsLast(initialTile);
  map_.pushAsLast(row);
}

uint8_t Map::numberOfRows() {
  return number_of_rows_;
}

uint8_t Map::numberOfColumns() {
  return number_of_columns_;
}

uint8_t Map::currentRow() {
  return current_row_;
}

uint8_t Map::currentColumn() {
  return current_column_;
}

uint8_t Map::getOrientation() {
  return orientation_;
}

uint8_t Map::getUnvisitedTiles() {
  unvisited_tiles_ = 0;
  for (int row = 0 ; row < number_of_rows_ ; row++) {
    for (int column = 0 ; column < number_of_columns_ ; column++) {
      if (!map_[row][column].isVisited() &&
          map_[row][column].isAccessible() &&
          !map_[row][column].isBlack()) {
        unvisited_tiles_++;
      }
    }
  }
  return unvisited_tiles_;
}

Tile Map::getTile(const uint8_t row, const uint8_t column) {
  return map_[row][column];
}

Tile Map::currTile() {
  return map_[current_row_][current_column_];
}

Tile Map::northTile() {
  return map_[current_row_ - 1][current_column_];
}

Tile Map::eastTile() {
  return map_[current_row_][current_column_ + 1];
}

Tile Map::southTile() {
  return map_[current_row_ + 1][current_column_];
}

Tile Map::westTile() {
  return map_[current_row_][current_column_ - 1];
}

void Map::setTile(Tile tile, char position) {
  if (position == '0') {
      map_[current_row_][current_column_] = tile;
  }
  else if (position == 'N') {
      map_[current_row_ - 1][current_column_] = tile;
  }
  else if (position == 'E') {
      map_[current_row_][current_column_ + 1] = tile;
  }
  else if (position == 'S') {
      map_[current_row_ + 1][current_column_] = tile;
  }
  else if (position == 'W') {
      map_[current_row_][current_column_ - 1] = tile;
  }
}

void Map::addRowFirst(Tile newTile) {
  TVector<Tile> newRow;
  Tile emptyTile;
  
  for(int column = 0 ; column < number_of_columns_ ; column++) {
    newRow.pushAsLast(emptyTile);
  }

  map_.pushAsLast(newRow);
  current_row_++;
  number_of_rows_++;

  for(int row = number_of_rows_ - 1 ; row > 0 ; row--) {
    map_[row] = map_[row - 1];
  }

  newRow[current_column_] = newTile;
  map_[0] = newRow;
}

void Map::addRowLast(Tile newTile) {
  TVector<Tile> newRow;
  Tile emptyTile;
  
  for(int i = 0 ; i < number_of_columns_ ; i++) {
    newRow.pushAsLast(emptyTile);
  }

  newRow[current_column_] = newTile;
  map_.pushAsLast(newRow);

  number_of_rows_++;
}

void Map::addColumnFirst(Tile newTile) {
  Tile emptyTile;

  for (int row = 0 ; row < number_of_rows_ ; row++) {
    map_[row].pushAsLast(emptyTile);

    for (int column = number_of_columns_ ; column > 0 ; column--) {
      map_[row][column] = map_[row][column - 1];
    }

    map_[row][0] = emptyTile;
  }

  map_[current_row_][0] = newTile;

  current_column_++;
  number_of_columns_++;
}

void Map::addColumnLast(Tile newTile) {
  Tile emptyTile;

  for (int i = 0 ; i < number_of_rows_ ; i++) {
    map_[i].pushAsLast(emptyTile);
  }

  map_[current_row_][current_column_ + 1] = newTile;

  number_of_columns_++;
}

void Map::moveNorth() {
  orientation_ = 1;
  current_row_--;
}

void Map::moveEast() {
  orientation_ = 2;
  current_column_++;
}

void Map::moveSouth() {
  orientation_ = 3;
  current_row_++;
}

void Map::moveWest() {
  orientation_ = 4;
  current_column_--;
}