#include "tile.h"

Tile::Tile(vector<Clearing*> *cl, Direction orient, string n) {
    clearings = *cl;
    orientation = orient;
    name = n;

}
string Tile::getName()
{
    return name;
}

Clearing* Tile::getClearing(int clearingID)
{
    for(vector<Clearing*>::iterator it = clearings.begin(); it != clearings.end(); ++it){
        if( (*it)->getClearingNum() == clearingID)
            return *it;
    }
    return NULL;
}