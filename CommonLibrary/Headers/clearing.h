#ifndef CLEARING_H
#define CLEARING_H

#include <vector>
#include "character.h"
#include "shared.h"
#include "commonlibrary_global.h"
#include "path.h"

//forward declare
class Character;
class Path;
class Tile;

//Abstract class, extend this with all 3 clearing types
class COMMONLIBRARY_EXPORT Clearing{
public:
	Clearing(int clNum, Tile* parentTile);
    ~Clearing();
    /*
    *   addCharacterToClearing
    *   in: The player's character to be added to the clearing.
    */
    void addCharacterToClearing(Character player);

    /*
    *   chartPath
    *   in: Pointer to the path you wish to add to the clearing
    */
    void chartPath(Path* newPath);

    /*
    *   getClearingNum
    *   Out:    The number in the clearing
    */
    int getClearingNum();

    //TODO: Add the get dwelling object here.

private:
    //list of characters in a clearing.
	vector<Character> characters;

    //list of paths in a clearing.
	vector<Path> pathways;

    //Tile the clearing is in.
    Tile myTile;

    //clearing number  
    int ID;

    //TODO: Add Dwelling object here!!!!!
};

#endif // CLEARING_H