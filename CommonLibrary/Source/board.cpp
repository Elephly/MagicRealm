#include "board.h"

Board::Board() {
	//whole lotta nothing
}

void Board::addTile(Tile* newTile, Tile** adjArray)
{
    Tile* arr [6] = {NULL, NULL, NULL, NULL, NULL, NULL};
    tilePaths.insert(newTile, adjArray);

}



