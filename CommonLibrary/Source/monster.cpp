#include "monster.h"

int Monster::currID = 0;
Monster::Monster(string n, int f, int notor)
{
	name = n;
	fame = f;
	notoriety = notor;
	id = currID;
	++currID;
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
