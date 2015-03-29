#ifndef MONSTER_H
#define MONSTER_H

#include "shared.h"
#include "commonlibrary_global.h"

class COMMONLIBRARY_EXPORT Monster
{
public:
    Monster(string name, int fame, int notoriety);

    int getFame();
	int getNotoriety();
	string getName();
	int getID();


private:
	static int currID;
    int fame;
	int notoriety;
	string name;
	int id;

};

#endif //SOUND_H