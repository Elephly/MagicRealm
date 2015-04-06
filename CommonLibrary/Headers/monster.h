#ifndef MONSTER_H
#define MONSTER_H

#include "shared.h"
#include "commonlibrary_global.h"
#include "clearing.h"

class Clearing;

class COMMONLIBRARY_EXPORT Monster
{
public:
    Monster(string name, char harmLetter, int as, int sharp, int ms, int fame, int notoriety);
    
	int getFame();
	int getNotoriety();
	string getName();
	int getID();
	char getHarm();
	int getAS();
	int getMS();
	int getSharp();

	void move(Clearing* loc);

	//NOTE: if null, has not spawned yet.
	Clearing* getLocation();

    bool isBlocked();
    void setBlock(bool newBlock);

private:
	static int currID;
	char harm;
	int attackSpeed;
	int sharpness;
	int moveSpeed;
    int fame;
	int notoriety;
	string name;
	int id;
	Clearing* location;

    bool blocked;

};

#endif //SOUND_H