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
	location = NULL;
	alive = true;
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

bool Monster::isAlive()
{
	return alive;
}

void Monster::kill()
{
	alive = false;
	move(NULL);
}
char Monster::getHarm()
{
	return harm;
}

int Monster::getAS()
{
	return attackSpeed;
}

int Monster::getMS()
{
	return moveSpeed;
}

int Monster::getSharp()
{
	return sharpness;
}

void Monster::move(Clearing* loc)
{
	if (location != NULL)
		location->removeMonster(this);
	location = loc;
	if(loc != NULL)
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