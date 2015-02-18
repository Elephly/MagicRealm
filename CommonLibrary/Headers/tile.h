#ifndef TILE_H
#define TILE_H

#include "clearing.h"
#include "shared.h"
#include <vector>

//Abstract class, extend this with all different tile types
class COMMONLIBRARY_EXPORT Tile {
public:
	Tile(vector<Clearing*>* cls, Direction orient, string n);

    string getName();

private:
	vector<Clearing*> clearings;

    //The offset of a rotated tile, the standard is SOUTH(0), when the name of the tile is orientated correctly.
    Direction orientation;

    //name of the string
    string name;
};

#endif // TILE_H