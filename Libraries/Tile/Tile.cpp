#include "Tile.h"

Tile::Tile(){
  data1_ = 0;
  data2_ = 0;
}

// Getters.
bool Tile::isVisited(){
  return (data1_ & 0x80);
}

bool Tile::getStart(){
  return (data1_ & 0x40);
}

bool Tile::isCheckpoint(){
  return (data1_ & 0x20);
}

bool Tile::isBlack(){
  return (data1_ & 0x10);
}

bool Tile::ableToGoNorth(){
  return (data1_ & 0x08);
}

bool Tile::ableToGoEast(){
  return (data1_ & 0x04);
}

bool Tile::ableToGoSouth(){
  return (data1_ & 0x02);
}

bool Tile::ableToGoWest(){
  return (data1_ & 0x01);
}

bool Tile::getRampUp(){
  return (data2_ & 0x80);
}

bool Tile::getRampDown(){
  return (data2_ & 0x40);
}

bool Tile::isAccessible() {
  return (data2_ & 0x20);
}

bool Tile::getDeployedKit(){
  return (data2_ & 0x10);
}

uint8_t Tile::getWeight(){
  uint8_t weight = 1;
  if (data2_ & 0x01) weight += 4;
  if (data2_ & 0x02) weight += 8;
  return weight;
}

// Setters.
void Tile::setVisited(){
  data1_ |= 0x80;
}

void Tile::setStart(){
  data1_ |= 0x40;
}

void Tile::setCheckpoint(){
  data1_ |= 0x20;
}

void Tile::setBlack(){
  data1_ |= 0x10;
}

void Tile::setNorth(){
  data1_ |= 0x08;
}

void Tile::setEast(){
  data1_ |= 0x04;
}

void Tile::setSouth(){
  data1_ |= 0x02;
}

void Tile::setWest(){
  data1_ |= 0x01;
}

void Tile::setRampUp(){
  data2_ |= 0x80;
}

void Tile::setRampDown(){
  data2_ |= 0x40;
}

void Tile::setAccessible() {
  data2_ |= 0x20;
}

void Tile::setUnaccessible() {
  data2_ &= 0xBF;
}

void Tile::setDeployedKit(){
  data2_ |= 0x10;
}

void Tile::setWeight(const int weight){
  if (weight == 1) {
    data2_ |= 0x01;
  }
  if (weight == 2) {
    data2_ |= 0x02;
  }
  if (weight == 3) {
    data2_ |= 0x03;
  }
}

void Tile::operator=(const Tile newTile) {
  data1_ = newTile.data1_;
  data2_ = newTile.data2_;
}