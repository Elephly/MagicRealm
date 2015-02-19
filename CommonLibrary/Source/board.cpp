#include "board.h"

Board::Board() {
	//whole lotta nothing
}

void Board::addTile(Tile* newTile)
{
     for(vector<Tile*>::iterator it = tileList.begin(); it != tileList.end(); ++it){
        if((*it)->getName() == newTile->getName()){
            cout << "WARN: Tile already in List not adding tile" <<endl;
            return;
        }
    }
    //tile not found so we can addTile.
    tileList.push_back(newTile);
}

Tile* Board::getTile(string tName)
{
    for(vector<Tile*>::iterator it = tileList.begin(); it != tileList.end(); ++it){
        if((*it)->getName() == tName)
            return *it;
    }
    //Tile String not found.
    return NULL;
}



