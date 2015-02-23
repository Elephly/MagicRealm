#ifndef CLEARING_H
#define CLEARING_H

#include <vector>
#include "character.h"
#include "shared.h"
#include "commonlibrary_global.h"
#include "path.h"
#include "tile.h"
#include "serializer.h"
#include "board.h"
#include "chit.h"

//forward declare
class Character;
class Path;
class Tile;
class Board;
class Dwelling;

//Abstract class, extend this with all 3 clearing types
class COMMONLIBRARY_EXPORT Clearing : public Serializer {
public:
	Clearing(int clNum, Tile* parentTile, ClearingType ct);
	Clearing(string* serialString, Board* board);
    ~Clearing();
    /*
    *   addCharacter
    *   in: The player's character to be added to the clearing.
    */
    void addCharacter(Character* player);
    /*
    *   removeCharacter
    *   in: The player's character to be remove to the clearing.
    */
    void removeCharacter(Character* player);

    /*
    *   addPath
    *   in: Pointer to the path you wish to add to the clearing
    */
    void addPath(Path* newPath);
    /*
    *   removePath
    *   in: Pointer to the path you wish to remove from the clearing
    */
    void removePath(Path* oldPath);

    /*
    *   in:         DwellingType to be built
    *   out:        The Dwelling that was built
    *   Purpose:    Build The Dwelling and assigns it to this clearing.
    */
    Dwelling* buildDwelling(DwellingType dt);

    /*
    *   getDwelling
    *   out: Dwelling pointer in the clearing (null otherwise)
    */
    Dwelling* getDwelling();

    /*
    *   getTile
    *   Out:    Pointer to the clearing's tile
    */
    Tile* getTile();
    
    /*
    *   getPaths
    *   out:    vector of paths
    */
    vector<Path*>* getPaths();

    /*
    *   getClearingNum
    *   Out:    The number in the clearing
    */
    int getClearingNum();

    /*
    *   getClearingType
    *   Out:    The Type of Clearing
    */
    ClearingType getClearingType();

    //toString method, returns POINTER TO STRING, MUST BE DELETED
    string* toString();

	const vector<Character*>* getCharacters();

	virtual string* serialize();

	static char* getTypeString(ClearingType);

	/*
	*	returns whether or not a clearing is lootable.
	*	
	*/
	bool lootable();

private:
    //list of characters in a clearing.
	vector<Character*>* characters;

    //list of paths in a clearing.
	vector<Path*>* pathways;

    //Tile the clearing is in.
    Tile* myTile;

    //clearing number  
    int ID;

    ClearingType myType;

    Dwelling* myDwelling;
};

#endif // CLEARING_H