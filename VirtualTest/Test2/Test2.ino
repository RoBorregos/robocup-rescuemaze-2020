#include "Map.h"
#include "Dijkstra.h"
#include "VirtualFunctions.h"
#include "Ramp.h"

using namespace VirtualFunctions;

void setup() {
  Tile support_tile;
  TVector<char> path;
  unsigned short int current_zone = 0, unvisited_tiles = 1;
  TVector<Map> tiles_map;
  TVector<Ramp> ramps_vector;

  Serial.begin(9600);

  support_tile = updateFirstTile(support_tile, 0, 0, 0);

  // Adding the initial zone to the map.
  Map zone0;
  zone0.setInitialTile(support_tile);
  tiles_map.pushAsFirst(zone0);

  tiles_map[current_zone] = updateTiles(tiles_map[current_zone], 0);

  Serial.println("");
  printVirtualMap(0);
  Serial.println("");
  printMap(tiles_map[current_zone]);

  while (tiles_map[current_zone].getUnvisitedTiles(tiles_map) != 0) {
    Dijkstra dijkstra_matrix(tiles_map[current_zone]);
    path = dijkstra_matrix.getPath(tiles_map[current_zone]);
    Serial.println("");
    delay(1);

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

    printMap(tiles_map[current_zone]);
    Serial.println("");
    Serial.print("UNVISITED TILES: ");
    Serial.println(tiles_map[current_zone].getUnvisitedTiles(tiles_map));
    Serial.println("");
  }

  Serial.println(current_zone);
  printMap(tiles_map[current_zone]);
}

void loop() {

}
