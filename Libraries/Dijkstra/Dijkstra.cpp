#include "Dijkstra.h"

void Dijkstra::initialValues(const Map tiles_map) {
  dijkstraTile support_dijkstra_tile;
  TVector<dijkstraTile> support_row;

  current_row_ = tiles_map.currentRow();
  current_column_ = tiles_map.currentColumn();

  support_dijkstra_tile.weight = 255;
  support_dijkstra_tile.checked = false;

  for (uint8_t row = 0; row < tiles_map.numberOfRows(); ++row) {
      support_dijkstra_tile.current.x = row;
      support_dijkstra_tile.prev.x = row;
    for (uint8_t column = 0; column < tiles_map.numberOfColumns(); ++column) {
      support_dijkstra_tile.current.y = column;
      support_dijkstra_tile.prev.y = column;
      support_row.pushAsLast(support_dijkstra_tile);
    }
    matrix_.pushAsLast(support_row);
    support_row.empty();
  }
}

void Dijkstra::updateMatrix(const Map tiles_map) {
  // Changing values of the current coord in the matrix.
  matrix_[current_row_][current_column_].weight = 0;
  current_coord_ = &matrix_[current_row_][current_column_].current;
  matrix_[current_row_][current_column_].checked = true;
  open_vector_.pushAsLast(current_coord_);

  // Adding all the accessible tiles to the open_vector_.
  while (open_vector_.getSize() > 0) {
    current_coord_ = open_vector_[0];

    // Pushing new coords to the open_vector.
    // Then checking and updating weights in the matrix_.
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).ableToGoNorth()
    && !tiles_map.getTile(current_coord_->x - 1, current_coord_->y).isBlack()) {
      if (matrix_[current_coord_->x - 1][current_coord_->y].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x - 1, current_coord_->y).getWeight()) {
        matrix_[current_coord_->x - 1][current_coord_->y].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x - 1, current_coord_->y).getWeight();
        matrix_[current_coord_->x - 1][current_coord_->y].prev = matrix_[current_coord_->x][current_coord_->y].current;
        open_vector_.pushAsLast(&matrix_[current_coord_->x - 1][current_coord_->y].current);
      }
    }
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).ableToGoEast()
    && !tiles_map.getTile(current_coord_->x, current_coord_->y + 1).isBlack()) {
      if (matrix_[current_coord_->x][current_coord_->y + 1].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y + 1).getWeight()) {
        matrix_[current_coord_->x][current_coord_->y + 1].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y + 1).getWeight();
        matrix_[current_coord_->x][current_coord_->y + 1].prev = matrix_[current_coord_->x][current_coord_->y].current;
        open_vector_.pushAsLast(&matrix_[current_coord_->x][current_coord_->y + 1].current);
      }
    }
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).ableToGoSouth()
    && !tiles_map.getTile(current_coord_->x + 1, current_coord_->y).isBlack()) {
      if (matrix_[current_coord_->x + 1][current_coord_->y].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x + 1, current_coord_->y).getWeight()) {
        matrix_[current_coord_->x + 1][current_coord_->y].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x + 1, current_coord_->y).getWeight();
        matrix_[current_coord_->x + 1][current_coord_->y].prev = matrix_[current_coord_->x][current_coord_->y].current;
        open_vector_.pushAsLast(&matrix_[current_coord_->x + 1][current_coord_->y].current);
      }
    }
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).ableToGoWest()
    && !tiles_map.getTile(current_coord_->x, current_coord_->y - 1).isBlack()) {
      if (matrix_[current_coord_->x][current_coord_->y - 1].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y - 1).getWeight()) {
        matrix_[current_coord_->x][current_coord_->y - 1].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y - 1).getWeight();
        matrix_[current_coord_->x][current_coord_->y - 1].prev = matrix_[current_coord_->x][current_coord_->y].current;
        open_vector_.pushAsLast(&matrix_[current_coord_->x][current_coord_->y - 1].current);
      }
    }
    open_vector_.popFirst();
  }
}

Dijkstra::Dijkstra(const Map tiles_map) {
  initialValues(tiles_map);

  for (uint8_t row = 0; row < tiles_map.numberOfRows(); ++row) {
    for (uint8_t column = 0; column < tiles_map.numberOfColumns(); ++column) {
      if (tiles_map.getTile(row, column).isAccessible() &&
      !tiles_map.getTile(row, column).isVisited() &&
      !tiles_map.getTile(row, column).isBlack()) {
        current_coord_ = &matrix_[row][column].current;
        non_visited_vector_.pushAsLast(current_coord_);
      }
    }
  }
}

Dijkstra::Dijkstra(const Map tiles_map, Tile tile_to_find) {
  initialValues(tiles_map);
}

void Dijkstra::printDijkstraMatrix(const Map tiles_map) {
  for (int row = 0 ; row < tiles_map.numberOfRows() ; ++row) {
    for (int column = 0 ; column < tiles_map.numberOfColumns() ; ++column) {
      Serial.print("(");
      Serial.print(matrix_[row][column].current.x);
      Serial.print(",");
      Serial.print(matrix_[row][column].current.y);
      Serial.print(")");
      Serial.print("[");
      Serial.print(matrix_[row][column].prev.x);
      Serial.print(",");
      Serial.print(matrix_[row][column].prev.y);
      Serial.print("]");
      Serial.print(matrix_[row][column].weight);
      Serial.print("  ");
    }
    Serial.println("");
  }
}

TVector<char> Dijkstra::getPath(const Map tiles_map) {
  updateMatrix(tiles_map);
  if (non_visited_vector_.getSize() > 0) current_coord_ = non_visited_vector_[0];
  else Serial.print("There are no Tiles to travel");

  // Comparing all the non-visited tiles.
  for (int i = 1 ; i < non_visited_vector_.getSize() ; ++i) {
    if (matrix_[current_coord_->x][current_coord_->y].weight > matrix_[non_visited_vector_[i]->x][non_visited_vector_[i]->y].weight) {
      current_coord_ = non_visited_vector_[i];
    }
  }

  printDijkstraMatrix(tiles_map);

  while (current_coord_->x != current_row_ || current_coord_->y != current_column_) {
    if (current_coord_->x - matrix_[current_coord_->x][current_coord_->y].prev.x == -1) {
      path_.pushAsFirst('N');
    }
    if (current_coord_->y - matrix_[current_coord_->x][current_coord_->y].prev.y == 1) {
      path_.pushAsFirst('E');
    }
    if (current_coord_->x - matrix_[current_coord_->x][current_coord_->y].prev.x == 1) {
      path_.pushAsFirst('S');
    }
    if (current_coord_->y - matrix_[current_coord_->x][current_coord_->y].prev.y == -1) {
      path_.pushAsFirst('W');
    }
    Serial.print("(");
    Serial.print(current_coord_->x);
    Serial.print(",");
    Serial.print(current_coord_->y);
    Serial.print(")");
    Serial.print("  ");
    current_coord_ = &matrix_[current_coord_->x][current_coord_->y].prev;
  }
    Serial.print(current_coord_->x);
    Serial.print(",");
    Serial.print(current_coord_->y);
    Serial.print("  ");

  return path_;
}