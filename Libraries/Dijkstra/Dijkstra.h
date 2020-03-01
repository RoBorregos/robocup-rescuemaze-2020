// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// The code includes functions that use an implementation of Dijkstra's algorith to simulate the shortest
// path to the closest unvisited tile of the map.

#include "Map.h"

struct coord {
  uint8_t x, y;
};

struct dijkstra_tile {
  uint8_t weight;
  coord prev, current;
  bool checked;
};

class Dijkstra {
  private:
    TVector<coord*> open_vector_, non_visited_vector_;
    TVector<char> path_;
    TVector<TVector<dijkstra_tile>> matrix_;
    coord *current_coord_;
    uint8_t current_row_;
    uint8_t current_column_;

    void initialValues(const Map tiles_map);
    void updateMatrix(const Map tiles_map);
  public:
    //Setting all the elements of the matrix with the initial values.
    Dijkstra(const Map tiles_map);
    Dijkstra(const Map tiles_map, Tile tile_to_find);
    
    void printDijkstraMatrix(const Map tiles_map);
    TVector<char> getPath(const Map tiles_map);
};

void Dijkstra::initialValues(const Map tiles_map) {
  dijkstra_tile support_dijkstra_tile;
  TVector<dijkstra_tile> support_row;

  current_row_ = tiles_map.currentRow();
  current_column_ = tiles_map.currentColumn();

  for (uint8_t row = 0; row < tiles_map.numberOfRows(); ++row) {
    for (uint8_t column = 0; column < tiles_map.numberOfColumns(); ++column) {
      support_dijkstra_tile.current.x = row;
      support_dijkstra_tile.current.y = column;
      support_dijkstra_tile.prev.x = row;
      support_dijkstra_tile.prev.y = column;
      support_dijkstra_tile.weight = 255;
      support_dijkstra_tile.checked = false;
      //////////////////////////////////////////////
      Serial.print(support_dijkstra_tile.current.x);
      Serial.print(support_dijkstra_tile.current.y);
      //////////////////////////////////////////////
      support_row.pushAsLast(support_dijkstra_tile);
    }
    matrix_.pushAsLast(support_row);
  }
}

void Dijkstra::updateMatrix(const Map tiles_map) {
  //Changing values of the current coord in the matrix.
  matrix_[current_row_][current_column_].weight = 0;
  current_coord_ = &matrix_[current_row_][current_column_].current;
  matrix_[current_row_][current_column_].checked = true;
  open_vector_.pushAsLast(current_coord_);

  //Adding all the accessible tiles to the open_vector_.
  while (open_vector_.getSize() > 0) {
    current_coord_ = open_vector_[0];

    //Pushing new coords to the open_vector.
    //Then checking and updating weights in the matrix_.
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).getNorth() == true && tiles_map.getTile(current_coord_->x - 1, current_coord_->y).isBlack() == false) {
      if (tiles_map.getTile(current_coord_->x - 1, current_coord_->y).isVisited() == true && matrix_[current_coord_->x - 1][current_coord_->y].checked == false) {
        open_vector_.pushAsLast(&matrix_[current_coord_->x - 1][current_coord_->y].current);
        matrix_[current_coord_->x - 1][current_coord_->y].checked = true;
      }
      if (matrix_[current_coord_->x - 1][current_coord_->y].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x - 1, current_coord_->y).getWeight()) {
        matrix_[current_coord_->x - 1][current_coord_->y].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x - 1, current_coord_->y).getWeight();
        matrix_[current_coord_->x - 1][current_coord_->y].prev = matrix_[current_coord_->x][current_coord_->y].current;
      }
    }
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).getEast() == true && tiles_map.getTile(current_coord_->x, current_coord_->y + 1).isBlack() == false) {
      if (tiles_map.getTile(current_coord_->x, current_coord_->y + 1).isVisited() == true && matrix_[current_coord_->x][current_coord_->y + 1].checked == false) {
        open_vector_.pushAsLast(&matrix_[current_coord_->x][current_coord_->y + 1].current);
        matrix_[current_coord_->x][current_coord_->y + 1].checked = true;
      }
      if (matrix_[current_coord_->x][current_coord_->y + 1].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y + 1).getWeight()) {
        matrix_[current_coord_->x][current_coord_->y + 1].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y + 1).getWeight();
        matrix_[current_coord_->x][current_coord_->y + 1].prev = matrix_[current_coord_->x][current_coord_->y].current;
      }
    }
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).getSouth() == true && tiles_map.getTile(current_coord_->x + 1, current_coord_->y).isBlack() == false) {
      if (tiles_map.getTile(current_coord_->x + 1, current_coord_->y).isVisited() == true && matrix_[current_coord_->x + 1][current_coord_->y].checked == false) {
        open_vector_.pushAsLast(&matrix_[current_coord_->x + 1][current_coord_->y].current);
        matrix_[current_coord_->x + 1][current_coord_->y].checked = true;
      }
      if (matrix_[current_coord_->x + 1][current_coord_->y].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x + 1, current_coord_->y).getWeight()) {
        matrix_[current_coord_->x + 1][current_coord_->y].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x + 1, current_coord_->y).getWeight();
        matrix_[current_coord_->x + 1][current_coord_->y].prev = matrix_[current_coord_->x][current_coord_->y].current;
      }
    }
    if (tiles_map.getTile(current_coord_->x, current_coord_->y).getWest() == true && tiles_map.getTile(current_coord_->x, current_coord_->y - 1).isBlack() == false) {
      if (tiles_map.getTile(current_coord_->x, current_coord_->y - 1).isVisited() == true && matrix_[current_coord_->x][current_coord_->y - 1].checked == false) {
        open_vector_.pushAsLast(&matrix_[current_coord_->x][current_coord_->y - 1].current);
        matrix_[current_coord_->x][current_coord_->y - 1].checked = true;
      }
      if (matrix_[current_coord_->x][current_coord_->y - 1].weight > matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y - 1).getWeight()) {
        matrix_[current_coord_->x][current_coord_->y - 1].weight = matrix_[current_coord_->x][current_coord_->y].weight + tiles_map.getTile(current_coord_->x, current_coord_->y - 1).getWeight();
        matrix_[current_coord_->x][current_coord_->y - 1].prev = matrix_[current_coord_->x][current_coord_->y].current;
      }
    }
    open_vector_.popFirst();
  }
}

Dijkstra::Dijkstra(const Map tiles_map) {
  initialValues(tiles_map);

  for (uint8_t row = 0; row < tiles_map.numberOfRows(); ++row) {
    for (uint8_t column = 0; column < tiles_map.numberOfColumns(); ++column) {
      if (tiles_map.getTile(row, column).isAccessible() == true &&
      tiles_map.getTile(row, column).isVisited() == false &&
      tiles_map.getTile(row, column).isBlack() == false) {
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

  //Comparing all the non-visited tiles.
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