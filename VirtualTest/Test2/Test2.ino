#include "Tile.h"
#include "TVector.h"
#include "Map.h"

uint8_t iSize = 11, iRow = 1, iColumn = 1;
char virtualMap[11][11] = {{'.','W','.','W','.','W','.','W','.','W','.'},
                    {'W','R','W',' ','W',' ','.',' ','.',' ','W'},
                    {'.','.','.','.','.','.','.','.','.','.','.'},
                    {'W',' ','.',' ','W',' ','W',' ','W',' ','W'},
                    {'.','.','.','.','.','.','.','.','.','.','.'},
                    {'W',' ','W',' ','W',' ','W',' ','W',' ','W'},
                    {'.','.','.','.','.','W','.','.','.','.','.'},
                    {'W',' ','.',' ','W',' ','W',' ','W',' ','W'},
                    {'.','.','.','.','.','.','.','.','.','.','.'},
                    {'W',' ','W',' ','.',' ','.',' ','.',' ','W'},
                    {'.','W','.','W','.','W','.','W','.','W','.'}};

void printVirtualMap() {
  for(int iX = 0 ; iX < iSize ; iX++) {
    for(int iY = 0 ; iY < iSize ; iY++) {
      Serial.print(virtualMap[iX][iY]);
      if(iY < iSize - 1) Serial.print(" ");
    }
    Serial.println("");
  }
}

void moveMapNorth() {
  virtualMap[iRow][iColumn] = 'V';
  virtualMap[iRow - 2][iColumn] = 'R';
  iRow -= 2;
}

void moveMapEast() {
  virtualMap[iRow][iColumn] = 'V';
  virtualMap[iRow][iColumn + 2] = 'R';
  iColumn += 2;
}

void moveMapSouth() {
  virtualMap[iRow][iColumn] = 'V';
  virtualMap[iRow + 2][iColumn] = 'R';
  iRow += 2;
}

void moveMapWest() {
  virtualMap[iRow][iColumn] = 'V';
  virtualMap[iRow][iColumn - 2] = 'R';
  iColumn -= 2;
}

