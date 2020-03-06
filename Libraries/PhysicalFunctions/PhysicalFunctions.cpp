#include "PhysicalFunctions.h"

PhysicalFunctions::PhysicalFunctions(Movement *movement, SensorMap *map) {
  movement_ = movement;
  map_ = map;
}

void PhysicalFunctions::moveRobot(const char orientation) {
  switch (orientation) {
    case 'N':
        movement_->turnDegrees(0);
        delay(500);
        movement_->advancePID(0);
      break;
    case 'E':
        movement_->turnDegrees(90);
        delay(500);
        movement_->advancePID(90);
      break;
    case 'S':
        movement_->turnDegrees(180);
        delay(500);
        movement_->advancePID(180);
      break;
    case 'W':
        movement_->turnDegrees(270);
        delay(500);
        movement_->advancePID(270);
      break;        
  }
}

Map PhysicalFunctions::followPath(TVector<char> path, Map tiles_map, uint8_t zone) {
  while (path.getSize() > 0) {
    if (path[0] == 'N') {
      tiles_map.moveNorth();
      moveRobot('N');
    }
    else if (path[0] == 'E') {
      tiles_map.moveEast();
      moveRobot('E');
    }
    else if (path[0] == 'S') {
      tiles_map.moveSouth();
      moveRobot('S');
    }
    else if (path[0] == 'W') {
      tiles_map.moveWest();
      moveRobot('W');
    }

    path.popFirst();
  }

  return tiles_map;
}

Map PhysicalFunctions::updateFirstTile(Map tiles_map, uint8_t zone) {
  Tile tile = tiles_map.currentTile();
  Serial.print("FRONT LEFT: ");
  Serial.println(map_->getDistanceFrontLeft());
  Serial.print("FRONT RIGHT: ");
  Serial.println(map_->getDistanceFrontRight());
  Serial.print("RIGHT UP: ");
  Serial.println(map_->getDistanceRightUp());
  Serial.print("RIGHT DOWN: ");
  Serial.println(map_->getDistanceRightDown());
  Serial.print("LEFT UP: ");
  Serial.println(map_->getDistanceLeftUp());
  Serial.print("LEFT DOWN: ");
  Serial.println(map_->getDistanceLeftDown());
  Serial.print("checkWallsBack: ");
  Serial.println(map_->getDistanceBack());

  if (!map_->checkWallsFront()) {
    tile.setNorth();
    Tile north_tile;
    north_tile.setSouth();
    north_tile.setAccessible();
    tiles_map.addRowFirst(north_tile);
    Serial.print("NORTE");
  }
  if (!map_->checkWallsRight()) {
    tile.setEast();
    Tile east_tile;
    east_tile.setWest();
    east_tile.setAccessible();
    tiles_map.addColumnLast(east_tile);
    Serial.print("ESTE");
  }
  if (!map_->checkWallsBack()) {
    tile.setSouth();
    Tile south_tile;
    south_tile.setNorth();
    south_tile.setAccessible();
    tiles_map.addRowLast(south_tile);
    Serial.print("SUR");
  }
  if (!map_->checkWallsLeft()) {
    tile.setWest();
    Tile west_tile;
    west_tile.setEast();
    west_tile.setAccessible();
    tiles_map.addColumnFirst(west_tile);
    Serial.print("OESTE");
  }

  tile.setVisited();
  tile.setAccessible();
  tile.setStart();

  tiles_map.setTile(tile, '0');

  return tiles_map;
}

// TODO(Eme112): Implement a function to synthetize how to update North, East, South, and West.
// TODO(Eme112): Implement weights and ramps.
// TODO(Eme112): Implement black tiles.
Map PhysicalFunctions::updateTiles(Map tiles_map, const uint8_t zone) {
  Tile current_tile = tiles_map.currentTile();
  bool able_to_go_North = false;
  bool able_to_go_East = false;
  bool able_to_go_South  = false;
  bool able_to_go_West = false;

  current_tile.setVisited();

  // Ramps.
  /*if (virtual_map[zone][tiles_map.currentRow()*2 + 1][tiles_map.currentColumn()*2 + 1] == 'U') {
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
  }*/
  
  // North.
  switch (tiles_map.getOrientation()) {
    case 1:
        if (!map_->checkWallsFront()) {
          able_to_go_North = true;
        }
      break;
    case 2:
        if (!map_->checkWallsLeft()) {
          able_to_go_North = true;
        }
      break;
    case 4:
        if (!map_->checkWallsRight()) {
          able_to_go_North = true;
        }
      break;
    default:
        able_to_go_North = true;
  }
  if (able_to_go_North) {
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
  }

  // East.
  switch (tiles_map.getOrientation()) {
    case 1:
        if (!map_->checkWallsRight()) {
          able_to_go_East = true;
        }
      break;
    case 2:
        if (!map_->checkWallsFront()) {
          able_to_go_East = true;
        }
      break;
    case 3:
        if (!map_->checkWallsLeft()) {
          able_to_go_East = true;
        }
      break;
    default:
        able_to_go_East = true;
  }
  if (able_to_go_East) {
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
  }

  // South.
  switch (tiles_map.getOrientation()) {
    case 2:
        if (!map_->checkWallsRight()) {
          able_to_go_South = true;
        }
      break;
    case 3:
        if (!map_->checkWallsFront()) {
          able_to_go_South = true;
        }
      break;
    case 4:
        if (!map_->checkWallsLeft()) {
          able_to_go_South = true;
        }
      break;
    default:
        able_to_go_South = true;
  }
  if (able_to_go_South) {
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
  }

  // West.
  switch (tiles_map.getOrientation()) {
    case 1:
        if (!map_->checkWallsLeft()) {
          able_to_go_West = true;
        }
      break;
    case 3:
        if (!map_->checkWallsRight()) {
          able_to_go_West = true;
        }
      break;
    case 4:
        if (!map_->checkWallsFront()) {
          able_to_go_West = true;
        }
      break;
    default:
        able_to_go_West = true;
  }
  if (able_to_go_West) {
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
  }

  tiles_map.setTile(current_tile, '0');

  return tiles_map;
}