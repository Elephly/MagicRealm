#ifndef TILE_H
#define TILE_H

#include "clearing.h"
#include <vector>

class Tile {
public:
	Tile();
	~Tile();

private:
	std::vector<Clearing> clearings;
};

#endif // TILE_H