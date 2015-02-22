#include "clearing.h"
#include <sstream>

Clearing::Clearing(int clNum, Tile* parentTile, ClearingType ct) {

    myType = ct;
	ID= clNum;
    myTile = parentTile;
    pathways = new vector<Path*>;
    characters = new vector<Character*>;
    myDwelling = NULL;
    if(parentTile !=NULL)
        parentTile->addClearing(this);
    else
        cout << "WARN: Parent Tile NULL" <<endl;
}

Clearing::Clearing(string* serialString, Board* board) {

	int pos = serialString->find(CLASSDELIM);
	string first = serialString->substr(0, pos);
	string second = serialString->substr(pos + 2);

	pos = second.find(VARDELIM);
	first = second.substr(0, pos);
	second = second.substr(pos + 1);
	int num = atoi(first.c_str());

	pos = second.find(VARDELIM);
	first = second.substr(0, pos);
	second = second.substr(pos + 1);
	string tile = first;

	ClearingType t = (ClearingType) atoi(second.c_str());

	Clearing(num, board->getTile(tile), t);

}

Clearing::~Clearing()
{
    //destroying the paths in the clearing.
    pathways->clear();
    delete pathways;
    pathways = 0;

    if(myDwelling)
        delete myDwelling;
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

Dwelling* Clearing::buildDwelling(DwellingType dt)
{
    if(!myDwelling){
        myDwelling = new Dwelling(dt, this, false);
        return myDwelling;
    }
    cout << "ERR: Clearing::buildDwelling Dwelling already existed in this clearing" << endl;
    return NULL;
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

ClearingType Clearing::getClearingType()
{
    return myType;
}

Dwelling* Clearing::getDwelling()
{
    return myDwelling;
}


const vector<Character*>* Clearing::getCharacters()
{
	return characters;
}

string* Clearing::serialize() {
	stringstream s;
	s << "Clearing";
	s << CLASSDELIM;
	s << ID;
	s << VARDELIM;
	s << myTile->getName();
	s << VARDELIM;
	s << myType;

	return new string(s.str());
}

char* Clearing::getTypeString(ClearingType type)
{
	switch (type)
	{
	case WOODS:
		return "Woods";
		break;
	case CAVES:
		return "Caves";
		break;
	case MOUNTAIN:
		return "Mountain";
		break;
	default:
		return "?";
		break;
	}
}