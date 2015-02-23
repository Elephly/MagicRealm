#include "lost.h"

Lost::Lost(string n, bool hide, vector<Chit *> * inside): Chit(n,hide)
{
	contains = inside;
}

ChitType Lost::getType()
{
	return CHIT_LOST;
}

vector<Chit *>* Lost::getContents()
{
	return contains;
}