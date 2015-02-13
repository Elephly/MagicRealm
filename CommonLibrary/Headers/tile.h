#ifndef TILE_H
#define TILE_H

#include "clearing.h"
#include <vector>
#include "commonlibrary_global.h"

//Abstract class, extend this with all different tile types
class COMMONLIBRARY_EXPORT Tile {
public:
	virtual ~Tile();

private:
	std::vector<Clearing> clearings;
};

#endif // TILE_H