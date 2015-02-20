#include "tile.h"

Tile::Tile( Direction orient, string n)
{
    clearings = new vector<Clearing*>;
    orientation = orient;
    name = n;
    
    //setting up adjacent tiles as null
    for(int i =0; i <CONNECTED_LENGTH; i++)
        connectedTiles[i] = NULL;

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

Direction Tile::getOrientation()
{
    return orientation;
}

Tile* Tile::getConnected(Direction edge)
{
    if(edge >= 0 && edge < 6)
        return connectedTiles[edge];
    else
        return NULL;
}

//LUKE: I know this is horribly optimized although I do not think this should be much of an issue
void Tile::addConnectedTile(Tile* newTile, Direction edge)
{
    int oppEdge = 0;
    int boardEdge = 0;
    int targetEdge = 0;

    switch(boardEdge){
                case 0:     targetEdge = 3; break;
                case 1:     targetEdge = 4; break;
                case 2:     targetEdge = 5; break;
                case 3:     targetEdge = 0; break;
                case 4:     targetEdge = 1; break;
                case 5:     targetEdge = 2; break;
                }
    for(int i =0; i<CONNECTED_LENGTH; i++){
        //when we hit null we have iterated over all current adjacent tiles
        if(connectedTiles[i] == NULL){
            connectedTiles[i] = newTile;
            
            //calculating the opposite edge to set to adjacent
            boardEdge = (edge+orientation) % 6;
            for(int i=0; i<CONNECTED_LENGTH; i++){
                oppEdge = (i+newTile->getOrientation()) % 6;
                if(oppEdge == targetEdge){
                    newTile->addConnectedTile(this, (Direction) oppEdge);
                    return;
                }
            }

            newTile->addConnectedTile(this, edge);
            return;
        }
        //tile already been added, not doing anything
        if(connectedTiles[i] == newTile){
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