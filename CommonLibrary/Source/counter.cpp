#include "counter.h"

int Counter::currID = 0;

Counter::Counter(CounterType ct, char si, int s, int f)
{
	type = ct;
	size = si;
	speed = s;
	fatigue = f;
	id = currID;
	++currID;

	wounded = false;
	resting = false;
}

CounterType Counter::getType()
{
	return type;
}

char Counter::getSize()
{
	return size;
}

int Counter::getSpeed()
{
	return speed;
}

int Counter::getFatigue(){
	return fatigue;
}

int Counter::getID()
{
	return id;
}

bool Counter::isAvailable()
{
	return !wounded && !resting;
}

void Counter::wound()
{
	wounded = true;
}

void Counter::heal()
{
	wounded = false;
}

bool Counter::isResting()
{
	return resting;
}

void Counter::setRest(bool r)
{
	resting = r;
}