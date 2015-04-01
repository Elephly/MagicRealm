#include "monsterSpawner.h"

MonsterSpawner::Element::Element(vector <Monster*>* monList)
{
	monsterList = monList;
	spawned = false;
}

vector<Monster*>* MonsterSpawner::Element::spawnMonsters()
{
	spawned = true;
	return monsterList;

}
bool MonsterSpawner::Element::getSpawned()
{
	return spawned;
}

MonsterSpawner::MonsterSpawner()
{
	flutterSmokeM1 = new vector<Element*>;
	vector< Monster*>* mList = new vector<Monster*>;
	mList->push_back(new Monster("Heavy Flying Dragon", 'H', 4, 0, 4, 5, 5));
	mList->push_back(new Monster("Heavy Flying Dragon", 'H', 4, 0, 4, 5, 5));
	flutterSmokeM1->push_back(new Element(mList));

	smokeCSlitherRoarC1 = new vector<Element*>;
	mList = new vector<Monster*>;
	//first entry
	mList->push_back(new Monster("Heavy Dragon", 'H', 4, 0, 4, 5, 5));
	smokeCSlitherRoarC1->push_back(new Element(mList));
	//second entry
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Tremendous Dragon", 'H', 5, 0, 6, 10, 10));
	smokeCSlitherRoarC1->push_back(new Element(mList));

	hoard1 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster ("Tremendous Flying Dragon", 'M', 3, 0, 4, 12, 12));
	hoard1->push_back(new Element(mList));

	lair1 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster ("Tremendous Dragon", 'H', 5, 0, 6, 10, 10));
	lair1->push_back(new Element(mList));

	dankW2 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Viper", 'M', 4, 2, 4, 1, 2));
	mList->push_back(new Monster("Viper", 'M', 4, 2, 4, 1, 2));
	dankW2->push_back(new Element(mList));

	dankCSlither2 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Heavy Serpent", 'M', 4, 0, 3, 4, 4));
	mList->push_back(new Monster("Heavy Serpent", 'M', 4, 0, 3, 4, 4));
	dankCSlither2->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Tremendous Serpent", 'L', 4, 0, 4, 7, 7));
	dankCSlither2->push_back(new Element(mList));

	altar2 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Demon", 'V', 2, 0, 4, 8, 8));
	altar2->push_back(new Element(mList));

	shrine2 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Winged Demon", 'V', 3, 0, 3, 8, 8));
	shrine2->push_back(new Element(mList));

	ruinsW3 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Wolf", 'L', 4, 0, 3, 0, 1));
	mList->push_back(new Monster("Wolf", 'L', 4, 0, 3, 0, 1));
	mList->push_back(new Monster("Wolf", 'L', 4, 0, 3, 0, 1));
	mList->push_back(new Monster("Wolf", 'M', 5, 0, 3, 0, 1));
	mList->push_back(new Monster("Wolf", 'M', 5, 0, 3, 0, 1));
	mList->push_back(new Monster("Wolf", 'M', 5, 0, 3, 0, 1));
	ruinsW3->push_back(new Element(mList));

	bonesW3 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Ogre", 'T', 5, 0, 5, 0, 2));
	mList->push_back(new Monster("Ogre", 'T', 5, 0, 5, 0, 2));
	bonesW3->push_back(new Element(mList));

	ruinsCPatterCHowlC3 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Axe", 'L', 4, 1, 3, 1, 1));
	ruinsCPatterCHowlC3->push_back(new Element(mList));
	mList = new vector<Monster*>;
	//NOTE: A is to replace something that doesnt have harm letter
	mList->push_back(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	mList->push_back(new Monster("Golbin with Spear", 'A', 0, 0, 3, 1, 1));
	ruinsCPatterCHowlC3->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	mList->push_back(new Monster("Golbin with GreatSword", 'H', 6, 1, 3, 1, 1));
	ruinsCPatterCHowlC3->push_back(new Element(mList));


	pool3 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Octopus", 'L', 4, 0, 2, 8, 8));
	pool3->push_back(new Element(mList));

	bonesMRoarMStinkM4 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Giant", 'H', 5, 0, 5, 8, 8));
	bonesMRoarMStinkM4 ->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Giant", 'H', 5, 0, 5, 8, 8));
	bonesMRoarMStinkM4->push_back(new Element(mList));

	stinkCBonesCRoarC4 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Heavy Troll", 'M', 4, 0, 4, 5, 5));
	mList->push_back(new Monster("Heavy Troll", 'M', 4, 0, 4, 5, 5));
	stinkCBonesCRoarC4->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Tremendous Troll", 'H', 4, 0, 4, 8, 8));
	stinkCBonesCRoarC4->push_back(new Element(mList));

	vault4 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Tremendous Troll", 'H', 4, 0, 4, 8, 8));
	vault4->push_back(new Element(mList));

	stinkMDankMPatterM5 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3));
	stinkMDankMPatterM5->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3));
	stinkMDankMPatterM5->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Heavy Spider", 'L', 4, 0, 3, 3, 3));
	stinkMDankMPatterM5->push_back(new Element(mList));

	cairns5 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Tremendous Spider", 'M', 4, 0, 3, 6, 6));
	cairns5->push_back(new Element(mList));

	statue5 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Imp", 'A', 2, 0, 2, 2, 1));
	statue5->push_back(new Element(mList));

	ruinsMBonesMFlutterHowlM6 = new vector<Element*>;
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Giant Bat", 'M', 4, 0, 3, 3, 3));
	ruinsMBonesMFlutterHowlM6->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	mList->push_back(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	ruinsMBonesMFlutterHowlM6->push_back(new Element(mList));
	mList = new vector<Monster*>;
	mList->push_back(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	mList->push_back(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	mList->push_back(new Monster("Giant Bat", 'A', 4, 0, 3, 3, 3));
	ruinsMBonesMFlutterHowlM6->push_back(new Element(mList));
}

vector<Monster*>* MonsterSpawner::getMonsterList()
{
	cout << "Not Implemented" <<endl;
	return NULL;
}

vector<Monster*>* MonsterSpawner::spawn(Clearing* targetClearing, int dRoll)
{
	cout << "Not Implemented" <<endl;
	return NULL;
}