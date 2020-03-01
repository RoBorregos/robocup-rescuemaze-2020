// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// The class includes functions that use an implementation of Dijkstra's algorith to simulate the shortest
// path to the closest unvisited tile of the map.

#ifndef Dijkstra_h
#define Dijkstra_h

#include "Map.h"

// Stores a 2-D coordinate. 
struct coord {
  uint8_t x, y;
};

// Stores 2 coords, the current and the one were it comes from.
// Stores if it has been checked for revision and the weight it costs to travel that tile.
struct dijkstraTile {
  uint8_t weight;
  coord prev, current;
  bool checked;
};

class Dijkstra {
  private:
    TVector<coord*> open_vector_, non_visited_vector_;
    TVector<char> path_;
    TVector<TVector<dijkstraTile>> matrix_;
    coord *current_coord_;
    uint8_t current_row_;
    uint8_t current_column_;

    void initialValues(const Map tiles_map);
    void updateMatrix(const Map tiles_map);
  public:
    // Constructor that sets all the elements of the matrix with the initial values.
    Dijkstra(const Map tiles_map);
    // Constructor that sets all the elements of the matrix with the initial values and recieves a tile to find its shortest path.
    Dijkstra(const Map tiles_map, Tile tile_to_find);
    
    // Prints the matrix with the weight it costs to reach each tile.
    void printDijkstraMatrix(const Map tiles_map);
    // Returns a char vector with the indications to get to the wanted tile.
    TVector<char> getPath(const Map tiles_map);
};

#endif