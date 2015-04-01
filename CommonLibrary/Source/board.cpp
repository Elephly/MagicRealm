#include "board.h"
#include <sstream>

Board::Board() {
	//whole lotta nothing
    tileList = new vector <Tile*>;
	siteList = new vector <Site*>;
	soundList  = new vector<Sound*>;
	warningList = new vector<Warning*>;
	smallTreasureList = new vector<Treasure*>;
	largeTreasureList = new vector<Treasure*>;
    dwellingList = new vector<Dwelling*>;
	monsterTable = new MonsterSpawner();
	createTiles();
	createChits();
	createTreasures();

}

void Board::addTile(Tile* newTile)
{
     for(vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it){
        if((*it)->getName() == newTile->getName()){
            cout << "WARN: Tile already in List not adding tile" <<endl;
            return;
        }
    }
    //tile not found so we can addTile.
    tileList->push_back(newTile);
}

Tile* Board::getTile(string tName)
{
    for(vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it){
        if((*it)->getName() == tName)
            return *it;
    }
    //Tile String not found.
    return NULL;
}

void Board::addDwelling(Dwelling* newDwelling)
{
     for(vector<Dwelling*>::iterator it = dwellingList->begin(); it != dwellingList->end(); ++it){
        if((*it)->getType() == newDwelling->getType()){
            cout << "WARN: Dwelling already in List not adding dwelling" <<endl;
            return;
        }
    }
    //tile not found so we can addTile.
    dwellingList->push_back(newDwelling);
}

Dwelling* Board::getDwelling(DwellingType dType)
{
    for(vector<Dwelling*>::iterator it = dwellingList->begin(); it != dwellingList->end(); ++it){
        if((*it)->getType() == dType)
            return *it;
    }
    //Tile String not found.
    return NULL;
}

vector <Tile *>* Board::getTileByType(TileType type)
{
	vector <Tile *> * typeList = new vector <Tile *>;
	for(vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it){
		if((*it)->getType() == type){
			typeList->push_back(*it);
		}
	}
	return typeList;
}

vector <Warning *>* Board::getWarningsByType(TileType type)
{
	vector <Warning *> * typeList = new vector <Warning *>;
	for(vector<Warning*>::iterator it = warningList->begin(); it != warningList->end(); ++it){
		if((*it)->getTileType() == type){
			typeList->push_back(*it);
		}
	}
	return typeList;
}

string* Board::serialize() {
	stringstream s;
	s << "Board";
	s << CLASSDELIM;

	for (vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it) {
		s << *((*it)->serialize());
		s << LISTDELIM;
	}

	return new string(s.str());
}

