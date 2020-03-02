#include "Tile.h"
#include "Map.h"
#include "TVector.h"
#include "Dijkstra.h"
#include "VirtualFunctions.h"

void setup() {
  Tile current_tile;
  TVector<char> path;
  unsigned short int current_row = 0, current_column = 0, current_zone = 0;

  Serial.begin(9600);

  // Updating walls of the first tile.
  if (virtual_map[0][1] != 'W') {
    current_tile.setNorth();
  }
  if (virtual_map[1][2] != 'W') {
    current_tile.setEast();
  }
  if (virtual_map[2][1] != 'W') {
    current_tile.setSouth();
  }
  if (virtual_map[1][0] != 'W') {
    current_tile.setWest();
  }

  // Setting values of the first tile.
  current_tile.setVisited();
  current_tile.setAccessible();
  current_tile.setStart();
  
  // Creating the map with the initial zone.
  Map zone0;
  zone0.setInitialTile(current_tile);
  TVector<Map> tiles_map;
  tiles_map.pushAsFirst(zone0);

  // Creating and adding new adjacent tiles.
  if (tiles_map[current_zone].currTile().ableToGoNorth() == true) {
    Tile new_tile;
    new_tile.setSouth();
    new_tile.setAccessible();
    //if (virtual_map[][] == 'B') new_tile.setBlack();
    //tiles_map[current_zone].addRowFirst(new_tile);
  }
  if (tiles_map[current_zone].currTile().ableToGoEast() == true) {
    Tile new_tile;
    new_tile.setWest();
    new_tile.setAccessible();
    if (virtual_map[1][3] == 'B') new_tile.setBlack();
    tiles_map[current_zone].addColumnLast(new_tile);
  }
  if (tiles_map[current_zone].currTile().ableToGoSouth() == true) {
    Tile new_tile;
    new_tile.setNorth();
    new_tile.setAccessible();
    if (virtual_map[3][1] == 'B') new_tile.setBlack();
    tiles_map[current_zone].addRowLast(new_tile);
  }
  if (tiles_map[current_zone].currTile().ableToGoWest() == true) {
    Tile new_tile;
    new_tile.setEast();
    new_tile.setAccessible();
    //if (virtual_map[][] == 'B') new_tile.setBlack();
    //tiles_map[current_zone].addColumnFirst(new_tile);
  }

  printVirtualMap();
  Serial.println("");
  printMap(tiles_map[current_zone], 1);
  
  ///////////////////////////////////////////////////////////////////
  /////////////////////////// MAIN LOOP /////////////////////////////
  ///////////////////////////////////////////////////////////////////
  while (tiles_map[current_zone].getUnvisitedTiles() != 0) {
    Dijkstra dijkstra_matrix(tiles_map[current_zone]);
    path = dijkstra_matrix.getPath(tiles_map[current_zone]);
    //path = dijkstra(tiles_map[current_zone]);
    Serial.println(path.getSize());

    /////////////////////////////////////////////
    for (int i = 0 ; i < path.getSize() ; ++i) {
      Serial.print(path[i]);
      Serial.print(" ");
    }
    /////////////////////////////////////////////
    Serial.println("");
    Serial.println("");
    Serial.println("");
    delay(100);

    tiles_map[current_zone] = followPath(path, tiles_map[current_zone]);

    tiles_map[current_zone] = updateTiles(tiles_map[current_zone]);

    printMap(tiles_map[current_zone], 1);
    Serial.println("");
    //////////////////////////////////////////////
    Serial.print("UNVISITED TILES: ");
    Serial.println(tiles_map[current_zone].getUnvisitedTiles());
    //////////////////////////////////////////////
  }
  ///////////////////////////////////////////////////////////////////
  //////////////////////////// END LOOP /////////////////////////////
  ///////////////////////////////////////////////////////////////////

  
  /*path = goToStart(tiles_map[current_zone]);

  /////////////////////////////////////////////
  for (int i = 0 ; i < path.getSize() ; ++i) {
    Serial.print(path[i]);
    Serial.print(" ");
  }
  /////////////////////////////////////////////
  Serial.println("");
  Serial.println("");
  Serial.println("");
  delay(100);

  while (path.getSize() > 0) {
    if (path[0] == 'N') {
      tiles_map[current_zone].moveNorth();
      moveMapNorth();
    }
    else if (path[0] == 'E') {
      tiles_map[current_zone].moveEast();
      moveMapEast();
    }
    else if (path[0] == 'S') {
      tiles_map[current_zone].moveSouth();
      moveMapSouth();
    }
    else if (path[0] == 'W') {
      tiles_map[current_zone].moveWest();
      moveMapWest();
    }
    
    printVirtualMap();
    Serial.println("");

    path.popFirst();
  }*/
}

void loop() {

}
