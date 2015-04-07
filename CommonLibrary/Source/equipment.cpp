#include "equipment.h"

Equipment::Equipment(string n) 
{
	name = n;
}

string Equipment::getName()
{
	return name;
}

bool Equipment::getActive()
{
	return false;
}

void Equipment::setActive(bool act)
{
	cout << "Setting Active on Equipment does not do anything" <<endl;
}

bool Equipment::isDamaged()
{
	return false;
}

void Equipment::setDamaged(bool status)
{
	cout << "Setting Damage on Equipment does not do anything" << endl;
}