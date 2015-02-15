#ifndef CLEARING_H
#define CLEARING_H

#include <vector>
#include "character.h"
#include "shared.h"
#include "commonlibrary_global.h"

//forward declare
class Character;

//Abstract class, extend this with all 3 clearing types
class COMMONLIBRARY_EXPORT Clearing{
public:
	Clearing();

private:
	vector<Character> characters;
};

#endif // CLEARING_H