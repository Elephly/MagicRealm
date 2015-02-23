#include "game.h"

Game::Game()
{
    //initalizing players list
    for(int i=0; i < MAXPLAYERS; i ++)
        players[i] = NULL;
    
    day = 28;
    currentTime = BIRDSONG;
    gameBoard = new Board();
    cout << "Game Initialized" <<endl;
}

Game::~Game()
{
	for(int i=0; i < MAXPLAYERS; i++)
    {
        if(players[i]){
            delete players[i];
            players[i] = NULL;
        }
    }
    
	if (gameBoard != 0)
	{
		delete gameBoard;
		gameBoard = NULL;
	}
    cout << "Game Destroyed" << endl;
}

void Game::setupGame(bool cm)
{
    cheatMode = cm;
    cout << "Setting Up Game..." <<endl;
    setupTiles();
    plopDwellings();
    //placePlayers();

    //TODO PLOP CHARACTERS IN THEIR APPROPRIATE POSITIONS


    cout << "Finished Setup..." <<endl <<endl;
}

void Game::dealChits()
{
    vector<Chit *> mountainList;
    vector<Chit *> cavesList;
    vector<Chit *> woodsList;
    vector<Chit *> valleyList;

    valleyList.push_back(new Warning("BONES V", true));
    valleyList.push_back(new Warning("DANK V", true));
    valleyList.push_back(new Warning("RUINS V", true));
    valleyList.push_back(new Warning("SMOKE V", true));
    valleyList.push_back(new Warning("STINK V", true));

    woodsList.push_back(new Warning("BONES W", true));
    woodsList.push_back(new Warning("DANK W", true));
    woodsList.push_back(new Warning("RUINS W", true));
    woodsList.push_back(new Warning("SMOKE W", true));
    woodsList.push_back(new Warning("STINK W", true));

    cavesList.push_back(new Warning("BONES C", true));
    cavesList.push_back(new Warning("DANK C", true));
    cavesList.push_back(new Warning("RUINS C", true));
    cavesList.push_back(new Warning("SMOKE C", true));
    cavesList.push_back(new Warning("STINK C", true));

    mountainList.push_back(new Warning("BONES M", true));
    mountainList.push_back(new Warning("DANK M", true));
    mountainList.push_back(new Warning("RUINS M", true));
    mountainList.push_back(new Warning("SMOKE M", true));
    mountainList.push_back(new Warning("STINK M", true));

    vector <Treasure*> largeTreasure;
    vector <Treasure*> smallTreasure;

    largeTreasure.push_back(new Treasure("Battle Bracelets", 10, LARGE));
    largeTreasure.push_back(new Treasure("Beast Pipes", 15, GREAT));
    largeTreasure.push_back(new Treasure("Bejewled Vest", 15, GREAT));
    largeTreasure.push_back(new Treasure("Belt of Strength", 15, GREAT));
    largeTreasure.push_back(new Treasure("Book of Lore", 10, LARGE));
    largeTreasure.push_back(new Treasure("Blasted Jewel", 15, GREAT));
    largeTreasure.push_back(new Treasure("Cloak of Mist", 15, GREAT));
    largeTreasure.push_back(new Treasure("Cloven Hoof", 15, GREAT));
    largeTreasure.push_back(new Treasure("Cloven Hoof", 15, GREAT));
    largeTreasure.push_back(new Treasure("Deft Gloves", 15, GREAT));
    largeTreasure.push_back(new Treasure("Dragon Essence", 10, LARGE));
    largeTreasure.push_back(new Treasure("Dragonfang Necklace", 10, LARGE));
    largeTreasure.push_back(new Treasure("Draught of Speed", 10, LARGE));
    largeTreasure.push_back(new Treasure("Elusive Cloak", 10, LARGE));
    largeTreasure.push_back(new Treasure("Elven Slippers", 10, LARGE));
    largeTreasure.push_back(new Treasure("Enchanted Meadow", 10, LARGE));
    largeTreasure.push_back(new Treasure("Echanter's Skull", 10, LARGE));
    largeTreasure.push_back(new Treasure("Eye of Idol", 10, LARGE));
    largeTreasure.push_back(new Treasure("Eye of the Moon", 15, GREAT));
    largeTreasure.push_back(new Treasure("Flowers of Rest", 15, GREAT));
    largeTreasure.push_back(new Treasure("Garb of Speed", 15, GREAT));
    largeTreasure.push_back(new Treasure("Girtle of Energy", 15, GREAT));
    largeTreasure.push_back(new Treasure("Gloves of Strength", 10, LARGE));
    largeTreasure.push_back(new Treasure("Golden Arm Band", 15, GREAT));
    largeTreasure.push_back(new Treasure("Magic Wand", 15, GREAT));
    largeTreasure.push_back(new Treasure("Map of the Lost Castle", 15, GREAT));
    largeTreasure.push_back(new Treasure("Map of the Lost City", 15, GREAT));
    largeTreasure.push_back(new Treasure("Map of Ruins", 15, GREAT));
    largeTreasure.push_back(new Treasure("Oil of Poison", 10, LARGE));

    smallTreasure.push_back(new Treasure("7-League Boots", 5, SMALL));
    smallTreasure.push_back(new Treasure("Alchemist's Mixture", 5, SMALL));
    smallTreasure.push_back(new Treasure("Amulet", 5, SMALL));
    smallTreasure.push_back(new Treasure("Ancient Telescope", 5, SMALL));
    smallTreasure.push_back(new Treasure("Black Book", 5, SMALL));
    smallTreasure.push_back(new Treasure("Crystal Ball", 5, SMALL));
    smallTreasure.push_back(new Treasure("Flying Carpet", 5, SMALL));
    smallTreasure.push_back(new Treasure("Glimmering Ring", 5, SMALL));
    smallTreasure.push_back(new Treasure("Glowing Gem", 5, SMALL));
    smallTreasure.push_back(new Treasure("Golden Crown", 5, SMALL));
    smallTreasure.push_back(new Treasure("Golden Icon", 5, SMALL));
    smallTreasure.push_back(new Treasure("Good Book", 5, SMALL));
    smallTreasure.push_back(new Treasure("Gripping Dust", 5, SMALL));
    smallTreasure.push_back(new Treasure("Handy Gloves", 5, SMALL));
    smallTreasure.push_back(new Treasure("Hidden Ring", 5, SMALL));
    smallTreasure.push_back(new Treasure("Imperial Tabard", 5, SMALL));
    smallTreasure.push_back(new Treasure("Lost Keys", 5, SMALL));
    smallTreasure.push_back(new Treasure("Lucky Charm", 5, SMALL));
    smallTreasure.push_back(new Treasure("Magic Spectacles", 5, SMALL));
    smallTreasure.push_back(new Treasure("Ointment of Bite", 5, SMALL));
    smallTreasure.push_back(new Treasure("Oitment of Steel", 5, SMALL));
    smallTreasure.push_back(new Treasure("Penetrating Grease", 5, SMALL));
    smallTreasure.push_back(new Treasure("Phantom Glass", 5, SMALL));
    smallTreasure.push_back(new Treasure("Potion of Energy", 5, SMALL));
    smallTreasure.push_back(new Treasure("Poultrice of Health", 5, SMALL));
    smallTreasure.push_back(new Treasure("Power Boots", 5, SMALL));
    smallTreasure.push_back(new Treasure("Power Gauntlets", 5, SMALL));
    smallTreasure.push_back(new Treasure("Quick Boots", 5, SMALL));
    smallTreasure.push_back(new Treasure("Reflecting Grease", 5, SMALL));
    smallTreasure.push_back(new Treasure("Regent of Jewels", 5, SMALL));
    smallTreasure.push_back(new Treasure("Royal Sceptre", 5, SMALL));
    smallTreasure.push_back(new Treasure("Sacred Grail", 5, SMALL));
    smallTreasure.push_back(new Treasure("Sacred Statue", 5, SMALL));
    smallTreasure.push_back(new Treasure("Scroll of Alchemy", 5, SMALL));
    smallTreasure.push_back(new Treasure("Scroll of Nature", 5, SMALL));
    smallTreasure.push_back(new Treasure("Shielded Lantern", 5, SMALL));
    smallTreasure.push_back(new Treasure("Shoes of Stealth", 5, SMALL));
    smallTreasure.push_back(new Treasure("Timeless Jewel", 5, SMALL));
    smallTreasure.push_back(new Treasure("Toadstool Ring", 5, SMALL));
    smallTreasure.push_back(new Treasure("Vial of Healing", 5, SMALL));
    smallTreasure.push_back(new Treasure("Withered Claw", 5, SMALL));

    //Hoard Treasure setup
    vector <Site *> siteList;
    siteList.push_back(setupSite(HOARD, &largeTreasure, &smallTreasure));

    //Lair Treasure setup
    siteList.push_back(setupSite(LAIR, &largeTreasure, &smallTreasure));

    //Altar Treasure setup
    siteList.push_back(setupSite(ALTAR, &largeTreasure, &smallTreasure));

    //Shrine Treasure setup
    siteList.push_back(setupSite(SHRINE, &largeTreasure, &smallTreasure));

    //Pool Treasure setup
    siteList.push_back(setupSite(POOL, &largeTreasure, &smallTreasure));

    //Vault treasure setup
    siteList.push_back(setupSite(VAULT, &largeTreasure, &smallTreasure));

    //Cairns treasure setup
    siteList.push_back(setupSite(CAIRNS, &largeTreasure, &smallTreasure));
    
    //Statue treasure setup
    siteList.push_back(setupSite(STATUE, &largeTreasure, &smallTreasure));
}

