#include "tile.h"

Tile::Tile(vector<Clearing*> *cl, Direction orient, string n) {
    clearings = *cl;
    orientation = orient;
    name = n;

}