void Board::createTiles()
{
	cout << "Creating Tiles" <<endl;
	Clearing* c1 = NULL;
    Clearing* c2 = NULL;
    Clearing* c3 = NULL;
    Clearing* c4 = NULL;
    Clearing* c5 = NULL;
    Clearing* c6 = NULL;
    Path* p = NULL;
	Tile* newTile;

    //creating borderland tile and clearings and INTERNAL paths
	newTile = new Tile ("Border Land", TILE_CAVES);
	c1 = new Clearing(1, newTile, WOODS);
	c2 = new Clearing(2, newTile, WOODS);
	c3 = new Clearing(3, newTile, WOODS);
	c4 = new Clearing(4, newTile, CAVES);
	c5 = new Clearing(5, newTile, CAVES);
	c6 = new Clearing(6, newTile, CAVES);
	p = new Path(c1, c6);
	p = new Path(c2, c3);
	p = new Path(c3, c5);
	p = new Path(c3, c6);
	p = new Path(c4, c5, SECRET);
	p = new Path(c4, c6);
	addTile(newTile);

    //resetting the clearings and paths
	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //setting up the Oak Woods Tile and INTERNAL PATHS
    newTile = new Tile("Oak Woods", TILE_WOODS);
    c1 = new Clearing(2, newTile, WOODS);
    c2 = new Clearing(4, newTile, WOODS);
    c3 = new Clearing(5, newTile, WOODS);
    p = new Path(c1, c2);
    addTile(newTile);

    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //setting up the Bad Valley Tile. and INTERNAL PATHS
    newTile = new Tile("Bad Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(4, newTile, WOODS);
    c4 = new Clearing(5, newTile, WOODS);

    //regular paths
    p = new Path(c1, c3);
    p = new Path(c2, c4);

    addTile(newTile);
    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //Setting up the Maple Woods Tile and INTERNAL PATHS
    newTile = new Tile("Maple Woods", TILE_WOODS);

    c1 = new Clearing(2, newTile, WOODS);
    c2 = new Clearing(4, newTile, WOODS);
    c3 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c2);

    addTile(newTile);

    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    newTile = new Tile("Cavern", TILE_CAVES);

    c1 = new Clearing(1, newTile, CAVES);
    c2 = new Clearing(2, newTile, CAVES);
    c3 = new Clearing(3, newTile, CAVES);
    c4 = new Clearing(4, newTile, CAVES);
    c5 = new Clearing(5, newTile, CAVES);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c3);
    p = new Path(c1, c4, SECRET);
    p = new Path(c2, c3);
    p = new Path(c3, c5, SECRET);
    p = new Path(c3, c6);
    p = new Path(c4, c5);
    p = new Path(c4, c6);

    addTile(newTile);
    //resetting the clearings and paths

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //HighPass
    newTile = new Tile("High Pass", TILE_CAVES);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, MOUNTAIN);
    c3 = new Clearing(3, newTile, CAVES);
    c4 = new Clearing(4, newTile, MOUNTAIN);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c5);
    p = new Path(c1, c4);
    p = new Path(c2, c4);
    p = new Path(c3, c6);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Evil Valley
    newTile = new Tile("Evil Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Ledges

	newTile = new Tile("Ledges", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, MOUNTAIN);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, WOODS);

    p = new Path(c1, c3, HIDDEN);
    p = new Path(c1, c4);
    p = new Path(c1, c6);
    p = new Path(c2, c5);
    p = new Path(c3, c6);
    p = new Path(c4, c6, HIDDEN);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Cliff
    newTile = new Tile("Cliff", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, MOUNTAIN);
    c5 = new Clearing(5, newTile, WOODS);
    c6 = new Clearing(6, newTile, MOUNTAIN);

    p = new Path(c1, c6);
    p = new Path(c2, c3);
    p = new Path(c2, c5, HIDDEN);
    p = new Path(c3, c5);
    p = new Path(c3, c6, SECRET);
    p = new Path(c4, c6);

    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //crag
	newTile = new Tile("Crag", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, MOUNTAIN);
    c3 = new Clearing(3, newTile, MOUNTAIN);
    c4 = new Clearing(4, newTile, MOUNTAIN);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, MOUNTAIN);

    p = new Path(c1, c4);
    p = new Path(c1, c6, SECRET);
    p = new Path(c2, c5);
    p = new Path(c2, c3, HIDDEN);
    p = new Path(c3, c5);
    p = new Path(c3, c6);
    p = new Path(c4, c6);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Dark Valey
    newTile = new Tile("Dark Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Deep Woods
    newTile = new Tile("Deep Woods", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);
    c6 = new Clearing(6, newTile, WOODS);

    p = new Path(c1, c6);
	p = new Path(c1, c4, HIDDEN);
    p = new Path(c2, c3);
    p = new Path(c3, c5);
    p = new Path(c3, c6, HIDDEN);
    p = new Path(c4, c5);
    p = new Path(c4, c6);
    
    addTile(newTile);
    
	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Curst Valley
    newTile = new Tile("Curst Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Nut Woods
    newTile = new Tile("Nut Woods", TILE_WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c2, c4);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Awful Valley
    newTile = new Tile("Awful Valley", TILE_VALLEY);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c1, c4);
    p = new Path(c2, c5);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Linden Woods
    newTile = new Tile("Linden Woods", TILE_WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c2, c4);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Ruins
    newTile = new Tile("Ruins", TILE_CAVES);
    c1 = new Clearing(1, newTile, WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c2);
    p = new Path(c1, c5, HIDDEN);
    p = new Path(c1, c4);
    p = new Path(c3, c5);
    p = new Path(c3, c6);
    p = new Path(c4, c6);
    
    addTile(newTile);

    newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Caves
    newTile = new Tile("Caves", TILE_CAVES);
    c1 = new Clearing(1, newTile, CAVES);
    c2 = new Clearing(2, newTile, CAVES);
    c3 = new Clearing(3, newTile, CAVES);
    c4 = new Clearing(4, newTile, CAVES);
    c5 = new Clearing(5, newTile, CAVES);
    c6 = new Clearing(6, newTile, CAVES);

    p = new Path(c1, c6);
    p = new Path(c2, c3, SECRET);
    p = new Path(c2, c4);
    p = new Path(c3, c5);
    p = new Path(c4, c6);
    
    addTile(newTile);

    newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Linden Woods
    newTile = new Tile("Pine Woods", TILE_WOODS);
    c2 = new Clearing(2, newTile, WOODS);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, WOODS);

    p = new Path(c2, c4);
    
    addTile(newTile);

	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Mountain
    newTile = new Tile("Mountain", TILE_MOUNTAIN);
    c1 = new Clearing(1, newTile, MOUNTAIN);
    c2 = new Clearing(2, newTile, WOODS);
    c3 = new Clearing(3, newTile, MOUNTAIN);
    c4 = new Clearing(4, newTile, WOODS);
    c5 = new Clearing(5, newTile, MOUNTAIN);
    c6 = new Clearing(6, newTile, MOUNTAIN);

    p = new Path(c1, c3);
    p = new Path(c2, c5);
    p = new Path(c2, c4);
    p = new Path(c3, c6);
    p = new Path(c4, c6, HIDDEN);
    p = new Path(c5, c6);

    addTile(newTile);
    
	newTile = NULL;
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;
}

