#ifndef CHARACTER_H
#define CHARACTER_H

#include "commonlibrary_global.h"
#include "clearing.h"
#include "shared.h"
#include "equipment.h"
#include "serializer.h"
#include <vector>
#include <string>

//forward declare
class Clearing;
class Board;
class Path;


class  COMMONLIBRARY_EXPORT Character : public Serializer{
public:
	Character(CharacterTypes type);
	Character(string* serialString);
	int getGold();
	vector<Equipment *>* getEquipment();
	Clearing* getCurrentLocation();
	void moveToClearing(Clearing *destination);
	bool hasAdvantage(CharAdvantages);
	CharacterTypes getType();
	static char* getTypeString(CharacterTypes t);
	static vector<DwellingType>* getStartLocations(CharacterTypes t);
	virtual string* serialize();

    /*
    *   addPath
    *   in:     Pointer to the Path
    */
    void addPath(Path* discoveredPath);

    /*
    *   isDiscovered
    *   in:     Path you wish to check discovery
    *   out:    boolean whether that path is discovered.
    */
    bool isDiscovered(Path*);

private:
	CharacterTypes myType;
	int gold;
	Clearing *location;
	CharAdvantages advantages[2];
	vector<Equipment *> *equipment;
    vector<Path *>* knownPaths;

	//private functions
	void init(CharacterTypes);
	void initAmazon();
	void initBlackknight();
	void initCaptain();
	void initDwarf();
	void initElf();
	void initSwordsman();
};

#endif // CHARACTER_H