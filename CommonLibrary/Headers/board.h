#ifndef BOARD_H
#define BOARD_H
#include "commonlibrary_global.h"
#include "tile.h"
#include "shared.h"
#include <vector>
#include "serializer.h"

//Abstract class, extend this with all different Character types
class  COMMONLIBRARY_EXPORT Board : public Serializer {
public:
	Board();
	Board(string* serialString);
    //TODO BOARD DESTRUCTOR
    /*
    *   addTile
    *   In:         Pointer to the tile you wish to add. 
    *   Purpose:    To Add a tile to the map with its desired paths betwen other tiles.
    */
    void addTile(Tile* newTile);
    
    /*
    *   getTile
    *   in:     String of the tile name
    *   out:    Pointer to that tile.
    */
    Tile* getTile(string tName);

	virtual string* serialize();

private:
    vector<Tile*>* tileList;
};

#endif // BOARD_H