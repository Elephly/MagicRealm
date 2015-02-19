#ifndef BOARD_H
#define BOARD_H
#include "commonlibrary_global.h"
#include "tile.h"
#include "shared.h"
#include <unordered_map>

//Abstract class, extend this with all different Character types
class  COMMONLIBRARY_EXPORT Board{
public:
	Board();
    /*
    *   addTile
    *   In:         Pointer to the tile you wish to add. 
    *   *           Array of Tile Pointers of tiles that have paths between them. Assumed size 6, null for no path.
    *   Purpose:    To Add a tile to the map with its desired paths betwen other tiles.
    */
    void addTile(Tile* newTile, Tile** adjArray);

    /*
    *   getTile
    *   in:     String of the tile name
    *   out:    Pointer to that tile.
    */
    Tile* getTile(string);

    /*
    *   getAdjacent
    *   in:     Tile Pointer
    *   out:    Array of adjacent tile pointers
    */
    Tile** getAdjacent(Tile*);
private:
    unordered_map<Tile*, Tile**> tilePaths;
    unordered_map<string, Tile*> tileList;

};

#endif // BOARD_H