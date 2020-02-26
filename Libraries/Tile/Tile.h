#ifndef Tile_h
#define Tile_h

class Tile{
  private:
    char datos1, datos2;

  public:
    Tile();

    //getters
    //datos1
    bool getVisited();
    bool getStart();
    bool getCheckpoint();
    bool getBlack();
    bool getNorth();
    bool getEast();
    bool getSouth();
    bool getWest();
    //datos2
    bool getRampUp();
    bool getRampDown();
    bool getAccessible();
    bool getDeployedKit();
    int getWeight();

    //setters
    //datos1
    void setVisited();
    void setStart();
    void setCheckpoint();
    void setBlack();
    void setNorth();
    void setEast();
    void setSouth();
    void setWest();
    //datos2
    void setRampUp();
    void setRampDown();
    void setAccessible();
    void setUnaccessible();
    void setDeployedKit();
    void setWeight(const int weight);

    void operator=(Tile newTile);

    void print();
};

Tile::Tile(){
  datos1 = 0;
  datos2 = 0;
}

//setters
bool Tile::getVisited(){
  return (datos1 & 0x80);
}

bool Tile::getStart(){
  return (datos1 & 0x40);
}

bool Tile::getCheckpoint(){
  return (datos1 & 0x20);
}

bool Tile::getBlack(){
  return (datos1 & 0x10);
}

bool Tile::getNorth(){
  return (datos1 & 0x08);
}

bool Tile::getEast(){
  return (datos1 & 0x04);
}

bool Tile::getSouth(){
  return (datos1 & 0x02);
}

bool Tile::getWest(){
  return (datos1 & 0x01);
}

bool Tile::getRampUp(){
  return (datos2 & 0x80);
}

bool Tile::getRampDown(){
  return (datos2 & 0x40);
}

bool Tile::getAccessible() {
  return (datos2 & 0x20);
}

bool Tile::getDeployedKit(){
  return (datos2 & 0x10);
}

int Tile::getWeight(){
  uint8_t weight = 1;
  if (datos2 & 0x01) weight += 4;
  if (datos2 & 0x02) weight += 8;
  return weight;
}

//getters
void Tile::setVisited(){
  datos1 |= 0x80;
}

void Tile::setStart(){
  datos1 |= 0x40;
}

void Tile::setCheckpoint(){
  datos1 |= 0x20;
}

void Tile::setBlack(){
  datos1 |= 0x10;
}

void Tile::setNorth(){
  datos1 |= 0x08;
}

void Tile::setEast(){
  datos1 |= 0x04;
}

void Tile::setSouth(){
  datos1 |= 0x02;
}

void Tile::setWest(){
  datos1 |= 0x01;
}

void Tile::setRampUp(){
  datos2 |= 0x80;
}

void Tile::setRampDown(){
  datos2 |= 0x40;
}

void Tile::setAccessible() {
  datos2 |= 0x20;
}

void Tile::setUnaccessible() {
  datos2 &= 0xBF;
}

void Tile::setDeployedKit(){
  datos2 |= 0x10;
}

void Tile::setWeight(const int weight){
  if (weight == 1) {
    datos2 |= 0x01;
  }
  if (weight == 2) {
    datos2 |= 0x02;
  }
  if (weight == 3) {
    datos2 |= 0x03;
  }
}

void Tile::operator=(const Tile newTile) {
  datos1 = newTile.datos1;
  datos2 = newTile.datos2;
}

/*void Tile::print() {
  if (datos1 & 0x80) Serial.print("V");
  else Serial.print("0");
  if (datos1 & 0x08) Serial.print("N");
  else Serial.print("0");
  if (datos1 & 0x04) Serial.print("E");
  else Serial.print("0");
  if (datos1 & 0x02) Serial.print("S");
  else Serial.print("0");
  if (datos1 & 0x01) Serial.print("W");
  else Serial.print("0");
}*/

#endif