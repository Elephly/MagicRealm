#include "sound.h"

Sound::Sound(string n, bool hide, TileType myTileType, int clnum): Chit(n, hide, myTileType)
{
    clearingLocation = clnum;
}

int Sound::getClearingNum()
{
    return clearingLocation;
}

ChitType Sound::getType()
{
	return CHIT_SOUND;
}