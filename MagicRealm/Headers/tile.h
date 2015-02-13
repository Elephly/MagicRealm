#ifndef TILE_H
#define TILE_H

#include "clearing.h"
#include <vector>

//Abstract class, extend this with all different tile types
class Tile {
public:
	virtual ~Tile();

private:
	std::vector<Clearing> clearings;
};

#endif // TILE_H