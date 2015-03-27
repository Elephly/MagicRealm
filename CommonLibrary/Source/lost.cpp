#include "lost.h"

Lost::Lost(string n, bool hide, TileType myTileType, vector<Chit *> * inside): Chit(n,hide, myTileType)
{
	contains = inside;
}

ChitType Lost::getType()
{
	return CHIT_LOST;
}

vector<Chit *>* Lost::getContents()
{
	return contains;
}