void Board::createChits()
{
	//setting up warnings
	//valley warnings
	warningList->push_back(new Warning("BONES V", false, TILE_VALLEY));
	warningList->push_back(new Warning("DANK V", false, TILE_VALLEY));
	warningList->push_back(new Warning("RUINS V", false, TILE_VALLEY));
	warningList->push_back(new Warning("SMOKE V", false, TILE_VALLEY));
	warningList->push_back(new Warning("STINK V", false, TILE_VALLEY));
	//woods warnings
	warningList->push_back(new Warning("BONES W", true, TILE_WOODS));
	warningList->push_back(new Warning("DANK W", true, TILE_WOODS));
	warningList->push_back(new Warning("RUINS W", true, TILE_WOODS));
	warningList->push_back(new Warning("SMOKE W", true, TILE_WOODS));
	warningList->push_back(new Warning("STINK W", true, TILE_WOODS));
	//caves warning
	warningList->push_back(new Warning("BONES C", true, TILE_CAVES));
	warningList->push_back(new Warning("DANK C", true, TILE_CAVES));
	warningList->push_back(new Warning("RUINS C", true, TILE_CAVES));
	warningList->push_back(new Warning("SMOKE C", true, TILE_CAVES));
	warningList->push_back(new Warning("STINK C", true, TILE_CAVES));
	//Mountain warning
	warningList->push_back(new Warning("BONES M", true, TILE_MOUNTAIN));
	warningList->push_back(new Warning("DANK M", true, TILE_MOUNTAIN));
	warningList->push_back(new Warning("RUINS M", true, TILE_MOUNTAIN));
	warningList->push_back(new Warning("SMOKE M", true, TILE_MOUNTAIN));
	warningList->push_back(new Warning("STINK M", true, TILE_MOUNTAIN));

	//setting up sounds
	soundList->push_back(new Sound("Howl 4", true, TILE_CANDM, 4));
	soundList->push_back(new Sound("Howl 5", true, TILE_CANDM, 5));
	soundList->push_back(new Sound("Flutter 1", true, TILE_CANDM, 1));
	soundList->push_back(new Sound("Flutter 2", true, TILE_CANDM, 2));
	soundList->push_back(new Sound("Patter 2", true, TILE_CANDM, 2));
	soundList->push_back(new Sound("Patter 5", true, TILE_CANDM, 5));
	soundList->push_back(new Sound("Roar 4", true, TILE_CANDM, 4));
	soundList->push_back(new Sound("Roar 6", true, TILE_CANDM, 2));
	soundList->push_back(new Sound("Slither 3", true, TILE_CANDM, 3));
	soundList->push_back(new Sound("Slither 6", true, TILE_CANDM, 6));
	cout << "Unimplemented" <<endl;

	siteList->push_back(new Site("Hoard", true, TILE_CANDM, 6));
	siteList->push_back(new Site("Lair", true, TILE_CANDM, 3));
	siteList->push_back(new Site("Altar", true, TILE_CANDM, 1));
	siteList->push_back(new Site("Shrine", true, TILE_CANDM, 4));
	siteList->push_back(new Site("Pool", true, TILE_CANDM, 6));
	siteList->push_back(new Site("Vault", true, TILE_CANDM, 3));
	siteList->push_back(new Site("Cairns", true, TILE_CANDM, 5));
	siteList->push_back(new Site("Statue", true, TILE_CANDM, 2));

	lostCity = new Lost("Lost City", true, TILE_CANDM);
	lostCastle = new Lost("Lost Castle", true, TILE_CANDM);
}

