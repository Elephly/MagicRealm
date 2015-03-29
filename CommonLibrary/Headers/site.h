#ifndef SITE_H
#define SITE_H

#include "shared.h"
#include "commonlibrary_global.h"

#include "chit.h"
#include "treasure.h"

class COMMONLIBRARY_EXPORT Site: public Chit {
public:
    Site(string n, bool hide, TileType myTileType, int clearingLocation);
    ~Site();
    virtual int getClearingNum();
    /*
    *   loot
    *   in:         array index of treasure location
    *   out:        Treasure that you got
    *   Purpose:    Removes the treasure from the list
    */
    virtual Treasure* loot(int location);
	virtual ChitType getType();

	/*
	*	storeTreasure
	*	in: Treasure let
	*	saves the trasurelist as the trasure
	*/
	void storeTreasure(vector<Treasure*>* myTreasure);


private:
    int clearingLocation;
    vector <Treasure*> * trove;
};

#endif //SITE_H