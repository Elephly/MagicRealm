#include "dwelling.h"

Dwelling::Dwelling(DwellingType t, Clearing* loc, bool hide)
{
	type = t;
	name = getTypeString(t);
    location = loc;
    hidden = hide;
}

string Dwelling::getName()
{
    return name;
}

Clearing* Dwelling::getLocation()
{
    return location;
}

bool Dwelling::isHidden()
{
    return hidden;
}

DwellingType Dwelling::getType()
{
	return type;
}

string Dwelling::toString()
{
	string out = location->getTile()->getName();
	out += " clearing ";
	out += location->getClearingNum();
	out += (hidden ? " hidden " : " ");
	out += name;
	return out;
}

char* Dwelling::getTypeString(DwellingType t)
{
	switch (t)
	{
	case CHAPEL:
		return "Chapel";
		break;
	case GUARD:
		return "Guard";
		break;
	case HOUSE:
		return "House";
		break;
	case INN:
		return "Inn";
		break;
	default:
		return "?";
		break;
	}
}