vector<Site*>* Board::getSiteChits()
{
	return siteList;
}
vector<Sound*>* Board::getSoundChits()
{
	return soundList;
}
vector<Treasure*> * Board::getLargeTreasureList()
{
	return largeTreasureList;
}

vector<Treasure*>* Board::getSmallTreasureList()
{
	return smallTreasureList;
}
void Board::createTreasures()
{
	largeTreasureList->push_back(new Treasure("Battle Bracelets", LARGE));
    largeTreasureList->push_back(new Treasure("Beast Pipes", GREAT));
    largeTreasureList->push_back(new Treasure("Bejewled Vest", GREAT));
    largeTreasureList->push_back(new Treasure("Belt of Strength", GREAT));
    largeTreasureList->push_back(new Treasure("Book of Lore", LARGE));
    largeTreasureList->push_back(new Treasure("Blasted Jewel", GREAT));
    largeTreasureList->push_back(new Treasure("Cloak of Mist", GREAT));
    largeTreasureList->push_back(new Treasure("Cloven Hoof", GREAT));
    largeTreasureList->push_back(new Treasure("Cloven Hoof", GREAT));
    largeTreasureList->push_back(new Treasure("Deft Gloves", GREAT));
    largeTreasureList->push_back(new Treasure("Dragon Essence", LARGE));
    largeTreasureList->push_back(new Treasure("Dragonfang Necklace", LARGE));
    largeTreasureList->push_back(new Treasure("Draught of Speed", LARGE));
    largeTreasureList->push_back(new Treasure("Elusive Cloak", LARGE));
    largeTreasureList->push_back(new Treasure("Elven Slippers", LARGE));
    largeTreasureList->push_back(new Treasure("Enchanted Meadow", LARGE));
    largeTreasureList->push_back(new Treasure("Echanter's Skull", LARGE));
    largeTreasureList->push_back(new Treasure("Eye of Idol", LARGE));
    largeTreasureList->push_back(new Treasure("Eye of the Moon", GREAT));
    largeTreasureList->push_back(new Treasure("Flowers of Rest", GREAT));
    largeTreasureList->push_back(new Treasure("Garb of Speed", GREAT));
    largeTreasureList->push_back(new Treasure("Girtle of Energy", GREAT));
    largeTreasureList->push_back(new Treasure("Gloves of Strength", LARGE));
    largeTreasureList->push_back(new Treasure("Golden Arm Band", GREAT));
    largeTreasureList->push_back(new Treasure("Magic Wand", GREAT));
    largeTreasureList->push_back(new Treasure("Map of the Lost Castle", GREAT));
    largeTreasureList->push_back(new Treasure("Map of the Lost City", GREAT));
    largeTreasureList->push_back(new Treasure("Map of Ruins", GREAT));
    largeTreasureList->push_back(new Treasure("Oil of Poison", LARGE));

    smallTreasureList->push_back(new Treasure("7-League Boots", SMALL));
    smallTreasureList->push_back(new Treasure("Alchemist's Mixture", SMALL));
    smallTreasureList->push_back(new Treasure("Amulet", SMALL));
    smallTreasureList->push_back(new Treasure("Ancient Telescope", SMALL));
    smallTreasureList->push_back(new Treasure("Black Book", SMALL));
    smallTreasureList->push_back(new Treasure("Crystal Ball", SMALL));
    smallTreasureList->push_back(new Treasure("Flying Carpet", SMALL));
    smallTreasureList->push_back(new Treasure("Glimmering Ring", SMALL));
    smallTreasureList->push_back(new Treasure("Glowing Gem", SMALL));
    smallTreasureList->push_back(new Treasure("Golden Crown", SMALL));
    smallTreasureList->push_back(new Treasure("Golden Icon", SMALL));
    smallTreasureList->push_back(new Treasure("Good Book", SMALL));
    smallTreasureList->push_back(new Treasure("Gripping Dust", SMALL));
    smallTreasureList->push_back(new Treasure("Handy Gloves", SMALL));
    smallTreasureList->push_back(new Treasure("Hidden Ring", SMALL));
    smallTreasureList->push_back(new Treasure("Imperial Tabard", SMALL));
    smallTreasureList->push_back(new Treasure("Lost Keys", SMALL));
    smallTreasureList->push_back(new Treasure("Lucky Charm", SMALL));
    smallTreasureList->push_back(new Treasure("Magic Spectacles", SMALL));
    smallTreasureList->push_back(new Treasure("Ointment of Bite", SMALL));
    smallTreasureList->push_back(new Treasure("Oitment of Steel", SMALL));
    smallTreasureList->push_back(new Treasure("Penetrating Grease", SMALL));
    smallTreasureList->push_back(new Treasure("Phantom Glass", SMALL));
    smallTreasureList->push_back(new Treasure("Potion of Energy", SMALL));
    smallTreasureList->push_back(new Treasure("Poultrice of Health", SMALL));
    smallTreasureList->push_back(new Treasure("Power Boots", SMALL));
    smallTreasureList->push_back(new Treasure("Power Gauntlets", SMALL));
    smallTreasureList->push_back(new Treasure("Quick Boots", SMALL));
    smallTreasureList->push_back(new Treasure("Reflecting Grease", SMALL));
    smallTreasureList->push_back(new Treasure("Regent of Jewels", SMALL));
    smallTreasureList->push_back(new Treasure("Royal Sceptre", SMALL));
    smallTreasureList->push_back(new Treasure("Sacred Grail", SMALL));
    smallTreasureList->push_back(new Treasure("Sacred Statue", SMALL));
    smallTreasureList->push_back(new Treasure("Scroll of Alchemy", SMALL));
    smallTreasureList->push_back(new Treasure("Scroll of Nature", SMALL));
    smallTreasureList->push_back(new Treasure("Shielded Lantern", SMALL));
    smallTreasureList->push_back(new Treasure("Shoes of Stealth", SMALL));
    smallTreasureList->push_back(new Treasure("Timeless Jewel", SMALL));
    smallTreasureList->push_back(new Treasure("Toadstool Ring", SMALL));
    smallTreasureList->push_back(new Treasure("Vial of Healing", SMALL));
    smallTreasureList->push_back(new Treasure("Withered Claw", SMALL));
}


Chit* Board::getChitByName(string name)
{
	if(name == lostCastle->getName())
		return lostCastle;
	if(name == lostCity->getName())
		return lostCity;

	for(vector<Site*>::iterator it= siteList->begin(); it != siteList->end(); ++it){
		if(name == (*it)->getName())
			return *it;
	}
	for(vector<Sound*>::iterator it= soundList->begin(); it != soundList->end(); ++it){
		if(name == (*it)->getName())
			return *it;
	}
	for(vector<Warning*>::iterator it= warningList->begin(); it != warningList->end(); ++it){
		if(name == (*it)->getName())
			return *it;
	}
	//have not found anything.
	return NULL;
}

vector<Tile*>* Board::getTiles() 
{
	return tileList;
}
