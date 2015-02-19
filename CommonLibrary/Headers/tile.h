#ifndef TILE_H
#define TILE_H

#include "clearing.h"
#include "shared.h"
#include <vector>

//Abstract class, extend this with all different tile types
class COMMONLIBRARY_EXPORT Tile {
public:
	Tile(Direction orient, string n);
    ~Tile();

    /*
    *   getName()
    *   out:    The name of the Tile as a String
    */
    string getName();

    /*
    *   getClearing
    *   in: Id of the Clearing
    *   out: Pointer to the clearing
    */
    Clearing* getClearing(int id);

    /*
    *   addClearing
    *   in: new Clearing Pointer
    */
    void addClearing(Clearing* newClearing);

    /*
    *   addAdjacentTile
    *   in: Pointer of an adjacentTile
        Runs through current list of tiles and determines if exists, or if already full
    */
    void addAdjacentTile(Tile* myTile);


private:
	vector<Clearing*>* clearings;

    //The offset of a rotated tile, the standard is SOUTH(0), when the name of the tile is orientated correctly.
    Direction orientation;

    //name of the string
    string name;

    Tile* adjacentTiles [ADJACENT_LENGTH];
};

#endif // TILE_H