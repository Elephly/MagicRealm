#include "warning.h"

Warning::Warning(string n, bool hide, TileType myTileType): Chit(n, hide, myTileType)
{
}

ChitType Warning::getType()
{
	return CHIT_WARNING;
}