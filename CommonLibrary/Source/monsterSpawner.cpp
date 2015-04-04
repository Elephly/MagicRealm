#include "monsterSpawner.h"

MonsterSpawner::Element::Element()
{
	monsterList = new vector<Monster*>;
	spawned = false;
}

vector<Monster*>* MonsterSpawner::Element::spawnMonsters(Clearing* targetClearing)
{
	spawned = true;
	for(vector<Monster*>::iterator it = monsterList->begin(); it != monsterList->end(); ++it){
		(*it)->move(targetClearing);
	}
	return monsterList;

}
bool MonsterSpawner::Element::getSpawned()
{
	return spawned;
}
void MonsterSpawner::Element::addMonster(Monster* newMonster)
{
    monsterList->push_back(newMonster);
}

MonsterSpawner::MonsterSpawner()
{
	flutterSmokeM1 = new vector<Element*>;
	Element* mList = new Element();
    m = new Monster("Heavy Flying Dragon", 'H', 4, 0, 4, 5, 5);
	mList->addMonster(m);
	mList->addMonster(new Monster("Heavy Flying Dragon", 'H', 4, 0, 4, 5, 5));
	flutterSmokeM1->push_back(mList);
    mList = NULL;

	smokeCSlitherRoarC1 = new vector<Element*>;
	mList = new Element();
	//first entry
	mList->addMonster(new Monster("Heavy Dragon", 'H', 4, 0, 4, 5, 5));
	smokeCSlitherRoarC1->push_back(mList);
    mList = NULL;
	//second entry
	mList = new Element();
	mList->addMonster(new Monster("Tremendous Dragon", 'H', 5, 0, 6, 10, 10));
	smokeCSlitherRoarC1->push_back(mList);
    mList = NULL;

	hoard1 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster ("Tremendous Flying Dragon", 'M', 3, 0, 4, 12, 12));
	hoard1->push_back(mList);
    mList = NULL;

	lair1 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster ("Tremendous Dragon", 'H', 5, 0, 6, 10, 10));
	lair1->push_back(mList);
    mList = NULL;

	dankW2 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Viper", 'M', 4, 2, 4, 1, 2));
	mList->addMonster(new Monster("Viper", 'M', 4, 2, 4, 1, 2));
	dankW2->push_back(mList);
    mList = NULL;

	dankCSlither2 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Heavy Serpent", 'M', 4, 0, 3, 4, 4));
	mList->addMonster(new Monster("Heavy Serpent", 'M', 4, 0, 3, 4, 4));
	dankCSlither2->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Tremendous Serpent", 'L', 4, 0, 4, 7, 7));
	dankCSlither2->push_back(mList);
    mList = NULL;

	altar2 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Demon", 'V', 2, 0, 4, 8, 8));
	altar2->push_back(mList);
    mList = NULL;

	shrine2 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Winged Demon", 'V', 3, 0, 3, 8, 8));
	shrine2->push_back(mList);
    mList = NULL;

	ruinsW3 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Wolf", 'L', 4, 0, 3, 0, 1));
	mList->addMonster(new Monster("Wolf", 'L', 4, 0, 3, 0, 1));
	mList->addMonster(new Monster("Wolf", 'L', 4, 0, 3, 0, 1));
	mList->addMonster(new Monster("Wolf", 'M', 5, 0, 3, 0, 1));
	mList->addMonster(new Monster("Wolf", 'M', 5, 0, 3, 0, 1));
	mList->addMonster(new Monster("Wolf", 'M', 5, 0, 3, 0, 1));
	ruinsW3->push_back(mList);
    mList = NULL;

	bonesW3 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Ogre", 'T', 5, 0, 5, 0, 2));
	mList->addMonster(new Monster("Ogre", 'T', 5, 0, 5, 0, 2));
	bonesW3->push_back(mList);
    mList = NULL;

	ruinsCPatterCHowlC3 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	ruinsCPatterCHowlC3->push_back(mList);
    mList = NULL;
	mList = new Element();
	//NOTE: A is to replace something that doesnt have harm letter
	mList->addMonster(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	ruinsCPatterCHowlC3->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->addMonster(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	ruinsCPatterCHowlC3->push_back(mList);
    mList = NULL;

	pool3 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Octopus", 'L', 4, 0, 2, 8, 8));
	pool3->push_back(mList);
    mList = NULL;

	bonesMRoarMStinkM4 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Giant", 'H', 5, 0, 5, 8, 8));
	bonesMRoarMStinkM4 ->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Giant", 'H', 5, 0, 5, 8, 8));
	bonesMRoarMStinkM4->push_back(mList);
    mList = NULL;

	stinkCBonesCRoarC4 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Heavy Troll", 'M', 4, 0, 4, 5, 5));
	mList->addMonster(new Monster("Heavy Troll", 'M', 4, 0, 4, 5, 5));
	stinkCBonesCRoarC4->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Tremendous Troll", 'H', 4, 0, 4, 8, 8));
	stinkCBonesCRoarC4->push_back(mList);
    mList = NULL;

	vault4 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Tremendous Troll", 'H', 4, 0, 4, 8, 8));
	vault4->push_back(mList);
    mList = NULL;

	stinkMDankMPatterM5 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3));
	stinkMDankMPatterM5->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3));
	stinkMDankMPatterM5->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3));
	stinkMDankMPatterM5->push_back(mList);
    mList = NULL;

	cairns5 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Tremendous Spider", 'M', 4, 0, 3, 6, 6));
	cairns5->push_back(mList);
    mList=NULL;

	statue5 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Imp", 'A', 2, 0, 2, 2, 1));
	statue5->push_back(mList);
    mList = NULL;

	ruinsMBonesMFlutterHowlM6 = new vector<Element*>;
	mList = new Element();
	mList->addMonster(new Monster("Giant Bat", 'M', 4, 0, 3, 3, 3));
	ruinsMBonesMFlutterHowlM6->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	mList->addMonster(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	ruinsMBonesMFlutterHowlM6->push_back(mList);
    mList = NULL;
	mList = new Element();
	mList->addMonster(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	mList->addMonster(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	mList->addMonster(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	ruinsMBonesMFlutterHowlM6->push_back(mList);
    blah();
}

void MonsterSpawner::blah()
{
    cout << "BLAH" <<endl;
}

vector<Monster*>* MonsterSpawner::getMonsterList()
{
	cout << "Not Implemented" <<endl;
	return NULL;
}

vector<Monster*>* MonsterSpawner::spawn(Clearing* targetClearing, int dRoll)
{
	Tile* targetTile = targetClearing->getTile();
	string warningName = targetTile->getWarningChit()->getName();
	string siteSoundName = "";
	Chit* siteSoundChit = targetClearing->getTile()->getSiteOrSoundChit();
	if(siteSoundChit)
		siteSoundName = siteSoundChit->getName();
	switch(dRoll){
	case 1:
		if(warningName == "SMOKE M" || siteSoundName == "Flutter 1" || siteSoundName == "Flutter 2")
			return spawnMonsters(flutterSmokeM1, targetClearing);

		else if(warningName == "SMOKE C" || siteSoundName == "Slither 3" || siteSoundName == "Slither 6"
			|| ((siteSoundName == "Roar 4" || siteSoundName == "Roar 6") && targetTile->getType() == TILE_CAVES))
			return spawnMonsters(smokeCSlitherRoarC1, targetClearing);

		else if(siteSoundName == "Hoard")
			return spawnMonsters(hoard1, targetClearing); 

		else if(siteSoundName == "Lair")
			return spawnMonsters(lair1, targetClearing);
		else //did not find any correct matchup to spawn monsters on roll 1.
			return NULL;
	case 2:
		if(warningName == "DANK W")
			return spawnMonsters(dankW2, targetClearing);

		else if(warningName == "DANK C" || siteSoundName == "Slither 3" ||siteSoundName == "Slither 6")
			return spawnMonsters(dankCSlither2, targetClearing);

		else if(siteSoundName == "Altar")
			return spawnMonsters(altar2, targetClearing);

		else if(siteSoundName == "Shrine")
			return spawnMonsters(shrine2, targetClearing);

		else //did not find any correct matchup to spawn monsters on roll 2.
			return NULL;
	case 3:
		if(warningName == "RUINS W")
			return spawnMonsters(ruinsW3, targetClearing);

		else if(warningName == "BONES W")
			return spawnMonsters(bonesW3, targetClearing);

		else if(warningName == "RUINS C" || 
			((siteSoundName == "Patter 2" || siteSoundName == "Patter 5" || siteSoundName == "Howl 4" || siteSoundName == "Howl 5") && targetTile->getType() == TILE_CAVES))
			return spawnMonsters(ruinsCPatterCHowlC3, targetClearing);

		else if(siteSoundName == "Pool")
			return spawnMonsters(pool3, targetClearing);

		else //did not find any correct matchup to spawn monsters on roll 3.
			return NULL;
	case 4:
		if(warningName == "BONES M" || warningName == "STINK M" || 
			((siteSoundName == "Roar 4" || siteSoundName == "Roar 6") && targetTile->getType() == TILE_MOUNTAIN))
			return spawnMonsters(bonesMRoarMStinkM4, targetClearing);

		else if(warningName == "STINK C" || warningName == "BONES C" ||
			((siteSoundName == "Roar 4" || siteSoundName == "Roar 6") && targetTile->getType() == TILE_CAVES))
			return spawnMonsters(stinkCBonesCRoarC4, targetClearing);

		else if(siteSoundName == "Vault")
			return spawnMonsters(vault4, targetClearing);

		else //did not find any correct matchup to spawn monsters on roll 4.
			return NULL;
	case 5:
		if(warningName == "STINK M" || warningName == "DANK M" ||
			((siteSoundName == "Patter 2" || siteSoundName == "Patter 5") && targetTile->getType() == TILE_MOUNTAIN))
			return spawnMonsters(stinkMDankMPatterM5, targetClearing);
		else if(siteSoundName == "Cairns")
			return spawnMonsters(cairns5, targetClearing);
		else if (siteSoundName == "Statue")
			return spawnMonsters(statue5, targetClearing);
		else
			return NULL;
	case 6:
		if(warningName == "RUINS M" || warningName == "BONES M" || (
			(siteSoundName == "Flutter 1" || siteSoundName == "Flutter 2" || siteSoundName == "Howl 4" || 
			siteSoundName == "Howl 5") && targetTile->getType() == TILE_MOUNTAIN))
			return spawnMonsters(ruinsMBonesMFlutterHowlM6, targetClearing);
	default:
		cout << "ERR: MonsterSpawner::Spawn bad dice roll";	return NULL;
	}
	cout << "Not Implemented" <<endl;
	return NULL;
}

vector<Monster*>* MonsterSpawner::spawnMonsters(vector<Element*>* elementList, Clearing* targetClearing)
{
	for(vector<Element*>::iterator it = elementList->begin(); it != elementList->end(); ++it){
		if(!(*it)->getSpawned())
			return (*it)->spawnMonsters(targetClearing);
	}
	//Monsters are all already on the map, therefore nothing left to return.
	return NULL;
}