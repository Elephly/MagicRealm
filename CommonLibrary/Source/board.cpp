#include "board.h"
#include <sstream>

Board::Board() {
	//whole lotta nothing
    tileList = new vector <Tile*>;
    dwellingList = new vector<Dwelling*>;
}

void Board::addTile(Tile* newTile)
{
     for(vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it){
        if((*it)->getName() == newTile->getName()){
            cout << "WARN: Tile already in List not adding tile" <<endl;
            return;
        }
    }
    //tile not found so we can addTile.
    tileList->push_back(newTile);
}

Tile* Board::getTile(string tName)
{
    for(vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it){
        if((*it)->getName() == tName)
            return *it;
    }
    //Tile String not found.
    return NULL;
}

void Board::addDwelling(Dwelling* newDwelling)
{
     for(vector<Dwelling*>::iterator it = dwellingList->begin(); it != dwellingList->end(); ++it){
        if((*it)->getName() == newDwelling->getName()){
            cout << "WARN: Dwelling already in List not adding dwelling" <<endl;
            return;
        }
    }
    //tile not found so we can addTile.
    dwellingList->push_back(newDwelling);
}

Dwelling* Board::getDwelling(DwellingType dType)
{
    for(vector<Dwelling*>::iterator it = dwellingList->begin(); it != dwellingList->end(); ++it){
        if((*it)->getType() == dType)
            return *it;
    }
    //Tile String not found.
    return NULL;
}
string* Board::serialize() {
	stringstream s;
	s << "Board";
	s << CLASSDELIM;

	for (vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it) {
		s << *((*it)->serialize());
		s << LISTDELIM;
	}

	return new string(s.str());
}