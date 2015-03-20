#include "tile.h"
#include <sstream>

Tile::Tile(string n, TileType type)
{
    clearings = new vector<Clearing*>;
	//placeholder, direction needs to be set after creating the tile.
	orientation = EDGE_NONE;
    name = n;
    myType = type;
    //setting up adjacent tiles as null
    for(int i =0; i <CONNECTED_LENGTH; i++)
        connectedTiles[i] = NULL;

	warningChit = 0;
	siteSoundChit = 0;
}

Tile::Tile(string* serialString) {
	clearings = new vector<Clearing*>;
	int pos = serialString->find(CLASSDELIM);
	string second = serialString->substr(pos + 2);
	string first;

	pos = second.find(VARDELIM);
	first = second.substr(0, pos);
	second = second.substr(pos + 1);
 
	Tile(second, TILE_WOODS);
	//setting the direction of the new tile.
	Direction o = (Direction) atoi(first.c_str());
	setOrientation(o);

	//TODO fix serialization
}

void Tile::addSiteOrSoundChit(Chit* newChit)
{
	siteSoundChit = newChit;
}

void Tile::addWarningChit(Warning* newChit)
{
	warningChit = newChit;
}

Chit* Tile::getWarningChit()
{
	return warningChit;
}

Chit* Tile::getSiteOrSoundChit()
{
	return siteSoundChit;
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

void Tile::setOrientation(Direction newOrientation)
{
	orientation = newOrientation;
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
#ifdef DEBUG
        cout << "WARN Tile::addAdjacentTile: Tile not Added, Tile passed in was Null" <<endl;
#endif

    }
    if(findConnectingEdge(newTile) != EDGE_NONE){
#ifdef DEBUG
        cout << "WARN Tile::addAdjacentTile: Tile not Added, Tile already exists in Connected Array" <<endl;
#endif
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
#ifdef DEBUG
            cout << "WARN: Clearing already exists in tile, not adding Tile" <<endl;
#endif
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
#ifdef DEBUG
        cout << "WARN: Tile::getConnectedClearing Tile is not connected" <<endl;
#endif
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

TileType Tile::getType()
{
	return myType;
}
//Tile**orientation^name^clearing1+clearing2+
string* Tile::serialize() {
	stringstream s;
	s << "Tile";
	s << CLASSDELIM;
	s << orientation;
	s << VARDELIM;
	s << name;
	s << VARDELIM;
	s << myType;

	return new string(s.str());
}