Site* Game::setupSite(siteType sType, vector<Treasure*>* lg,  vector<Treasure*>* sm)
{
    string name = "";
    int numLarge = 0;
    int numSmall = 0;
    int random = -1;

    switch(sType){
    case HOARD:
        name = "Hoard";
        numLarge = 5;
        numSmall = 4;
        break;
    case LAIR:
        name = "Lair";
        numLarge = 3;
        numSmall = 4;
        break;
    case ALTAR:
        name = "Altar";
        numLarge = 4;
        break;
    case SHRINE:
        name = "Shrine";
        numLarge = 2;
        numSmall = 2;
        break;
    case POOL:
        name = "Pool";
        numLarge = 3;
        numSmall = 6;
    case VAULT:
        name = "Vault";
        numLarge = 5;
        break;
    case CAIRNS:
        name = "Cairns";
        numLarge = 1;
        numSmall = 6;
        break;
    case STATUE:
        name = "Statue";
        numLarge = 1;
        numSmall = 2;
    default:
        cout << "Err: Game::setupSite site unrecognized" <<endl;
        return NULL;
    }
    return NULL;

    vector <Treasure *> * stash = new vector<Treasure *>;
    for(int i=0; i < numLarge; i++){
        //get random large treasure
        random = rand() % (lg->size()-1);
        
        //take the treasure add it to the site's stash.
        stash->push_back(lg->at(random));
        //remove it from the list of available treasures
        lg->erase(lg->begin() + random);
    }
    for(int i=0; i < numSmall; i++){
        //get random large treasure
        random = rand() % (sm->size()-1);
        
        //take the treasure add it to the site's stash.
        stash->push_back(sm->at(random));
        //remove it from the list of available treasures
        sm->erase(sm->begin() + random);
    }

    return new Site(name, true, stash);
}

