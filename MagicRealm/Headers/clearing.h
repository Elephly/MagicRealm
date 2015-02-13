#ifndef CLEARING_H
#define CLEARING_H

#include <vector>
#include "character.h"

//Abstract class, extend this with all 3 clearing types
class Clearing{
public:
	virtual ~Clearing();

private:
	std::vector<Character> characters;
};

#endif // CLEARING_H