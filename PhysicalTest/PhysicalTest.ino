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
  BNO *bno_;
  SensorMap *maps_;
  Control *control_;
  PhysicalFunctions *physical_;
  Multiplexor multii;
  Multiplexor *const i2c = &multii;

  Motors robo;
  Motors *const robot = &robo;

  BNO direct(i2c);
  bno_ = &direct;

  SensorMap sensorr(i2c);
  maps_ = &sensorr;

  Control controll(bno_, maps_);
  control_ = &controll;

  Movement robocup(bno_, control_, robot, maps_);
  movement_ = &robocup;

  movement_->initializePinEconders();
  attachInterrupt(digitalPinToInterrupt(encoder_1), encoderCountLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder_2), encoderCountRight, RISING);
  
  Tile support_tile;
  TVector<char> path;
  unsigned short int current_zone = 0, unvisited_tiles = 1;
  TVector<Map> tiles_map;
  PhysicalFunctions physicalFunctions(movement_, maps_, control_);
  physical_ = &physicalFunctions;
  while (bno_->orientationStatus() != 3) {
    screen.writeLCDdown("I'm not ready");
  }
  screen.writeLCDdown("MAZE 2020");

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
