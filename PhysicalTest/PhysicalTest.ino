#include "Dijkstra.h"
#include "PhysicalFunctions.h"
#include "VirtualFunctions.h"
#include "Screen.h"
#include "SensorMap.h"
#include "Motors.h"
#include "Movement.h"
#include "Multiplexor.h"
#include "DropKit.h"
#include "BNO.h"
#include "Control.h"

//using namespace PhysicalFunctions;
using namespace VirtualFunctions;

int encoder_1 = 2;
int encoder_2 = 3;
Movement *movement_;

void encoderCountLeft() {
  movement_->encoderCountLeft();
}

void encoderCountRight() {
  movement_->encoderCountRight();
}

void setup() {
  Serial.begin(9600);
  Screen screen;
  Control *control;
  BNO *bno;
  SensorMap *maps;

  DropKit dropkit;
  DropKit *const dispenser = &dropkit;

  Multiplexor multiplexor;
  Multiplexor *const i2c = &multiplexor;

  Motors motors;
  Motors *const robot = &motors;

  BNO direct(i2c);
  bno = &direct;

  SensorMap sensorr(i2c);
  maps = &sensorr;

  Control controll(bno, maps);
  control = &controll;

  Movement robocup(bno, control, robot, maps, dispenser);
  movement = &robocup;

  while (bno->orientationStatus() != 3) {
    screen.writeLCDdown("I'm not ready");
  }
  screen.writeLCDdown("LET'S GO MAZE");

  movement_->initializePinEconders();
  attachInterrupt(digitalPinToInterrupt(encoder_1), encoderCountLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder_2), encoderCountRight, RISING);
  
  Tile support_tile;
  TVector<char> path;
  unsigned short int current_zone = 0, unvisited_tiles = 1;
  TVector<Map> tiles_map;
  PhysicalFunctions physicalFunctions(movement, maps, control, dispenser);
  physical_ = &physicalFunctions;

  ////////////////////////////////

  // Adding the initial zone to the map.
  Map zone0;
  zone0.setInitialTile(support_tile);
  tiles_map.pushAsFirst(zone0);
  tiles_map[current_zone] = physical_->updateFirstTile(tiles_map[current_zone], current_zone);
  
  while (tiles_map[current_zone].getUnvisitedTiles(tiles_map) != 0) {
    Serial.println("");
    printMap(tiles_map[current_zone]);  
    
    Dijkstra dijkstra_matrix(tiles_map[current_zone]);
    path = dijkstra_matrix.getPath(tiles_map[current_zone]);
    printCharVector(path);
    
    physical_->detectVictimLeft(tiles_map[current_zone].getOrientation());
    physical_->detectVictimRight(tiles_map[current_zone].getOrientation());
    
    tiles_map[current_zone] = physical_->updateTiles(tiles_map[current_zone], current_zone);
    delay(800);
    
    tiles_map[current_zone] = physical_->followPath(path, tiles_map[current_zone], current_zone);
  }
}

void loop() {

}