void printMap(Map tiles_map, const uint8_t iFloor) {
  char char_map[tiles_map.getRows()*2 + 1][tiles_map.getColumns()*2 + 1];
  int row_char, column_char;

  for(int i = 0; i < tiles_map.getRows()*2 + 1; ++i) {
    for(int j = 0; j < tiles_map.getColumns()*2 + 1; ++j) {
      char_map[i][j] = '.';
    }
  }
  
  row_char = 1;

  for (int row_tile = 0 ; row_tile < tiles_map.getRows() ; row_tile++) {
    column_char = 1;
    for (int column_tile = 0 ; column_tile < tiles_map.getColumns() ; column_tile++) {
      if(tiles_map.getTile(row_tile, column_tile).getStart()) {
        char_map[row_char][column_char] = 'S';
      }
      else if(tiles_map.getTile(row_tile, column_tile).getVisited()) {
        char_map[row_char][column_char] = 'V';
      }
      else if(tiles_map.getTile(row_tile, column_tile).getAccessible()) {
        char_map[row_char][column_char] = ' ';
      }
      else {
        char_map[row_char][column_char] = 'X';
      }
      if(tiles_map.getTile(row_tile, column_tile).getNorth()) {
        char_map[row_char - 1][column_char] = '.';
      }
      else {
        char_map[row_char - 1][column_char] = 'W';
      }
      if(tiles_map.getTile(row_tile, column_tile).getEast()) {
        char_map[row_char][column_char + 1] = '.';
      }
      else {
        char_map[row_char][column_char + 1] = 'W';
      }
      if(tiles_map.getTile(row_tile, column_tile).getSouth()) {
        char_map[row_char + 1][column_char] = '.';
      }
      else {
        char_map[row_char+1][column_char] = 'W';
      }
      if(tiles_map.getTile(row_tile, column_tile).getWest()) {
        char_map[row_char][column_char - 1] = '.';
      }
      else {
        char_map[row_char][column_char - 1] = 'W';
      }
      column_char += 2;
    }
    row_char += 2;
  }
  
  for(int i = 0 ; i < tiles_map.getRows()*2 + 1 ; i++) {
    for(int j = 0 ; j < tiles_map.getColumns()*2 + 1 ; j++) {
      Serial.print(char_map[i][j]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
  Serial.println(" ");
}

struct coord {
  uint8_t x, y;
};

struct dijkstra_tile {
  uint8_t weight;
  coord prev, current;
};

TVector<char> dijkstra(Map tiles_map) {
  TVector<coord*> open_vector, non_visited_vector;
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
      
      if (tiles_map.getTile(i, j).getAccessible() == true && tiles_map.getTile(i, j).getVisited() == false) {
        current_coord = &matrix[i][j].current;
        non_visited_vector.push(current_coord);
      }
      
    }
  }

  matrix[current_row][current_column].weight = 0;
  current_coord = &matrix[current_row][current_column].current;
  open_vector.push(current_coord);

  while (open_vector.getSize() > 0) {
    current_coord = open_vector[0];
    
    if (tiles_map.getTile(current_coord->x, current_coord->y).getNorth() == true) {
      if (matrix[current_coord->x - 1][current_coord->y].weight > matrix[current_coord->x - 1][current_coord->y].weight + tiles_map.getTile(current_coord->x - 1, current_coord->y).getWeight()) {
        matrix[current_coord->x - 1][current_coord->y].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x - 1, current_coord->y).getWeight();
        matrix[current_coord->x - 1][current_coord->y].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getEast() == true) {
      if (matrix[current_coord->x][current_coord->y + 1].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y + 1).getWeight()) {
        matrix[current_coord->x][current_coord->y + 1].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y + 1).getWeight();
        matrix[current_coord->x][current_coord->y + 1].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getSouth() == true) {
      if (matrix[current_coord->x + 1][current_coord->y].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x + 1, current_coord->y).getWeight()) {
        matrix[current_coord->x + 1][current_coord->y].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x + 1, current_coord->y).getWeight();
        matrix[current_coord->x + 1][current_coord->y].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    if (tiles_map.getTile(current_coord->x, current_coord->y).getWest() == true) {
      if (matrix[current_coord->x][current_coord->y - 1].weight > matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y - 1).getWeight()) {
        matrix[current_coord->x][current_coord->y - 1].weight = matrix[current_coord->x][current_coord->y].weight + tiles_map.getTile(current_coord->x, current_coord->y - 1).getWeight();
        matrix[current_coord->x][current_coord->y - 1].prev = matrix[current_coord->x][current_coord->y].current;
      }
    }
    
  }

  if (non_visited_vector.getSize() > 0) current_coord = non_visited_vector[0];
  else Serial.print("No hay tiles por recorrer");

  for (int i = 1 ; i < non_visited_vector.getSize() ; ++i) {
    if (matrix[current_coord->x][current_coord->y].weight > matrix[non_visited_vector[i]->x][non_visited_vector[i]->y].weight) {
      current_coord = non_visited_vector[i];
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
  }

  return path;
}

