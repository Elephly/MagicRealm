#ifndef SOUND_H
#define SOUND_H

#include "shared.h"
#include "commonlibrary_global.h"

#include "chit.h"

class COMMONLIBRARY_EXPORT Sound: public Chit{
public:
    Sound(string n, bool hide, TileType myTileType, int clnum);
    virtual int getClearingNum();
	virtual ChitType getType();

private:
    int clearingLocation;
};

#endif //SOUND_H