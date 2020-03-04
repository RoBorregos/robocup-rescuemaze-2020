#include <Map.h>
#include "TVector.h"

Map::Map() {
  current_row_ = 0;
  current_column_ = 0;
  number_of_rows_ = 0;
  number_of_columns_ = 0;
  orientation_ = 1;
}

void Map::setInitialTile(Tile initial_tile) {
  number_of_rows_ = 1;
  number_of_columns_ = 1;

  TVector<Tile> row;
  row.pushAsLast(initial_tile);
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

uint8_t Map::getUnvisitedTiles(TVector<Map> tiles_map) {
  unvisited_tiles_ = 0;
  for(uint8_t zone = 0; zone < tiles_map.getSize(); ++zone) {
    for (uint8_t row = 0; row < number_of_rows_; ++row) {
      for (uint8_t column = 0; column < number_of_columns_; ++column) {
        if (tiles_map[zone].tileCandidateToVisit(row, column)) {
          ++unvisited_tiles_;
        }
      }
    }
  }
  return unvisited_tiles_;
}

Tile Map::getTile(const uint8_t row, const uint8_t column) {
  return map_[row][column];
}

Tile Map::currentTile() {
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
  switch(position) {
    case 'N':
        map_[current_row_ - 1][current_column_] = tile;
      break;
    case 'E':
        map_[current_row_][current_column_ + 1] = tile;
      break;
    case 'S':
        map_[current_row_ + 1][current_column_] = tile;
      break;
    case 'W':
        map_[current_row_][current_column_ - 1] = tile;
      break;
    default:
        map_[current_row_][current_column_] = tile;
  }
}

void Map::addRowFirst(Tile newTile) {
  Tile emptyTile;
  TVector<Tile> newRow(number_of_columns_, emptyTile);

  map_.pushAsLast(newRow);
  ++current_row_;
  ++number_of_rows_;

  for(uint8_t row = number_of_rows_ - 1 ; row > 0 ; --row) {
    map_[row] = map_[row - 1];
  }

  newRow[current_column_] = newTile;
  map_[0] = newRow;
}

void Map::addRowLast(Tile newTile) {
  TVector<Tile> newRow;
  Tile emptyTile;
  
  for(uint8_t i = 0 ; i < number_of_columns_ ; ++i) {
    newRow.pushAsLast(emptyTile);
  }

  newRow[current_column_] = newTile;
  map_.pushAsLast(newRow);

  ++number_of_rows_;
}

void Map::addColumnFirst(Tile newTile) {
  Tile emptyTile;

  for (int row = 0 ; row < number_of_rows_ ; ++row) {
    map_[row].pushAsLast(emptyTile);

    for (int column = number_of_columns_ ; column > 0 ; --column) {
      map_[row][column] = map_[row][column - 1];
    }

    map_[row][0] = emptyTile;
  }

  map_[current_row_][0] = newTile;

  ++current_column_;
  ++number_of_columns_;
}

void Map::addColumnLast(Tile newTile) {
  Tile emptyTile;

  for (int i = 0 ; i < number_of_rows_ ; ++i) {
    map_[i].pushAsLast(emptyTile);
  }

  map_[current_row_][current_column_ + 1] = newTile;

  ++number_of_columns_;
}

void Map::moveNorth() {
  orientation_ = 1;
  --current_row_;
}

void Map::moveEast() {
  orientation_ = 2;
  ++current_column_;
}

void Map::moveSouth() {
  orientation_ = 3;
  ++current_row_;
}

void Map::moveWest() {
  orientation_ = 4;
  --current_column_;
}

bool Map::tileCandidateToVisit(const uint8_t row, const uint8_t column) {
  if (map_[row][column].isAccessible()
  && !map_[row][column].isBlack()
  && !map_[row][column].isVisited()) {
    return true;
  }
  else {
    return false;
  }
}