void setup() {
  Serial.begin(9600);
  printVirtualMap();
  Tile currTile;
  currTile.setVisited();
  currTile.setAccessible();
  TVector<char> path;
  unsigned short int current_row = 0, current_column = 0;

  if (virtualMap[0][1] != 'W') {
    currTile.setNorth();
  }
  if (virtualMap[1][2] != 'W') {
    currTile.setEast();
  }
  if (virtualMap[2][1] != 'W') {
    currTile.setSouth();
  }
  if (virtualMap[1][0] != 'W') {
    currTile.setWest();
  }

  Map tiles_map(currTile);
  current_row = 0;
  current_column = 0;

  //creating new adjacent tiles
  if (tiles_map.currTile().getNorth() == true) {
    Tile newTile;
    newTile.setSouth();
    newTile.setAccessible();
    tiles_map.addRowFirst(newTile);
  }
  if (tiles_map.currTile().getEast() == true) {
    Tile newTile;
    newTile.setWest();
    newTile.setAccessible();
    tiles_map.addColumnLast(newTile);
  }
  if (tiles_map.currTile().getSouth() == true) {
    Tile newTile;
    newTile.setNorth();
    newTile.setAccessible();
    tiles_map.addRowLast(newTile);
  }
  if (tiles_map.currTile().getWest() == true) {
    Tile newTile;
    newTile.setEast();
    newTile.setAccessible();
    tiles_map.addColumnFirst(newTile);
  }

  printMap(tiles_map, 1);
  //tiles_map.print();
  Serial.println("");
  Serial.println("");
  delay(2000);

  path = dijkstra(tiles_map);

  while (tiles_map.getUnvisitedTiles() != 0) {
  
    

    currTile = tiles_map.currTile();
    currTile.setVisited();
    
    //Update North
    if (virtualMap[tiles_map.getCurrRow()*2][tiles_map.getCurrColumn()*2 + 1] != 'W') {
      currTile.setNorth();
      if (tiles_map.getCurrRow() > 0 && tiles_map.northTile().getVisited() == false) {
        Tile northTile = tiles_map.northTile();
        northTile.setSouth();
        northTile.setAccessible();
        tiles_map.setTile(northTile, 'N');
      }
      else if (tiles_map.getCurrRow() == 0) {
        Tile northTile;
        northTile.setSouth();
        northTile.setAccessible();
        tiles_map.addRowFirst(northTile);
      }
    }

    //Update East
    if (virtualMap[tiles_map.getCurrRow()*2 + 1][tiles_map.getCurrColumn()*2 + 2] != 'W') {
      currTile.setEast();
      if (tiles_map.getCurrColumn() < tiles_map.getColumns() - 1 && tiles_map.eastTile().getVisited() == false) {
        Tile eastTile = tiles_map.eastTile();
        eastTile.setWest();
        eastTile.setAccessible();
        tiles_map.setTile(eastTile, 'E');
      }
      else if (tiles_map.getCurrColumn() == tiles_map.getColumns() - 1) {
        Tile eastTile;
        eastTile.setWest();
        eastTile.setAccessible();
        tiles_map.addColumnLast(eastTile);
      }
    }

    //Update South
    if (virtualMap[tiles_map.getCurrRow()*2 + 2][tiles_map.getCurrColumn()*2 + 1] != 'W') {
      currTile.setSouth();
      if (tiles_map.getCurrRow() < tiles_map.getRows() - 1 && tiles_map.southTile().getVisited() == false) {
        Tile southTile = tiles_map.southTile();
        southTile.setNorth();
        southTile.setAccessible();
        tiles_map.setTile(southTile, 'S');
      } 
      else if (tiles_map.getCurrRow() == tiles_map.getRows() - 1) {
        Tile southTile;
        southTile.setNorth();
        southTile.setAccessible();
        tiles_map.addRowLast(southTile);
      }
    }

    //Update West
    if (virtualMap[tiles_map.getCurrRow()*2 + 1][tiles_map.getCurrColumn()*2] != 'W') {
      currTile.setWest();
      if (tiles_map.getCurrColumn() > 0 && tiles_map.westTile().getVisited() == false)  {
        Tile westTile = tiles_map.westTile();
        westTile.setEast();
        westTile.setAccessible();
        tiles_map.setTile(westTile, 'W');
      }
      else if (tiles_map.getCurrColumn() == 0) {
        Tile westTile;
        westTile.setEast();
        westTile.setAccessible();
        tiles_map.addColumnFirst(westTile);
      }
    }

    tiles_map.setTile(currTile, '0');

    Serial.print("Orientation: ");
    Serial.println(tiles_map.getOrientation());
    printVirtualMap();
    Serial.println("");
    printMap(tiles_map, 1);
    //tiles_map.print();
    Serial.println("");
    delay(2000);
  }
}

void loop() {

}
