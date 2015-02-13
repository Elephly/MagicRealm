#ifndef CLEARING_H
#define CLEARING_H

#include <vector>
#include "character.h"

class Clearing{
public:
	Clearing();
	~Clearing();

private:
	std::vector<Character> characters;
};

#endif // CLEARING_H