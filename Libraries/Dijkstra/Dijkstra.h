#include "Map.h"

struct coord {
  uint8_t x, y;
};

struct dijkstra_tile {
  uint8_t weight;
  coord prev, current;
  bool checked;
};

TVector<char> dijkstra(Map tiles_map) {
  TVector<coord*> open_vector, non_visited_vector;
  TVector<char> path;
  dijkstra_tile matrix[tiles_map.getRows()][tiles_map.getColumns()];
  coord *current_coord;
  uint8_t current_row = tiles_map.getCurrRow();
  uint8_t current_column = tiles_map.getCurrColumn();

  //Setting all the elements of the matrix with the initial values
  for (int i = 0 ; i < tiles_map.getRows() ; ++i) {
    for (int j = 0 ; j < tiles_map.getColumns() ; ++j) {
      matrix[i][j].current.x = i;
      matrix[i][j].current.y = j;
      matrix[i][j].prev.x = i;
      matrix[i][j].prev.y = j;
      matrix[i][j].weight = 255;
      matrix[i][j].checked = false;
      
      if (tiles_map.getTile(i, j).getAccessible() == true && tiles_map.getTile(i, j).getVisited() == false && tiles_map.getTile(i, j).getBlack() == false) {
        current_coord = &matrix[i][j].current;
        non_visited_vector.pushTop(current_coord);
      }
      
    }
  }

  //Changing values of the current coord in the matrix
  matrix[current_row][current_column].weight = 0;
  current_coord = &matrix[current_row][current_column].current;
  matrix[current_row][current_column].checked = true;
  open_vector.pushTop(current_coord);

  while (open_vector.getSize() > 0) {
    current_coord = open_vector[0];

    //Pushing new coords to the open_vector
    //Then checking and updating weights in the matrix
    if (tiles_map.getTile(current_coord->x, current_coord->y).getNorth() == true && tiles_map.getTile(current_coord->x - 1, current_coord->y).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x - 1, current_coord->y).getVisited() == true && matrix[current_coord->x - 1][current_coord->y].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x - 1][current_coord->y].current);
        matrix[current_coord->x - 1][current_coord->y].checked = true;
      }
      if (matrix[current_coord->x - 1][current_coord->y].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x - 1, current_coord->y).getWeight()) {
        matrix[current_coord->x - 1][current_coord->y].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x - 1, current_coord->y).getWeight();
        matrix[current_coord->x - 1][current_coord->y].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getEast() == true && tiles_map.getTile(current_coord->x, current_coord->y + 1).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x, current_coord->y + 1).getVisited() == true && matrix[current_coord->x][current_coord->y + 1].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x][current_coord->y + 1].current);
        matrix[current_coord->x][current_coord->y + 1].checked = true;
      }
      if (matrix[current_coord->x][current_coord->y + 1].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y + 1).getWeight()) {
        matrix[current_coord->x][current_coord->y + 1].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y + 1).getWeight();
        matrix[current_coord->x][current_coord->y + 1].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getSouth() == true && tiles_map.getTile(current_coord->x + 1, current_coord->y).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x + 1, current_coord->y).getVisited() == true && matrix[current_coord->x + 1][current_coord->y].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x + 1][current_coord->y].current);
        matrix[current_coord->x + 1][current_coord->y].checked = true;
      }
      if (matrix[current_coord->x + 1][current_coord->y].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x + 1, current_coord->y).getWeight()) {
        matrix[current_coord->x + 1][current_coord->y].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x + 1, current_coord->y).getWeight();
        matrix[current_coord->x + 1][current_coord->y].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getWest() == true && tiles_map.getTile(current_coord->x, current_coord->y - 1).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x, current_coord->y - 1).getVisited() == true && matrix[current_coord->x][current_coord->y - 1].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x][current_coord->y - 1].current);
        matrix[current_coord->x][current_coord->y - 1].checked = true;
      }
      if (matrix[current_coord->x][current_coord->y - 1].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y - 1).getWeight()) {
        matrix[current_coord->x][current_coord->y - 1].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y - 1).getWeight();
        matrix[current_coord->x][current_coord->y - 1].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    open_vector.popFront();
    
  }

  if (non_visited_vector.getSize() > 0) current_coord = non_visited_vector[0];
  else Serial.print("No hay tiles por recorrer");

  //Comparing all the non Visited Tiles
  for (int i = 1 ; i < non_visited_vector.getSize() ; ++i) {
    if (matrix[current_coord->x][current_coord->y].weight > matrix[non_visited_vector[i]->x][non_visited_vector[i]->y].weight) {
      current_coord = non_visited_vector[i];
    }
  }

  ///////////////////////////////////////////////////////////////////////////////
  for (int i = 0 ; i < tiles_map.getRows() ; ++i) {
    for (int j = 0 ; j < tiles_map.getColumns() ; ++j) {
      Serial.print("(");
      Serial.print(matrix[i][j].current.x);
      Serial.print(",");
      Serial.print(matrix[i][j].current.y);
      Serial.print(")");
      Serial.print("[");
      Serial.print(matrix[i][j].prev.x);
      Serial.print(",");
      Serial.print(matrix[i][j].prev.y);
      Serial.print("]");
      Serial.print(matrix[i][j].weight);
      Serial.print("  ");
    }
    Serial.println("");
  }
  Serial.println("");
  ////////////////////////////////////////////////////////////////////////////////

  while (current_coord->x != current_row || current_coord->y != current_column) {
    if (current_coord->x - matrix[current_coord->x][current_coord->y].prev.x == -1) {
      path.pushFront('N');
    }
    if (current_coord->y - matrix[current_coord->x][current_coord->y].prev.y == 1) {
      path.pushFront('E');
    }
    if (current_coord->x - matrix[current_coord->x][current_coord->y].prev.x == 1) {
      path.pushFront('S');
    }
    if (current_coord->y - matrix[current_coord->x][current_coord->y].prev.y == -1) {
      path.pushFront('W');
    }
    Serial.print("(");
    Serial.print(current_coord->x);
    Serial.print(",");
    Serial.print(current_coord->y);
    Serial.print(")");
    Serial.print("  ");
    current_coord = &matrix[current_coord->x][current_coord->y].prev;
  }
    Serial.print(current_coord->x);
    Serial.print(",");
    Serial.print(current_coord->y);
    Serial.print("  ");

  return path;
}

