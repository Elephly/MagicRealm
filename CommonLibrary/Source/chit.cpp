#include "chit.h"

Chit::Chit(string n, bool hide, TileType myCompatibleTileType)
{
    name = n;
    hidden = hide;
	compatibleTile = myCompatibleTileType;
}

bool Chit::isHidden()
{
    return hidden;
}

string Chit::getName()
{
    return name;
}

TileType Chit::getTileType()
{
	return compatibleTile;
}
void Chit::unhide()
{
    hidden = true;
}

int Chit::getClearingNum()
{
	return -1;
}

Treasure* Chit::loot(int diceUsed)
{
    return NULL;
}

vector<Chit *>* Chit::getContents()
{
	return NULL;
}

string* Chit::serialize() {
	stringstream s;

	s << "Chit";
	s << CLASSDELIM;
	s << name;

	return new string(s.str());
}