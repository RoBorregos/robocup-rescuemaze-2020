#include "PhysicalFunctions.h"

PhysicalFunctions::PhysicalFunctions(Movement *movement, SensorMap *map, Control *control) {
  movement_ = movement;
  map_ = map;
  control_ = control;
}

bool PhysicalFunctions::moveRobot(const char orientation) {
  switch (orientation) {
    case 'N':
        movement_->turnDegrees(0);
        delay(1000);
        if (movement_->advancePID(0)) return true;
      break;
    case 'E':
        movement_->turnDegrees(90);
        delay(100);
        if (movement_->advancePID(90)) return true;;
      break;
    case 'S':
        movement_->turnDegrees(180);
        delay(1000);
        if (movement_->advancePID(180)) return true;
      break;
    case 'W':
        movement_->turnDegrees(270);
        delay(1000);
        if (movement_->advancePID(270)) return true;
      break;        
  }
  return false;
}

Map PhysicalFunctions::followPath(TVector<char> path, Map tiles_map, uint8_t zone) {
  while (path.getSize() > 0) {
    if (path[0] == 'N') {
      if (moveRobot('N')) {
        Tile blackTile = tiles_map.northTile();
        blackTile.setBlack();
        tiles_map.setTile(blackTile, 'N');
      } else {
        tiles_map.moveNorth();
      }
    }
    else if (path[0] == 'E') {
      if (moveRobot('E')) {
        Tile blackTile = tiles_map.eastTile();
        blackTile.setBlack();
        tiles_map.setTile(blackTile, 'E');
      } else {
        tiles_map.moveEast();
      }
    }
    else if (path[0] == 'S') {
      if (moveRobot('S')) {
        Tile blackTile = tiles_map.southTile();
        blackTile.setBlack();
        tiles_map.setTile(blackTile, 'S');
      } else {
        tiles_map.moveSouth();
      }
    }
    else if (path[0] == 'W') {
      if (moveRobot('W')) {
        Tile blackTile = tiles_map.westTile();
        blackTile.setBlack();
        tiles_map.setTile(blackTile, 'W');
      } else {
        tiles_map.moveWest();
      }
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

bool PhysicalFunctions::detectVictim(const uint8_t orientation) {
  if (map_->heatVictimLeft()) {
    //control_->turnLED();
    switch (orientation) {
      case 1:
          movement_->turnDegrees(90);
          dispenser.dropOneKitLeft();
          delay(300);
          movement_->turnDegrees(0);
          delay(500);
        break;
      case 2:
          movement_->turnDegrees(180);
          dispenser.dropOneKitLeft();
          delay(300);
          movement_->turnDegrees(90);
          delay(500);
        break;
      case 3:
          movement_->turnDegrees(270);
          dispenser.dropOneKitLeft();
          delay(300);
          movement_->turnDegrees(180);
          delay(500);
        break;
      case 4:
          movement_->turnDegrees(0);
          dispenser.dropOneKitLeft();
          delay(300);
          movement_->turnDegrees(270);
          delay(500);
        break;
    }
    return true;
  }
  return false;
}

bool PhysicalFunctions::passRamp() {
  bool is_a_ramp = control_->detectRamp();
  while (is_a_ramp) {
    motor_.fastForward();
    delay(500);
    is_a_ramp = control_->detectRamp();
  }
}