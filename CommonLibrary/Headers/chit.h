#ifndef CHIT_H
#define CHIT_H

#include "shared.h"
#include "commonlibrary_global.h"
#include "treasure.h"
#include "serializer.h"
#include <vector>
#include <sstream>

class COMMONLIBRARY_EXPORT Chit : public Serializer {
public:
    Chit(string n, bool hide, TileType myCompatibleTileType);
    bool isHidden();
    string getName();
    /*
    *   unHide()
    *   Purpose:    to make the chit not hidden
    */
    void unhide();

	//returns the type of tiles that the chit would be found on.
	TileType getTileType();

    virtual Treasure* loot(int location);
	virtual int getClearingNum();
	virtual ChitType getType() = 0;
	virtual vector<Chit *>* getContents();
	virtual string* serialize();
protected:
    string name;
    bool hidden;
	TileType compatibleTile;
};

#endif //SITE_H