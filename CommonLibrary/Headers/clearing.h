#ifndef CLEARING_H
#define CLEARING_H

#include <vector>
#include "character.h"
#include "shared.h"
#include "commonlibrary_global.h"
#include "path.h"
#include "tile.h"

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

    //toString method, returns POINTER TO STRING, MUST BE DELETED
    string* toString();


    //TODO: Add the get dwelling object here.

private:
    //list of characters in a clearing.
	vector<Character*>* characters;

    //list of paths in a clearing.
	vector<Path*>* pathways;

    //Tile the clearing is in.
    Tile* myTile;

    //clearing number  
    int ID;

    //TODO: Add Dwelling object here!!!!!
};

#endif // CLEARING_H