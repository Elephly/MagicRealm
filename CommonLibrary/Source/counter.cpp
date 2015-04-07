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