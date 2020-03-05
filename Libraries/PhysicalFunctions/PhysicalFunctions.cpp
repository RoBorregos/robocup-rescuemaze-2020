#include "PhysicalFunctions.h"

namespace PhyisicalFunctions {
    void moveRobotNorth() {
        move->turnDegrees(0);
    }

    /*Map followPath(TVector<char> path, Map tiles_map, uint8_t zone) {
    while (path.getSize() > 0) {
      if (path[0] == 'N') {
        tiles_map.moveNorth();
        moveMapNorth(zone);
      }
      else if (path[0] == 'E') {
        tiles_map.moveEast();
        moveMapEast(zone);
      }
      else if (path[0] == 'S') {
        tiles_map.moveSouth();
        moveMapSouth(zone);
      }
      else if (path[0] == 'W') {
        tiles_map.moveWest();
        moveMapWest(zone);
      }

      Serial.println("");
      Serial.println("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
      Serial.println("");
      printVirtualMap(zone);
      Serial.println("");

      path.popFirst();
    }

    return tiles_map;
  }

  Tile updateFirstTile(Tile tile, uint8_t zone, const uint8_t x, const uint8_t y) {
    if (virtual_map[zone][2*x][2*y + 1] != 'W') {
      tile.setNorth();
    }
    if (virtual_map[zone][2*x + 1][2*y + 2] != 'W') {
      tile.setEast();
    }
    if (virtual_map[zone][2*x + 2][2*y + 1] != 'W') {
      tile.setSouth();
    }
    if (virtual_map[zone][2*x + 1][2*y] != 'W') {
      tile.setWest();
    }

    tile.setVisited();
    tile.setAccessible();
    tile.setStart();

    return tile;
  }

  // TODO(Eme112): Implement a function to synthetize how to update North, East, South, and West.
  Map updateTiles(Map tiles_map, const uint8_t zone) {
    Tile current_tile;

    current_tile = tiles_map.currentTile();
    current_tile.setVisited();

    // Ramps.
    if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 1] == 'U') {
      current_tile.setRampUp();
    }
    else if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 1] == 'D') {
      current_tile.setRampDown();
    }
    
    // Weight.
    if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 1] == '1') {
      current_tile.setWeight(1);
    }
    else if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 1] == '2') {
      current_tile.setWeight(2);
    }
    else if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 1] == '3') {
      current_tile.setWeight(3);
    }
    
    // North.
    if (virtual_map[zone][tiles_map.currentRow()*2][tiles_map.currentColumn()*2 + 1] != 'W') {
      current_tile.setNorth();
      if (tiles_map.currentRow() > 0
      && tiles_map.northTile().isVisited() == false) {
        Tile north_tile = tiles_map.northTile();
        north_tile.setSouth();
        north_tile.setAccessible();
        tiles_map.setTile(north_tile, 'N');
      }
      else if (tiles_map.currentRow() == 0) {
        Tile north_tile;
        north_tile.setSouth();
        north_tile.setAccessible();
        tiles_map.addRowFirst(north_tile);
      }
      
      if (virtual_map[zone][tiles_map.currentRow()*2 - 1][tiles_map.currentColumn()*2 + 1] == 'B') {
        Tile north_tile = tiles_map.northTile();
        north_tile.setBlack();
        tiles_map.setTile(north_tile, 'N');
      }
    }

    // East.
    if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 2] != 'W') {
      current_tile.setEast();
      if (tiles_map.currentColumn() < tiles_map.numberOfColumns() - 1
      && tiles_map.eastTile().isVisited() == false) {
        Tile east_tile = tiles_map.eastTile();
        east_tile.setWest();
        east_tile.setAccessible();
        tiles_map.setTile(east_tile, 'E');
      }
      else if (tiles_map.currentColumn() == tiles_map.numberOfColumns() - 1) {
        Tile east_tile;
        east_tile.setWest();
        east_tile.setAccessible();
        tiles_map.addColumnLast(east_tile);
      }
      
      if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 3] == 'B') {
        Tile east_tile = tiles_map.northTile();
        east_tile.setBlack();
        tiles_map.setTile(east_tile, 'E');
      }
    }

    // South.
    if (virtual_map[zone][tiles_map.currentRow()*2 + 2][tiles_map.currentColumn()*2 + 1] != 'W') {
      current_tile.setSouth();
      if (tiles_map.currentRow() < tiles_map.numberOfRows() - 1
      && tiles_map.southTile().isVisited() == false) {
        Tile south_tile = tiles_map.southTile();
        south_tile.setNorth();
        south_tile.setAccessible();
        tiles_map.setTile(south_tile, 'S');
      } 
      else if (tiles_map.currentRow() == tiles_map.numberOfRows() - 1) {
        Tile south_tile;
        south_tile.setNorth();
        south_tile.setAccessible();
        tiles_map.addRowLast(south_tile);
      }
      
      if (virtual_map[zone][tiles_map.currentRow()*2 + 3][tiles_map.currentColumn()*2 + 1] == 'B') {
        Tile south_tile = tiles_map.northTile(); 
        south_tile.setBlack();
        tiles_map.setTile(south_tile, 'S'); 
      }
    }

    // West.
    if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2] != 'W') {
      current_tile.setWest();
      if (tiles_map.currentColumn() > 0
      && tiles_map.westTile().isVisited() == false)  {
        Tile west_tile = tiles_map.westTile();
        west_tile.setEast();
        west_tile.setAccessible();
        tiles_map.setTile(west_tile, 'W');
      }
      else if (tiles_map.currentColumn() == 0) {
        Tile west_tile;
        west_tile.setEast();
        west_tile.setAccessible();
        tiles_map.addColumnFirst(west_tile);
      }

      if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 - 1] == 'B') {
        Tile west_tile = tiles_map.northTile();
        west_tile.setBlack();
        tiles_map.setTile(west_tile, 'W');
      }
    }

    tiles_map.setTile(current_tile, '0');

    return tiles_map;
  }*/
}