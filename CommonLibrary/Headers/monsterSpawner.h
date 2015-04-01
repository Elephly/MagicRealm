#ifndef MONSTERSPAWN_H
#define MONSTERSPAWN_H

#include "shared.h"
#include "commonlibrary_global.h"
#include "clearing.h"
#include "monster.h"

class Monster;

class COMMONLIBRARY_EXPORT MonsterSpawner
{
public:
	MonsterSpawner();
	vector<Monster*>* getMonsterList();
	vector<Monster*>* spawn(Clearing* targetClearing, int dieRoll);

private:
	class Element
	{
	public:
		Element(vector<Monster*>* monsterArray);
		vector<Monster*>* spawnMonsters();
		bool getSpawned();
	private: 
		Monster* monster;
		int numMonster;
		vector<Monster*>* monsterList; 
		bool spawned;
		
	};
	vector<Element*>* flutterSmokeM1;
	vector<Element*>* smokeCSlitherRoarC1;
	vector<Element*>* hoard1;
	vector<Element*>* lair1;
	vector<Element*>* dankW2;
	vector<Element*>* dankCSlither2;
	vector<Element*>* altar2;
	vector<Element*>* shrine2;
	vector<Element*>* ruinsW3;
	vector<Element*>* bonesW3;
	vector<Element*>* ruinsCPatterCHowlC3;
	vector<Element*>* pool3;
	vector<Element*>* bonesMRoarMStinkM4;
	vector<Element*>* stinkCBonesCRoarC4;
	vector<Element*>* vault4;
	vector<Element*>* stinkMDankMPatterM5;
	vector<Element*>* cairns5;
	vector<Element*>* statue5;
	vector<Element*>* ruinsMBonesMFlutterHowlM6;

};
#endif