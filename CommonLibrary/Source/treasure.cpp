#include "treasure.h"

Treasure::Treasure(string n, TreasureType t)
{
    name = n;
    type = t;

	//getting the random values assigned
	generateGold();
	generateFame();
	generateNotoriety();
}

string Treasure::getName()
{
    return name;
}

int Treasure::getWorth()
{
    return goldValue;
}

TreasureType Treasure::getType()
{
    return type;
}

void Treasure::generateGold()
{
	//lowerbound gold value depending on type
	int lowerBound = 0;

	switch(type){
	case SMALL:		lowerBound = 10;	break;
	case LARGE:		lowerBound = 25;	break;
	case GREAT:		lowerBound = 40;	break;
	}

	goldValue = rand() % 50 + lowerBound;

}

void Treasure::generateFame()
{ 
	//unknown if actually calculates random number
	fameValue = rand() % (30 - -5 +1);
}

void Treasure::generateNotoriety()
{
	notorietyValue = rand() % 20 + 1;
}