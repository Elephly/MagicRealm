#ifndef BOARD_H
#define BOARD_H
#include "commonlibrary_global.h"
#include "tile.h"
#include <unordered_map>

//Abstract class, extend this with all different Character types
class  COMMONLIBRARY_EXPORT Board{
public:
	Board();
private:
    std::unordered_map<Tile*, Tile[]> tiles;
};

#endif // BOARD_H