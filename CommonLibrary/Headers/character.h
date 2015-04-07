#ifndef CHARACTER_H
#define CHARACTER_H

#include "commonlibrary_global.h"
#include "clearing.h"
#include "shared.h"
#include "equipment.h"
#include "serializer.h"
#include <vector>
#include <string>
#include "chit.h"

//forward declare
class Clearing;
class Board;
class Path;


class  COMMONLIBRARY_EXPORT Character : public Serializer{
public:
	Character(CharacterType type);
	Character(string* serialString);
	int getGold();
	vector<Equipment *>* getEquipment();
	Clearing* getCurrentLocation();
	void moveToClearing(Clearing *destination);
	bool hasAdvantage(CharAdvantages);
	CharacterType getType();
	static char* getTypeString(CharacterType t);
	static vector<DwellingType>* getStartLocations(CharacterType t);
	virtual string* serialize();

	//returns the first advantage is passed true, the second is false
	CharAdvantages getAdvantage(bool firstAdvantage);

	void addGold(int);
	void addFame(int);
	void addNotoriety(int);

	int getFame();
	int getNotoriety();

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

    /*
    *   isHidden
    *   out: whether or not the character is hidden
    */
    bool isHidden();

    /*
    *   toggleHide()
    *   toggles whether or not the character is hidden
    */
    void toggleHide();

	void discover(Chit* newDiscovery);

	bool hasDiscovered(Chit* checkDiscovery);

    bool isBlocked();
    void setBlock(bool newBlock);

private:
	CharacterType myType;
    bool hidden;
    bool blocked;
	int gold;
	int fame;
	int notoriety;
	Clearing *location;
	CharAdvantages advantages[2];
	vector<Equipment *> *equipment;
    vector<Path *>* knownPaths;
	vector<Chit* >* discoveries;

	//private functions
	void init(CharacterType);
	void initAmazon();
	void initBlackknight();
	void initCaptain();
	void initDwarf();
	void initElf();
	void initSwordsman();
};

#endif // CHARACTER_H