#include "tile.h"

Tile::Tile( Direction orient, string n)
{
    clearings = new vector<Clearing*>;
    orientation = orient;
    name = n;
    
    //setting up adjacent tiles as null
    for(int i =0; i <ADJACENT_LENGTH; i++)
        adjacentTiles[i] = NULL;

}

Tile::~Tile()
{
    clearings->clear();
    delete clearings;
    clearings = 0;
}
string Tile::getName()
{
    return name;
}


//LUKE: I know this is horribly optimized although I do not think this should be much of an issue
void Tile::addAdjacentTile(Tile* newTile)
{
    for(int i =0; i<ADJACENT_LENGTH; i++){
        //when we hit null we have iterated over all current adjacent tiles
        if(adjacentTiles[i] == NULL){
            adjacentTiles[i] = newTile;
            newTile->addAdjacentTile(this);
            return;
        }
        //tile already been added, not doing anything
        if(adjacentTiles[i] == newTile){
            return;
        }

    }
    cout << "WARN Tile::addAdjacentTile: Tile not Added, AdjacentTile Array already full" <<endl; 
}

void Tile::addClearing(Clearing* newClearing)
{
    for(vector<Clearing*>::iterator it = clearings->begin(); it != clearings->end(); ++it){
        if(*it == newClearing){
            cout << "WARN: Clearing already exists in tile, not adding Tile" <<endl;
            return;
        }
    }
    clearings->push_back(newClearing);
}
Clearing* Tile::getClearing(int clearingID)
{
    for(vector<Clearing*>::iterator it = clearings->begin(); it != clearings->end(); ++it){
        if( (*it)->getClearingNum() == clearingID)
            return *it;
    }
    return NULL;
}