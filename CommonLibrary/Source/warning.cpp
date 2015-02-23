#include "warning.h"

Warning::Warning(string n, bool hide): Chit(n, hide)
{
}

ChitType Warning::getType()
{
	return CHIT_WARNING;
}