void Game::setupTiles()
{
    cout << "Arranging Tiles..." <<endl;
    Clearing* c1 = NULL;
    Clearing* c2 = NULL;
    Clearing* c3 = NULL;
    Clearing* c4 = NULL;
    Clearing* c5 = NULL;
    Clearing* c6 = NULL;
    Path* p = NULL;
    string *resultString = NULL;

    //creating borderland tile and clearings and INTERNAL paths
	Tile* borderLandTile = new Tile (EDGE_F, "Border Land");
	c1 = new Clearing(1, borderLandTile, WOODS);
	c2 = new Clearing(2, borderLandTile, WOODS);
	c3 = new Clearing(3, borderLandTile, WOODS);
	c4 = new Clearing(4, borderLandTile, CAVES);
	c5 = new Clearing(5, borderLandTile, CAVES);
	c6 = new Clearing(6, borderLandTile, CAVES);
	p = new Path(c1, c6, false);
	p = new Path(c2, c3, false);
	p = new Path(c3, c5, false);
	p = new Path(c3, c6, false);
	p = new Path(c4, c5, true);
	p = new Path(c4, c6, false);
	gameBoard->addTile(borderLandTile);
	
    if(gameBoard->getTile("Border Land") != NULL)
        cout << "Tile Found!!!" << endl;

    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //setting up the Oak Woods Tile and INTERNAL PATHS
    Tile* oakWoodsTile = new Tile(EDGE_E, "Oak Woods");
    c1 = new Clearing(2, oakWoodsTile, WOODS);
    c2 = new Clearing(4, oakWoodsTile, WOODS);
    c3 = new Clearing(5, oakWoodsTile, WOODS);
    p = new Path(c1, c2, false);
    gameBoard->addTile(oakWoodsTile);

    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //setting up the Bad Valley Tile. and INTERNAL PATHS
    Tile* badValleyTile = new Tile(EDGE_F, "Bad Valley");
    c1 = new Clearing(1, badValleyTile, WOODS);
    c2 = new Clearing(2, badValleyTile, WOODS);
    c3 = new Clearing(4, badValleyTile, WOODS);
    c4 = new Clearing(5, badValleyTile, WOODS);

    //regular paths
    p = new Path(c1, c3, false);
    p = new Path(c2, c4, false);

    gameBoard->addTile(badValleyTile);
    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //Setting up the Maple Woods Tile and INTERNAL PATHS
    Tile* mapleWoodsTile = new Tile(EDGE_C, "Maple Woods");

    c1 = new Clearing(2, mapleWoodsTile, WOODS);
    c2 = new Clearing(4, mapleWoodsTile, WOODS);
    c3 = new Clearing(5, mapleWoodsTile, WOODS);

    p = new Path(c1, c2, false);

    gameBoard->addTile(mapleWoodsTile);

    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    Tile* cavernTile = new Tile(EDGE_B, "Cavern");

    c1 = new Clearing(1, cavernTile, CAVES);
    c2 = new Clearing(2, cavernTile, CAVES);
    c3 = new Clearing(3, cavernTile, CAVES);
    c4 = new Clearing(4, cavernTile, CAVES);
    c5 = new Clearing(5, cavernTile, CAVES);
    c6 = new Clearing(6, cavernTile, CAVES);

    p = new Path(c1, c3, false);
    p = new Path(c1, c4, true);
    p = new Path(c2, c3, false);
    p = new Path(c3, c5, true);
    p = new Path(c3, c6, false);
    p = new Path(c4, c5, false);
    p = new Path(c4, c6, false);

    gameBoard->addTile(cavernTile);
    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //HighPass
    Tile* highPassTile = new Tile(EDGE_C, "High Pass");
    c1 = new Clearing(1, highPassTile, MOUNTAIN);
    c2 = new Clearing(2, highPassTile, MOUNTAIN);
    c3 = new Clearing(3, highPassTile, CAVES);
    c4 = new Clearing(4, highPassTile, MOUNTAIN);
    c5 = new Clearing(5, highPassTile, MOUNTAIN);
    c6 = new Clearing(6, highPassTile, CAVES);

    p = new Path(c1, c5, false);
    p = new Path(c1, c4, false);
    p = new Path(c2, c4, false);
    p = new Path(c3, c6, false);

    gameBoard->addTile(highPassTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Evil Valley
    Tile* evilValleyTile = new Tile(EDGE_C, "Evil Valley");
    c1 = new Clearing(1, evilValleyTile, WOODS);
    c2 = new Clearing(2, evilValleyTile, WOODS);
    c4 = new Clearing(4, evilValleyTile, WOODS);
    c5 = new Clearing(5, evilValleyTile, WOODS);

    p = new Path(c1, c4, false);
    p = new Path(c2, c5, false);

    gameBoard->addTile(evilValleyTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Ledges

    Tile* ledgesTile = new Tile(EDGE_E, "Ledges");
    c1 = new Clearing(1, ledgesTile, WOODS);
    c2 = new Clearing(2, ledgesTile, MOUNTAIN);
    c3 = new Clearing(3, ledgesTile, WOODS);
    c4 = new Clearing(4, ledgesTile, WOODS);
    c5 = new Clearing(5, ledgesTile, MOUNTAIN);
    c6 = new Clearing(6, ledgesTile, WOODS);

    p = new Path(c1, c3, true);
    p = new Path(c1, c4, false);
    p = new Path(c1, c6, false);
    p = new Path(c2, c5, false);
    p = new Path(c3, c6, false);
    p = new Path(c4, c6, true);

    gameBoard->addTile(ledgesTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Cliff
    Tile* cliffTile = new Tile(EDGE_F, "Cliff");
    c1 = new Clearing(1, cliffTile, MOUNTAIN);
    c2 = new Clearing(2, cliffTile, WOODS);
    c3 = new Clearing(3, cliffTile, WOODS);
    c4 = new Clearing(4, cliffTile, MOUNTAIN);
    c5 = new Clearing(5, cliffTile, WOODS);
    c6 = new Clearing(6, cliffTile, MOUNTAIN);

    p = new Path(c1, c6, false);
    p = new Path(c2, c3, false);
    p = new Path(c2, c5, true);
    p = new Path(c3, c5, false);
    p = new Path(c3, c6, true);
    p = new Path(c4, c6, false);

    gameBoard->addTile(cliffTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //crag
    Tile* cragTile = new Tile(EDGE_D, "Crag");
    c1 = new Clearing(1, cragTile, MOUNTAIN);
    c2 = new Clearing(2, cragTile, MOUNTAIN);
    c3 = new Clearing(3, cragTile, MOUNTAIN);
    c4 = new Clearing(4, cragTile, MOUNTAIN);
    c5 = new Clearing(5, cragTile, MOUNTAIN);
    c6 = new Clearing(6, cragTile, MOUNTAIN);

    p = new Path(c1, c4, false);
    p = new Path(c1, c6, true);
    p = new Path(c2, c5, false);
    p = new Path(c2, c3, true);
    p = new Path(c3, c5, false);
    p = new Path(c3, c6, false);
    p = new Path(c4, c6, false);
    
    gameBoard->addTile(cragTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Dark Valey
    Tile* darkValleyTile = new Tile(EDGE_C, "Dark Valley");
    c1 = new Clearing(1, darkValleyTile, WOODS);
    c2 = new Clearing(2, darkValleyTile, WOODS);
    c4 = new Clearing(4, darkValleyTile, WOODS);
    c5 = new Clearing(5, darkValleyTile, WOODS);

    p = new Path(c1, c4, false);
    p = new Path(c2, c5, false);
    
    gameBoard->addTile(darkValleyTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Deep Woods
    Tile* deepWoodsTile = new Tile(EDGE_A, "Deep Woods");
    c1 = new Clearing(1, deepWoodsTile, WOODS);
    c2 = new Clearing(2, deepWoodsTile, WOODS);
    c3 = new Clearing(3, deepWoodsTile, WOODS);
    c4 = new Clearing(4, deepWoodsTile, WOODS);
    c5 = new Clearing(5, deepWoodsTile, WOODS);
    c6 = new Clearing(6, deepWoodsTile, WOODS);

    p = new Path(c1, c6, false);
    p = new Path(c1, c4, true);
    p = new Path(c2, c3, false);
    p = new Path(c3, c5, false);
    p = new Path(c3, c6, true);
    p = new Path(c4, c5, false);
    p = new Path(c4, c6, false);
    
    gameBoard->addTile(deepWoodsTile);
    
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Curst Valley
    Tile* curstValleyTile = new Tile(EDGE_A, "Curst Valley");
    c1 = new Clearing(1, curstValleyTile, WOODS);
    c2 = new Clearing(2, curstValleyTile, WOODS);
    c4 = new Clearing(4, curstValleyTile, WOODS);
    c5 = new Clearing(5, curstValleyTile, WOODS);

    p = new Path(c1, c4, false);
    p = new Path(c2, c5, false);
    
    gameBoard->addTile(curstValleyTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Nut Woods
    Tile* nutWoodsTile = new Tile(EDGE_D, "Nut Woods");
    c2 = new Clearing(2, nutWoodsTile, WOODS);
    c4 = new Clearing(4, nutWoodsTile, WOODS);
    c5 = new Clearing(5, nutWoodsTile, WOODS);

    p = new Path(c2, c4, false);
    
    gameBoard->addTile(nutWoodsTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Awful Valley
    Tile* awfulValleyTile = new Tile(EDGE_A, "Awful Valley");
    c1 = new Clearing(1, awfulValleyTile, WOODS);
    c2 = new Clearing(2, awfulValleyTile, WOODS);
    c4 = new Clearing(4, awfulValleyTile, WOODS);
    c5 = new Clearing(5, awfulValleyTile, WOODS);

    p = new Path(c1, c4, false);
    p = new Path(c2, c5, false);
    
    gameBoard->addTile(awfulValleyTile);


    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Linden Woods
    Tile* lindenWoodsTile = new Tile(EDGE_B, "Linden Woods");
    c2 = new Clearing(2, lindenWoodsTile, WOODS);
    c4 = new Clearing(4, lindenWoodsTile, WOODS);
    c5 = new Clearing(5, lindenWoodsTile, WOODS);

    p = new Path(c2, c4, false);
    
    gameBoard->addTile(lindenWoodsTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Ruins
    Tile* ruinsTile = new Tile(EDGE_C, "Ruins");
    c1 = new Clearing(1, ruinsTile, WOODS);
    c2 = new Clearing(2, ruinsTile, WOODS);
    c3 = new Clearing(3, ruinsTile, WOODS);
    c4 = new Clearing(4, ruinsTile, WOODS);
    c5 = new Clearing(5, ruinsTile, WOODS);
    c6 = new Clearing(6, ruinsTile, CAVES);

    p = new Path(c1, c2, false);
    p = new Path(c1, c5, true);
    p = new Path(c1, c4, false);
    p = new Path(c3, c5, false);
    p = new Path(c3, c6, false);
    p = new Path(c4, c6, false);
    
    gameBoard->addTile(ruinsTile);
    
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Caves
    Tile* cavesTile = new Tile(EDGE_C, "Caves");
    c1 = new Clearing(1, cavesTile, CAVES);
    c2 = new Clearing(2, cavesTile, CAVES);
    c3 = new Clearing(3, cavesTile, CAVES);
    c4 = new Clearing(4, cavesTile, CAVES);
    c5 = new Clearing(5, cavesTile, CAVES);
    c6 = new Clearing(6, cavesTile, CAVES);

    p = new Path(c1, c6, false);
    p = new Path(c2, c3, true);
    p = new Path(c2, c4, false);
    p = new Path(c3, c5, false);
    p = new Path(c4, c6, false);
    
    gameBoard->addTile(cavesTile);
    
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //Linden Woods
    Tile* pineWoodsTile = new Tile(EDGE_A, "Pine Woods");
    c2 = new Clearing(2, pineWoodsTile, WOODS);
    c4 = new Clearing(4, pineWoodsTile, WOODS);
    c5 = new Clearing(5, pineWoodsTile, WOODS);

    p = new Path(c2, c4, false);
    
    gameBoard->addTile(pineWoodsTile);

    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c4 = NULL;
    c5 = NULL;

    //Mountain
    Tile* mountainTile = new Tile(EDGE_F, "Mountain");
    c1 = new Clearing(1, mountainTile, MOUNTAIN);
    c2 = new Clearing(2, mountainTile, WOODS);
    c3 = new Clearing(3, mountainTile, MOUNTAIN);
    c4 = new Clearing(4, mountainTile, WOODS);
    c5 = new Clearing(5, mountainTile, MOUNTAIN);
    c6 = new Clearing(6, mountainTile, MOUNTAIN);

    p = new Path(c1, c3, false);
    p = new Path(c2, c5, false);
    p = new Path(c2, c4, false);
    p = new Path(c3, c6, false);
    p = new Path(c4, c6, true);
    p = new Path(c5, c6, false);

    gameBoard->addTile(mountainTile);
        
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;

    //setting up connected stuff and connected paths.	
    borderLandTile->addConnectedTile(oakWoodsTile, EDGE_A);
    p = new Path(borderLandTile->getClearing(2), oakWoodsTile->getClearing(2), false);
    borderLandTile->addConnectedTile(badValleyTile, EDGE_B);
    p = new Path(borderLandTile->getClearing(1), badValleyTile->getClearing(5), false);
    borderLandTile->addConnectedTile(cavernTile, EDGE_C);
    p = new Path(borderLandTile->getClearing(5), cavernTile->getClearing(2), false);
    borderLandTile->addConnectedTile(highPassTile, EDGE_D);
    p = new Path(borderLandTile->getClearing(1), highPassTile->getClearing(2), false);
    borderLandTile->addConnectedTile(evilValleyTile, EDGE_E);
    p = new Path(borderLandTile->getClearing(2), evilValleyTile->getClearing(4), false);
    borderLandTile->addConnectedTile(ledgesTile, EDGE_F);
    p = new Path(borderLandTile->getClearing(4), ledgesTile->getClearing(4), false);

    highPassTile->addConnectedTile(evilValleyTile, EDGE_C);
    p = new Path(highPassTile->getClearing(6), evilValleyTile->getClearing(5), false);
    highPassTile->addConnectedTile(cavernTile, EDGE_E);
    p = new Path(highPassTile->getClearing(3), cavernTile->getClearing(5), false);

    oakWoodsTile->addConnectedTile(badValleyTile, EDGE_D);
    p = new Path(oakWoodsTile->getClearing(5), badValleyTile->getClearing(1), false);
    oakWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_C);
    p = new Path(oakWoodsTile->getClearing(5), mapleWoodsTile->getClearing(5), false);
    oakWoodsTile->addConnectedTile(deepWoodsTile, EDGE_B);
    p = new Path(oakWoodsTile->getClearing(4), deepWoodsTile->getClearing(1), false);
    oakWoodsTile->addConnectedTile(ledgesTile, EDGE_F);
    p = new Path(oakWoodsTile->getClearing(2), ledgesTile->getClearing(5), false);

    evilValleyTile->addConnectedTile(cliffTile, EDGE_C);
    p = new Path(evilValleyTile->getClearing(2), cliffTile->getClearing(1), false);
    evilValleyTile->addConnectedTile(ledgesTile, EDGE_D);
    p = new Path(evilValleyTile->getClearing(4), ledgesTile->getClearing(2), false);
    
    ledgesTile->addConnectedTile(cliffTile, EDGE_F);
    p = new Path(ledgesTile->getClearing(3), cliffTile->getClearing(2), false);

    deepWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_B);
    p = new Path(deepWoodsTile->getClearing(5), mapleWoodsTile->getClearing(5), false);
    deepWoodsTile->addConnectedTile(cragTile, EDGE_D);
    p = new Path(deepWoodsTile->getClearing(1), cragTile->getClearing(2), false);
    deepWoodsTile->addConnectedTile(darkValleyTile, EDGE_E);
    p = new Path(deepWoodsTile->getClearing(2), darkValleyTile->getClearing(5), false);
    deepWoodsTile->addConnectedTile(curstValleyTile, EDGE_F);
    p = new Path(deepWoodsTile->getClearing(2), curstValleyTile->getClearing(2), false);

    curstValleyTile->addConnectedTile(nutWoodsTile, EDGE_B);
    p = new Path(curstValleyTile->getClearing(4), nutWoodsTile->getClearing(5), false);
    curstValleyTile->addConnectedTile(darkValleyTile, EDGE_D);
    p = new Path(curstValleyTile->getClearing(1), darkValleyTile->getClearing(1), false);

    nutWoodsTile->addConnectedTile(awfulValleyTile, EDGE_D);
    p = new Path(nutWoodsTile->getClearing(2), awfulValleyTile->getClearing(5), false);
    nutWoodsTile->addConnectedTile(ruinsTile, EDGE_E);
    p = new Path(nutWoodsTile->getClearing(4), ruinsTile->getClearing(1), false);
    nutWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_F);
    p = new Path(nutWoodsTile->getClearing(5), mapleWoodsTile->getClearing(2), false);

    mapleWoodsTile->addConnectedTile(ruinsTile, EDGE_E);
    p = new Path(mapleWoodsTile->getClearing(2), ruinsTile->getClearing(5), false);
    mapleWoodsTile->addConnectedTile(cavesTile, EDGE_F);
    p = new Path(mapleWoodsTile->getClearing(4), cavesTile->getClearing(5), false);

    badValleyTile->addConnectedTile(cavesTile, EDGE_B);
    p = new Path(badValleyTile->getClearing(2), cavesTile->getClearing(2), false);
    badValleyTile->addConnectedTile(mountainTile, EDGE_C);
    p = new Path(badValleyTile->getClearing(4), mountainTile->getClearing(5), false);

    mountainTile->addConnectedTile(pineWoodsTile, EDGE_B);
    p = new Path(mountainTile->getClearing(2), pineWoodsTile->getClearing(4), false);

    cavesTile->addConnectedTile(pineWoodsTile, EDGE_F);
    p = new Path(cavesTile->getClearing(1), pineWoodsTile->getClearing(5), false);

    ruinsTile->addConnectedTile(awfulValleyTile, EDGE_D);
    p = new Path(ruinsTile->getClearing(2), awfulValleyTile->getClearing(1), false);
    ruinsTile->addConnectedTile(lindenWoodsTile, EDGE_E);
    p = new Path(ruinsTile->getClearing(2), lindenWoodsTile->getClearing(4), false);

    awfulValleyTile->addConnectedTile(lindenWoodsTile, EDGE_B);
    p = new Path(awfulValleyTile->getClearing(2), lindenWoodsTile->getClearing(5), false);
}

void Game::plopDwellings()
{
    cout << "Placing Dwellings.." <<endl;
    Dwelling* chapel = gameBoard->getTile("Awful Valley")->getClearing(5)->buildDwelling(CHAPEL);
    gameBoard->addDwelling(chapel);
	Dwelling* guard = gameBoard->getTile("Dark Valley")->getClearing(5)->buildDwelling(GUARD);
    gameBoard->addDwelling(guard);
	Dwelling* house = gameBoard->getTile("Curst Valley")->getClearing(5)->buildDwelling(HOUSE);
    gameBoard->addDwelling(house);
	Dwelling* inn = gameBoard->getTile("Bad Valley")->getClearing(5)->buildDwelling(INN);
    gameBoard->addDwelling(inn);
}

void Game::placePlayers()
{
    cout << "Placing Players..." <<endl;
    for(int i=0; i<MAXPLAYERS; i++){
        //no more players to loop through.
        if(!players[i]){
            break;
        }

        //place player in starting location depending on type
        switch(players[i]->getType()){
        case Amazon:
	    case BlackKnight:
      	case Captain:
	    case Dwarf:
	    case Elf:
	    case Swordsman:
            moveRequest(players[i], gameBoard->getTile("Border Land")->getClearing(1));
        }
    }
}
Board* Game::getBoard()
{
	return gameBoard;
}

void Game::runGame()
{
    cout << "Game Run..." << endl;
}

bool Game::addPlayer(CharacterType newPlayerType)
{
    if(getPlayer(newPlayerType)){
        cout << "ERR: Game::addPlayer attempted to add a player already in the list." <<endl;
        return false;
    }
    //Character doesnt yet exist, Creating new Character
    Character* newPlayer = new Character(newPlayerType);
    return addPlayer(newPlayer);
    //Adding character to the array.
    
}

bool Game::addPlayer(Character* newPlayer)
{
    for(int i=0; i<MAXPLAYERS; i++){
        if(!players[i]){
            players[i] = newPlayer;
            return true;
        }
        if(players[i] == newPlayer){
            cout << "ERR: Game::addPlayer attempted to add a player already in the list." <<endl;
            return false;
        }
    }
    cout << "WARN: Game::addPlayer Did not add the player, player list full" <<endl;
    return false;
}

void Game::removePlayer(CharacterType oldPlayerType)
{
    Character* oldPlayer = getPlayer(oldPlayerType);
    if(!oldPlayer){
        cout << "ERR: Game::removePlayer Player was not found (from Get)" <<endl;
        return;
    }
    int playerIndex = -1;
    int lastIndex = MAXPLAYERS-1;
    for(int i=0; i<MAXPLAYERS; i++){
        if(!players[i]){
            lastIndex = i-1;
            break;
        }
        if(players[i] == oldPlayer){
            playerIndex = i;
        }
    }
    if(playerIndex == -1)
        cout << "ERR: Game::removePlayer Player was not found" <<endl;
    //removing at the end of the current players in the array.
    if(playerIndex == lastIndex){
        delete players[playerIndex];
        players[playerIndex] = NULL;
    }
    //player is found, and its not the last player in the array.
    else{
        delete players[playerIndex];
        //setting the last player to the old players location
        players[playerIndex] = players[lastIndex];
        //now that the last player is moved, we can reduce the size of the array by removing the old lastIndex position (since its a duplicate)
        players[lastIndex] = NULL;
    }
}

Character* Game::getPlayer(CharacterType charType)
{
    for(int i=0; i<MAXPLAYERS; i++){
        if(players[i] == NULL){
            cout << "ERR: Game::getPlayer player not found, returning null" <<endl;
            return NULL;
        }
        if(players[i]->getType() == charType)
            return players[i];
    }
    //only get here if the player list is full
    cout << "ERR: Game::getPlayer player not found(looped through full array), returning null" <<endl;
    return NULL;
}

bool Game::hideRequest(Character* player)
{
    int d1 = rollDice();
    int d2 = rollDice();
    int diceUsed = (d1>d2) ? d1 : d2;

    if(diceUsed = 6)
        return false;
    
    if(player->isHidden())
        return true;
    player->toggleHide();
    return true;
}
bool Game::moveRequest(Character* player, Clearing* requestedClearing)
{
    Clearing* playerLoc = NULL;
    vector<Path*>* pathsAvailable =  NULL;
    //checking to see our data is valid
    if(player == NULL){
        cout << "ERR Game::moveRequest: Player is NULL" << endl;
        return false;
    }
    //valid player can get Location
    playerLoc = player->getCurrentLocation();
    if(requestedClearing == NULL){
        cout << "ERR Game::moveRequest: Requested clearing NULL" <<endl;
        return false;
    }
    if (playerLoc == NULL){
        cout << "TRACK Game::moveRequest: Player Loc NULL" <<endl;
        requestedClearing->addCharacter(player);
        player->moveToClearing(requestedClearing);
        return true;
    }
    //data valid we can populate
    pathsAvailable = playerLoc->getPaths();
    if(pathsAvailable == NULL){
        cout << "ERR Game::moveRequest: pathsAvailable is Null" <<endl;
        return false;
    }

    //TODO Check if Player Can move!!!!
    
    //going through possible cases of different types of move
    if(playerLoc == requestedClearing){
        cout << "ERR: Player Requested the location they are already in" <<endl;
        return false;
    }
    else //standard path checking
    {
        for(vector<Path*>::iterator it = pathsAvailable->begin(); it != pathsAvailable->end(); ++it){
            if((*it)->getEnd(playerLoc) == requestedClearing){
                //Found a path, Check if.
                playerLoc->removeCharacter(player);
                requestedClearing->addCharacter(player);
                player->moveToClearing(requestedClearing);
                return true;
            }
        }
        cout << "Pathway from the players current clearing to requested could not be found" <<endl;
        return false;
    }
}

void Game::move(Character* player, Clearing* requestedClearing)
{
    Clearing* playerLoc;
     if(player == NULL){
        cout << "ERR Game::moveRequest: Player is NULL" << endl;
    }
    //valid player can get Location
    playerLoc = player->getCurrentLocation();
    if(requestedClearing == NULL){
        cout << "ERR Game::moveRequest: Requested clearing NULL" <<endl;
    }
    else if (playerLoc == NULL){
        cout << "TRACK Game::moveRequest: Player Loc NULL" <<endl;
        requestedClearing->addCharacter(player);
        player->moveToClearing(requestedClearing);
    }
    else{
        playerLoc->removeCharacter(player);
        requestedClearing->addCharacter(player);
        player->moveToClearing(requestedClearing);
    }
}

int Game::rollDice()
{
    return rand() % 6 + 1;
}
Dwelling* Game::getDwelling(DwellingType dwellingType)
{
	return gameBoard->getDwelling(dwellingType);
}

void Game::doTurn()
{
}