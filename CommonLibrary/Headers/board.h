#ifndef BOARD_H
#define BOARD_H
#include "commonlibrary_global.h"
#include "tile.h"
#include "shared.h"
#include <vector>
#include "serializer.h"
#include "dwelling.h"
#include "site.h"
#include "sound.h"
#include "warning.h"
#include "treasure.h"

class Clearing;
class Tile;
class Dwelling;

//Abstract class, extend this with all different Character types
class  COMMONLIBRARY_EXPORT Board : public Serializer {
public:
	Board();
	Board(string* serialString);
    //TODO BOARD DESTRUCTOR    
    /*
    *   addDwelling
    *   In:         Pointer to the dwelling you wish to add. 
    *   Purpose:    To Add a dwelling to the map.
    */
    void addDwelling(Dwelling* newDwelling);

    /*
    *   getDwelling
    *   in:     String of the Dwelling name
    *   out:    Pointer to that dwelling.
    */
    Dwelling* getDwelling(DwellingType dType);

    /*
    *   getTile
    *   in:     String of the tile name
    *   out:    Pointer to that tile.
    */
    Tile* getTile(string tName);

	vector<Tile*>* getTileByType(TileType type);

	//returns a pointer to the list of treasure pointers
	vector<Treasure*>* getLargeTreasureList();
	vector<Treasure*>* getSmallTreasureList();


	virtual string* serialize();

private:
    vector<Tile*>* tileList;
    vector<Dwelling*>* dwellingList;
	vector<Site*>* siteList;
	vector<Warning*>* warningList;
	vector<Sound*>* soundList;
	vector<Treasure*>* smallTreasureList;
	vector<Treasure*>* largeTreasureList;

	void createTiles();
	void createTreasures();
	void createMonsters();
	/*
    *   addTile
    *   In:         Pointer to the tile you wish to add. 
    *   Purpose:    To Add a tile to the map with its desired paths betwen other tiles.
    */
    void addTile(Tile* newTile);
};

#endif // BOARD_H