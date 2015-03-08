#include "board.h"
#include <sstream>

Board::Board() {
	//whole lotta nothing
    tileList = new vector <Tile*>;
    dwellingList = new vector<Dwelling*>;
	createTiles();
	createTreasures();
	createMonsters();
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
        if((*it)->getType() == newDwelling->getType()){
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

vector <Tile *>* Board::getTileByType(TileType type)
{
	vector <Tile *> * typeList = new vector <Tile *>;
	for(vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it){
		if((*it)->getType() == type){
			typeList->push_back(*it);
		}
	}
	return typeList;
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

void Board::createTiles()
{
	cout << "Creating Tiles" <<endl;
	Clearing* c1 = NULL;
    Clearing* c2 = NULL;
    Clearing* c3 = NULL;
    Clearing* c4 = NULL;
    Clearing* c5 = NULL;
    Clearing* c6 = NULL;
    Path* p = NULL;
	Tile* newTile;

    //creating borderland tile and clearings and INTERNAL paths
	newTile = new Tile ("Border Land", TILE_CAVES);
	c1 = new Clearing(1, newTile, WOODS);
	c2 = new Clearing(2, newTile, WOODS);
	c3 = new Clearing(3, newTile, WOODS);
	c4 = new Clearing(4, newTile, CAVES);
	c5 = new Clearing(5, newTile, CAVES);
	c6 = new Clearing(6, newTile, CAVES);
	p = new Path(c1, c6);
	p = new Path(c2, c3);
	p = new Path(c3, c5);
	p = new Path(c3, c6);
	p = new Path(c4, c5, SECRET);
	p = new Path(c4, c6);
	addTile(newTile);

    //resetting the clearings and paths
	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //setting up the Oak Woods Tile and INTERNAL PATHS
    newTile = new Tile("Oak Woods", TILE_WOODS);
    c1 = new Clearing(2, newTile, WOODS);
    c2 = new Clearing(4, newTile, WOODS);
    c3 = new Clearing(5, newTile, WOODS);
    p = new Path(c1, c2);
    addTile(newTile);

    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //setting up the Bad Valley Tile. and INTERNAL PATHS
    newTile = new Tile("Bad Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(4, newTile, WOODS);
    c4 = new Clearing(5, newTile, WOODS);

    //regular paths
    p = new Path(c1, c3);
    p = new Path(c2, c4);

    addTile(newTile);
    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //Setting up the Maple Woods Tile and INTERNAL PATHS
    newTile = new Tile("Maple Woods", TILE_WOODS);

    c1 = new Clearing(2, newTile, WOODS);
    c2 = new Clearing(4, newTile, WOODS);
    c3 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c2);

    addTile(newTile);

    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    newTile = new Tile("Cavern", TILE_CAVES);

    c1 = new Clearing(1, newTile, CAVES);
    c2 = new Clearing(2, newTile, CAVES);
    c3 = new Clearing(3, newTile, CAVES);
    c4 = new Clearing(4, newTile, CAVES);
    c5 = new Clearing(5, newTile, CAVES);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c3);
    p = new Path(c1, c4, SECRET);
    p = new Path(c2, c3);
    p = new Path(c3, c5, SECRET);
    p = new Path(c3, c6);
    p = new Path(c4, c5);
    p = new Path(c4, c6);

    addTile(newTile);
    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //HighPass
    newTile = new Tile("High Pass", TILE_CAVES);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, MOUNTAIN);
    c3 = new Clearing(3, newTile, CAVES);
    c4 = new Clearing(4, newTile, MOUNTAIN);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c5);
    p = new Path(c1, c4);
    p = new Path(c2, c4);
    p = new Path(c3, c6);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Evil Valley
    newTile = new Tile("Evil Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Ledges

	newTile = new Tile("Ledges", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, MOUNTAIN);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, WOODS);

    p = new Path(c1, c3, HIDDEN);
    p = new Path(c1, c4);
    p = new Path(c1, c6);
    p = new Path(c2, c5);
    p = new Path(c3, c6);
    p = new Path(c4, c6, HIDDEN);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Cliff
    newTile = new Tile("Cliff", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, MOUNTAIN);
    c5 = new Clearing(5, newTile, WOODS);
    c6 = new Clearing(6, newTile, MOUNTAIN);

    p = new Path(c1, c6);
    p = new Path(c2, c3);
    p = new Path(c2, c5, HIDDEN);
    p = new Path(c3, c5);
    p = new Path(c3, c6, SECRET);
    p = new Path(c4, c6);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //crag
	newTile = new Tile("Crag", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, MOUNTAIN);
    c3 = new Clearing(3, newTile, MOUNTAIN);
    c4 = new Clearing(4, newTile, MOUNTAIN);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, MOUNTAIN);

    p = new Path(c1, c4);
    p = new Path(c1, c6, SECRET);
    p = new Path(c2, c5);
    p = new Path(c2, c3, HIDDEN);
    p = new Path(c3, c5);
    p = new Path(c3, c6);
    p = new Path(c4, c6);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Dark Valey
    newTile = new Tile("Dark Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Deep Woods
    newTile = new Tile("Deep Woods", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);
    c6 = new Clearing(6, newTile, WOODS);

    p = new Path(c1, c6);
	p = new Path(c1, c4, HIDDEN);
    p = new Path(c2, c3);
    p = new Path(c3, c5);
    p = new Path(c3, c6, HIDDEN);
    p = new Path(c4, c5);
    p = new Path(c4, c6);
    
    addTile(newTile);
    
	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Curst Valley
    newTile = new Tile("Curst Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Nut Woods
    newTile = new Tile("Nut Woods", TILE_WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c2, c4);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Awful Valley
    newTile = new Tile("Awful Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Linden Woods
    newTile = new Tile("Linden Woods", TILE_WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c2, c4);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Ruins
    newTile = new Tile("Ruins", TILE_CAVES);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c2);
    p = new Path(c1, c5, HIDDEN);
    p = new Path(c1, c4);
    p = new Path(c3, c5);
    p = new Path(c3, c6);
    p = new Path(c4, c6);
    
    addTile(newTile);

    newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Caves
    newTile = new Tile("Caves", TILE_CAVES);
    c1 = new Clearing(1, newTile, CAVES);
    c2 = new Clearing(2, newTile, CAVES);
    c3 = new Clearing(3, newTile, CAVES);
    c4 = new Clearing(4, newTile, CAVES);
    c5 = new Clearing(5, newTile, CAVES);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c6);
    p = new Path(c2, c3, SECRET);
    p = new Path(c2, c4);
    p = new Path(c3, c5);
    p = new Path(c4, c6);
    
    addTile(newTile);

    newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Linden Woods
    newTile = new Tile("Pine Woods", TILE_WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c2, c4);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Mountain
    newTile = new Tile("Mountain", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, MOUNTAIN);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, MOUNTAIN);

    p = new Path(c1, c3);
    p = new Path(c2, c5);
    p = new Path(c2, c4);
    p = new Path(c3, c6);
    p = new Path(c4, c6, HIDDEN);
    p = new Path(c5, c6);

    addTile(newTile);
    
	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;
}

void Board::createTreasures()
{
}

void Board::createMonsters()
{
	cout << "No Monsters Created" <<endl;
}
