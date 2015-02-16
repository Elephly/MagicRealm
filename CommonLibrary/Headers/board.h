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
    void addTile(Tile*, Tile**);
private:
    unordered_map<Tile*, Tile**> tile_paths;

};

#endif // BOARD_H