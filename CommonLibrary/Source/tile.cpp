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

    if(newTile == NULL){
        cout << "WARN Tile::addAdjacentTile: Tile not Added, Tile passed in was Null" <<endl;

    }
    if(findConnectingEdge(newTile) != EDGE_NONE){
        cout << "WARN Tile::addAdjacentTile: Tile not Added, Tile already exists in Connected Array" <<endl;
        return;
    }
    
    if(edge < EDGE_A || edge > EDGE_F){
        cout << "ERR Tile::addConnectedTile edge out of bounds" <<endl;
        return;
    }
    //when we hit null we have iterated over all current adjacent tiles
    if(connectedTiles[edge] == NULL){
        connectedTiles[edge] = newTile;
            
        //calculating the opposite edge to set to adjacent
        boardEdge = (edge+orientation) % 6;
        for(int i=0; i<CONNECTED_LENGTH; i++){
            oppEdge = (i+newTile->getOrientation()) % 6;
            if(oppEdge == ((boardEdge +3) % 6)){
                newTile->addConnectedTile(this, (Direction) i);
                return;
            }
        }
    }
    else{
        cout << "WARN Tile::addAdjacentTile: Tile not Added, ConnectedTile Array already has a Tile at that edge" <<endl;
        return;
    }    
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

Clearing* Tile::getConnectedClearing(Tile* aTile)
{
    vector <Path*> * paths = NULL;
    Direction connectedEdge = findConnectingEdge(aTile);
    if(connectedEdge !=EDGE_NONE){
        for(vector<Clearing*>::iterator it = clearings->begin(); it != clearings->end(); ++it)
        {
            paths = (*it)->getPaths();
            for(vector<Path*>::iterator iter = paths->begin(); iter != paths->end(); ++iter){
                if((*iter)->borderingSide() == connectedEdge){
                    return (*iter)->getEnd(NULL);
                }
            }
        }
        return NULL;
    }
    else{
        cout << "WARN: Tile::getConnectedClearing Tile is not connected" <<endl;
        return NULL;
    }
}

Direction Tile::findConnectingEdge(Tile* aTile)
{
    for(int i=0; i<CONNECTED_LENGTH; i++){
        if(aTile == connectedTiles[i])
            return (Direction) i;
    }
    return EDGE_NONE;
}