TVector<char> goToStart(Map tiles_map) {
  TVector<coord*> open_vector;
  TVector<char> path;
  dijkstra_tile matrix[tiles_map.getRows()][tiles_map.getColumns()];
  coord *current_coord;
  uint8_t current_row = tiles_map.getCurrRow();
  uint8_t current_column = tiles_map.getCurrColumn();

  for (int i = 0 ; i < tiles_map.getRows() ; ++i) {
    for (int j = 0 ; j < tiles_map.getColumns() ; ++j) {
      matrix[i][j].current.x = i;
      matrix[i][j].current.y = j;
      matrix[i][j].weight = 255;
      matrix[i][j].checked = false;
    }
  }

  //Changing values of the current coord in the matrix
  matrix[current_row][current_column].weight = 0;
  current_coord = &matrix[current_row][current_column].current;
  matrix[current_row][current_column].checked = true;
  open_vector.pushTop(current_coord);

  //Adding all the accessible tiles to the open_vector
  while (open_vector.getSize() > 0) {
    current_coord = open_vector[0];

    //Pushing new coords to the open_vector
    //Then checking and updating weights in the matrix
    if (tiles_map.getTile(current_coord->x, current_coord->y).getNorth() == true && tiles_map.getTile(current_coord->x - 1, current_coord->y).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x - 1, current_coord->y).getVisited() == true && matrix[current_coord->x - 1][current_coord->y].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x - 1][current_coord->y].current);
        matrix[current_coord->x - 1][current_coord->y].checked = true;
      }
      if (matrix[current_coord->x - 1][current_coord->y].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x - 1, current_coord->y).getWeight()) {
        matrix[current_coord->x - 1][current_coord->y].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x - 1, current_coord->y).getWeight();
        matrix[current_coord->x - 1][current_coord->y].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getEast() == true && tiles_map.getTile(current_coord->x, current_coord->y + 1).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x, current_coord->y + 1).getVisited() == true && matrix[current_coord->x][current_coord->y + 1].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x][current_coord->y + 1].current);
        matrix[current_coord->x][current_coord->y + 1].checked = true;
      }
      if (matrix[current_coord->x][current_coord->y + 1].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y + 1).getWeight()) {
        matrix[current_coord->x][current_coord->y + 1].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y + 1).getWeight();
        matrix[current_coord->x][current_coord->y + 1].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getSouth() == true && tiles_map.getTile(current_coord->x + 1, current_coord->y).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x + 1, current_coord->y).getVisited() == true && matrix[current_coord->x + 1][current_coord->y].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x + 1][current_coord->y].current);
        matrix[current_coord->x + 1][current_coord->y].checked = true;
      }
      if (matrix[current_coord->x + 1][current_coord->y].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x + 1, current_coord->y).getWeight()) {
        matrix[current_coord->x + 1][current_coord->y].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x + 1, current_coord->y).getWeight();
        matrix[current_coord->x + 1][current_coord->y].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getWest() == true && tiles_map.getTile(current_coord->x, current_coord->y - 1).getBlack() == false) {
      if (tiles_map.getTile(current_coord->x, current_coord->y - 1).getVisited() == true && matrix[current_coord->x][current_coord->y - 1].checked == false) {
        open_vector.pushTop(&matrix[current_coord->x][current_coord->y - 1].current);
        matrix[current_coord->x][current_coord->y - 1].checked = true;
      }
      if (matrix[current_coord->x][current_coord->y - 1].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y - 1).getWeight()) {
        matrix[current_coord->x][current_coord->y - 1].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y - 1).getWeight();
        matrix[current_coord->x][current_coord->y - 1].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }

    open_vector.popFront();
  }

  for (int i = 0 ; i < tiles_map.getRows() ; ++i) {
    for (int j = 0 ; j < tiles_map.getColumns() ; ++j) {
      if (tiles_map.getTile(i, j).getStart()) {
        current_coord = &matrix[i][j].current;
      }
    }
  }

   while (current_coord->x != current_row || current_coord->y != current_column) {
    if (current_coord->x - matrix[current_coord->x][current_coord->y].prev.x == -1) {
      path.pushFront('N');
    }
    if (current_coord->y - matrix[current_coord->x][current_coord->y].prev.y == 1) {
      path.pushFront('E');
    }
    if (current_coord->x - matrix[current_coord->x][current_coord->y].prev.x == 1) {
      path.pushFront('S');
    }
    if (current_coord->y - matrix[current_coord->x][current_coord->y].prev.y == -1) {
      path.pushFront('W');
    }
    Serial.print("(");
    Serial.print(current_coord->x);
    Serial.print(",");
    Serial.print(current_coord->y);
    Serial.print(")");
    Serial.print("  ");
    current_coord = &matrix[current_coord->x][current_coord->y].prev;
  }
    Serial.print(current_coord->x);
    Serial.print(",");
    Serial.print(current_coord->y);
    Serial.print("  ");

  return path;
}