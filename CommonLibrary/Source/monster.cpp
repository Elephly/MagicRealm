#include "monster.h"

int Monster::currID = 0;
Monster::Monster(string n, char harmLetter, int as, int sharp, int ms, int f, int notor)
{
	name = n;
	harm = harmLetter;
	attackSpeed = as;
	sharpness = sharp;
	moveSpeed = ms;
	fame = f;
	notoriety = notor;
	id = currID;
	++currID;
    blocked = false;
}

int Monster::getFame()
{
	return fame;
}

int Monster::getNotoriety()
{
	return notoriety;
}

string Monster::getName()
{
	return name;
}

int Monster::getID()
{
	return id;
}

void Monster::move(Clearing* loc)
{
	location = loc;
	loc->addMonster(this);
}

Clearing* Monster::getLocation()
{
	return location;
}

bool Monster::isBlocked()
{
    return blocked;
}

void Monster::setBlock(bool newBlock)
{
    blocked = newBlock;
}