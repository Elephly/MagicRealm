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
    masterList = new vector<Monster*>;
	flutterSmokeM1 = new vector<Element*>;
	Element* mList = new Element();
	//setting up ghosts
	ghosts = new vector<Monster*>;
	Monster* m = new Monster("Ghost", 'H', 4, 0, 4, 0, 2);
	ghosts->push_back(m);
	masterList->push_back(m);
	m = NULL;
	m = new Monster("Ghost", 'H', 4, 0, 4, 0, 2);
	ghosts->push_back(m);
	masterList->push_back(m);
	m = NULL;

    m = new Monster("Heavy Flying Dragon", 'H', 4, 0, 4, 5, 5);
	mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Heavy Flying Dragon", 'H', 4, 0, 4, 5, 5);
    mList->addMonster(m);
    masterList->push_back(m);
	flutterSmokeM1->push_back(mList);
    mList = NULL;
    m = NULL;

	smokeCSlitherRoarC1 = new vector<Element*>;
	mList = new Element();
	//first entry
    m = new Monster("Heavy Dragon", 'H', 4, 0, 4, 5, 5);
	mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	smokeCSlitherRoarC1->push_back(mList);
    mList = NULL;

	//second entry
	mList = new Element();
	m = new Monster("Tremendous Dragon", 'H', 5, 0, 6, 10, 10);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	smokeCSlitherRoarC1->push_back(mList);
    mList = NULL;

	hoard1 = new vector<Element*>;
	mList = new Element();
	m = new Monster ("Tremendous Flying Dragon", 'M', 3, 0, 4, 12, 12);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	hoard1->push_back(mList);
    mList = NULL;

	lair1 = new vector<Element*>;
	mList = new Element();
	m = new Monster ("Tremendous Dragon", 'H', 5, 0, 6, 10, 10);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	lair1->push_back(mList);
    mList = NULL;

	dankW2 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Viper", 'M', 4, 2, 4, 1, 2);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Viper", 'M', 4, 2, 4, 1, 2);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	dankW2->push_back(mList);
    mList = NULL;

	dankCSlither2 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Heavy Serpent", 'M', 4, 0, 3, 4, 4);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Heavy Serpent", 'M', 4, 0, 3, 4, 4);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	dankCSlither2->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Tremendous Serpent", 'L', 4, 0, 4, 7, 7);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	dankCSlither2->push_back(mList);
    mList = NULL;

	altar2 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Demon", 'V', 2, 0, 4, 8, 8);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	altar2->push_back(mList);
    mList = NULL;

	shrine2 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Winged Demon", 'V', 3, 0, 3, 8, 8);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	shrine2->push_back(mList);
    mList = NULL;

	ruinsW3 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Wolf", 'L', 4, 0, 3, 0, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Wolf", 'L', 4, 0, 3, 0, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Wolf", 'L', 4, 0, 3, 0, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Wolf", 'M', 5, 0, 3, 0, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Wolf", 'M', 5, 0, 3, 0, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Wolf", 'M', 5, 0, 3, 0, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	ruinsW3->push_back(mList);
    mList = NULL;

	bonesW3 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Ogre", 'T', 5, 0, 5, 0, 2);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Ogre", 'T', 5, 0, 5, 0, 2);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	bonesW3->push_back(mList);
    mList = NULL;

	ruinsCPatterCHowlC3 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	ruinsCPatterCHowlC3->push_back(mList);
    mList = NULL;
	mList = new Element();
	//NOTE: A is to replace something that doesnt have harm letter
	m = new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	ruinsCPatterCHowlC3->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	ruinsCPatterCHowlC3->push_back(mList);
    mList = NULL;

	pool3 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Octopus", 'L', 4, 0, 2, 8, 8);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	pool3->push_back(mList);
    mList = NULL;

	bonesMRoarMStinkM4 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Giant", 'H', 5, 0, 5, 8, 8);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	bonesMRoarMStinkM4 ->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Giant", 'H', 5, 0, 5, 8, 8);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	bonesMRoarMStinkM4->push_back(mList);
    mList = NULL;

	stinkCBonesCRoarC4 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Heavy Troll", 'M', 4, 0, 4, 5, 5);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Heavy Troll", 'M', 4, 0, 4, 5, 5);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	stinkCBonesCRoarC4->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Tremendous Troll", 'H', 4, 0, 4, 8, 8);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	stinkCBonesCRoarC4->push_back(mList);
    mList = NULL;

	vault4 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Tremendous Troll", 'H', 4, 0, 4, 8, 8);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	vault4->push_back(mList);
    mList = NULL;

	stinkMDankMPatterM5 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	stinkMDankMPatterM5->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	stinkMDankMPatterM5->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	stinkMDankMPatterM5->push_back(mList);
    mList = NULL;

	cairns5 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Tremendous Spider", 'M', 4, 0, 3, 6, 6);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	cairns5->push_back(mList);
    mList=NULL;

	statue5 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Imp", 'A', 2, 0, 2, 2, 1);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	statue5->push_back(mList);
    mList = NULL;

	ruinsMBonesMFlutterHowlM6 = new vector<Element*>;
	mList = new Element();
	m = new Monster("Giant Bat", 'M', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	ruinsMBonesMFlutterHowlM6->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	ruinsMBonesMFlutterHowlM6->push_back(mList);
    mList = NULL;
	mList = new Element();
	m = new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	m = new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3);
    mList->addMonster(m);
    masterList->push_back(m);
    m = NULL;
	ruinsMBonesMFlutterHowlM6->push_back(mList);
}
vector<Monster*>* MonsterSpawner::getMonsterList()
{
	return masterList;
}

Monster* MonsterSpawner::getMonsterByID(int id)
{
    for(vector<Monster*>::iterator iter = masterList->begin(); iter!= masterList->end(); ++iter)
        if((*iter)->getID() == id)
            return *iter;

    //could not find monster by ID
    cout << "WARN MonsterSpawner::getMonsterbyID ::: did not find monster with ID" <<endl;
    return NULL;
}

vector<Monster*>* MonsterSpawner::spawn(Clearing* targetClearing, Chit* siteSoundChit, int dRoll)
{
	Tile* targetTile = targetClearing->getTile();
	string warningName = targetTile->getWarningChit()->getName();
	string siteSoundName = "";
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

vector<Monster*>* MonsterSpawner::getGhosts()
{
	return ghosts;
}