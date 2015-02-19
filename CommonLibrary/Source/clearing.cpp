#include "clearing.h"
#include <sstream>

Clearing::Clearing(int clNum, Tile* parentTile) {
	ID= clNum;
    myTile = parentTile;
    pathways = new vector<Path*>;
    characters = new vector<Character*>;
    if(parentTile !=NULL)
        parentTile->addClearing(this);
    else
        cout << "WARN: Parent Tile NULL" <<endl;
}

Clearing::~Clearing()
{
    //destroying the paths in the clearing.
    pathways->clear();
    delete pathways;
    pathways = 0;

    //NOTE: not touching the characters, they should be destroyed later
}

void Clearing::addCharacter(Character* player)
{
    //checking to see if the player is already in this clearing.
    for(vector<Character*>::iterator it = characters->begin(); it != characters->end(); ++it){
        if(*it == player){
            cout << "WARN: character already registered in clearing, not registering character" <<endl;
            return;
        }
    }
    characters->push_back(player);
}
void Clearing::removeCharacter(Character* player)
{
    //checking to see if the player is already in this clearing.
    for(vector<Character*>::iterator it = characters->begin(); it != characters->end(); ++it){
        if(*it == player){
            characters->erase(it);
            return;
        }
    }
    cout << "WARN: character not found in clearing" <<endl;
}

void Clearing::removePath(Path* oldPath)
{
    //checking to see if the player is already in this clearing.
    for(vector<Path*>::iterator it = pathways->begin(); it != pathways->end(); ++it){
        if(*it == oldPath){
            pathways->erase(it);
            return;
        }
    }
    cout << "WARN: path not found in clearing" <<endl;
}

void Clearing::addPath(Path* newPath)
{
    //checking to see if the player is already in this clearing.
    for(vector<Path*>::iterator it = pathways->begin(); it != pathways->end(); ++it){
        if(*it == newPath){
            cout << "WARN: path already registered in clearing, not registering path" <<endl;
            return;
        }
    }
    pathways->push_back(newPath);
}

int Clearing::getClearingNum()
{
    return ID;
}

Tile* Clearing::getTile()
{
    return myTile;
}

vector<Path*>* Clearing::getPaths()
{
    return pathways;
}
string* Clearing::toString()
{
	ostringstream s;
	s << myTile->getName();
	s << VARDELIM;
	s << ID;

    string *tostring = new string (s.str());
    return tostring;
}