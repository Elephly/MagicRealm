#include "lost.h"

Lost::Lost(string n, bool hide, TileType myTileType): Chit(n,hide, myTileType)
{
}

void Lost::populateCity(vector<Chit*>* inside)
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