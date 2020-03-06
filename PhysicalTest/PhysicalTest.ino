#include "Dijkstra.h"
#include "PhysicalFunctions.h"

using namespace PhysicalFunctions;

void setup() {
  Tile support_tile;
  TVector<char> path;
  unsigned short int current_zone = 0, unvisited_tiles = 1;
  TVector<Map> tiles_map;
  //TVector<Ramp> ramps_vector;

  Serial.begin(9600);

  // Adding the initial zone to the map.
  Map zone0;
  zone0.setInitialTile(support_tile);
  tiles_map.pushAsFirst(zone0);
  tiles_map[current_zone] = updateFirstTile(tiles_map[current_zone], current_zone);
  
  while (tiles_map[current_zone].getUnvisitedTiles(tiles_map) != 0) {
    Dijkstra dijkstra_matrix(tiles_map[current_zone]);
    path = dijkstra_matrix.getPath(tiles_map[current_zone]);

    tiles_map[current_zone] = followPath(path, tiles_map[current_zone], current_zone);

    tiles_map[current_zone] = updateTiles(tiles_map[current_zone], current_zone);

    /*(if (tiles_map[current_zone].currentTile().isRampUp() || tiles_map[current_zone].currentTile().isRampDown()) {
      ++current_zone;
      Map nextZone;
      Tile support_tile;
      support_tile = updateFirstTile(support_tile, current_zone, 0, 0);
      nextZone.setInitialTile(support_tile);
      tiles_map.pushAsLast(nextZone);
      }*/
  }
}

void loop() {

}
