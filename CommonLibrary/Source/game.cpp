#include "game.h"

Game::Game()
{
    //initalizing players list
    for(int i=0; i < MAXPLAYERS; i ++)
        players[i] = NULL;
    
    day = 28;
    currentTime = BIRDSONG;
    gameBoard = new Board();
    activeMonsters = new vector<Monster*>;
    cout << "Game Initialized" <<endl;

	seed = time(NULL);
}

//used in client for seed passing in
Game::Game(time_t sd)
{
    //initalizing players list
    for(int i=0; i < MAXPLAYERS; i ++)
        players[i] = NULL;
    
    day = 28;
    currentTime = BIRDSONG;
    gameBoard = new Board();
    activeMonsters = new vector<Monster*>;
    cout << "Game Initialized" <<endl;

	seed = sd;
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

time_t Game::getTime()
{
	return seed;
}
void Game::setupGame(bool cm)
{
	//setting seed for randomness
	srand(seed);
    cheatMode = cm;
    cout << "Setting Up Game..." <<endl;
    
    //only 1 board tiles can be setup
    setupTiles();
    assignTreasures();
    //chits and dwellings change depending
    if(cheatMode)
        customSetup();
    else
	    dealChits();

    cout << "Finished Setup..." <<endl <<endl;
}

void Game::assignTreasures()
{
	vector<Site*>* siteList = gameBoard->getSiteChits();
	vector<Treasure*> largeTreasure;
	vector<Treasure*> smallTreasure;
	vector<Treasure*>* tempTreasureList = gameBoard->getLargeTreasureList();

	//setting up large treasure lists.
	for(vector<Treasure*>::iterator iter = tempTreasureList->begin(); iter!= tempTreasureList->end(); ++iter){
		largeTreasure.push_back(*iter);
	}
	//setting up small treasure lists
	tempTreasureList = gameBoard->getSmallTreasureList();
	for(vector<Treasure*>::iterator iter = tempTreasureList->begin(); iter!= tempTreasureList->end(); ++iter){
		smallTreasure.push_back(*iter);
	}
	//setting up site.
	for(vector<Site*>::iterator it = siteList->begin(); it != siteList->end(); ++it)
		setupSite(*it, &largeTreasure, &smallTreasure);
}
void Game::dealChits()
{
	vector <Chit *> siteAndSoundList;
	vector<Chit *> mountainList;
	vector<Chit *> cavesList;
	
	vector <Site*>* siteList = gameBoard->getSiteChits();
	vector <Sound*>* soundList = gameBoard->getSoundChits();
	vector<Warning *>* mountainWarningList = gameBoard->getWarningsByType(TILE_MOUNTAIN);
    vector<Warning *>* cavesWarningList = gameBoard->getWarningsByType(TILE_CAVES);
    vector<Warning *>* woodsList = gameBoard->getWarningsByType(TILE_WOODS);

	Lost* lostCity = (Lost*) gameBoard->getChitByName("Lost City");
	Lost* lostCastle = (Lost*) gameBoard->getChitByName("Lost Castle");
	
	vector<Chit *>* lostCityList = new vector<Chit*>;
	vector<Chit *>* lostCastleList = new vector<Chit*>;
	int random = 0;

	for(vector<Site*>::iterator it = siteList->begin(); it != siteList->end(); ++it)
		siteAndSoundList.push_back(*it);


	for(vector<Sound*>::iterator it = soundList->begin(); it != soundList->end(); ++it)
		siteAndSoundList.push_back(*it);
 
	//randomly putting into cavesList
	for(int i=0; i<4; i++){
		random = rand() % (siteAndSoundList.size());
		cavesList.push_back(siteAndSoundList.at(random));
		siteAndSoundList.erase(siteAndSoundList.begin() + random);
	}

	//randomly putting into mountain list
	for(int i=0; i<4; i++){
		random = rand() % (siteAndSoundList.size());
		mountainList.push_back(siteAndSoundList.at(random));
		siteAndSoundList.erase(siteAndSoundList.begin() + random);
	}

	//settig up LostCity
	for(int i=0; i<5; i++){
		random = rand() % (siteAndSoundList.size());
		lostCityList->push_back(siteAndSoundList.at(random));
		siteAndSoundList.erase(siteAndSoundList.begin() + random);
	}
	lostCity->populateCity(lostCityList);
	
	//Setting up LostCastle
	for(int i=0; i<5; i++){
		random = rand() % (siteAndSoundList.size());
		lostCastleList->push_back(siteAndSoundList.at(random));
		siteAndSoundList.erase(siteAndSoundList.begin() + random);
	}
	lostCastle->populateCity(lostCastleList);

	cavesList.push_back(lostCity);
	mountainList.push_back(lostCastle);


	vector <Tile *> * tileTypeList = gameBoard->getTileByType(TILE_MOUNTAIN);

	//populating mountain tiles
	for(vector<Tile*>::iterator it = tileTypeList->begin(); it != tileTypeList->end(); ++it){

		random = rand() % (mountainWarningList->size());

		(*it)->addWarningChit(mountainWarningList->at(random));
		mountainWarningList->erase(mountainWarningList->begin() + random);

		//adding Site or Sound
		
		random = rand() % (mountainList.size());
		(*it)->addSiteOrSoundChit(mountainList.at(random));
		mountainList.erase(mountainList.begin() +random);
	}
	delete mountainWarningList;
	delete tileTypeList;

	tileTypeList = gameBoard->getTileByType(TILE_CAVES);

	//populating caves tiles
	for(vector<Tile*>::iterator it = tileTypeList->begin(); it != tileTypeList->end(); ++it){
		//adding warningChit
		random = rand() % (cavesWarningList->size());
		(*it)->addWarningChit(cavesWarningList->at(random));
		cavesWarningList->erase(cavesWarningList->begin() + random);

		//adding Site or Sound
		random = rand() % (cavesList.size());
		(*it)->addSiteOrSoundChit(cavesList.at(random));
		cavesList.erase(cavesList.begin() +random);
	}
	delete cavesWarningList;
	delete tileTypeList;

	//populating woods tiles
	tileTypeList = gameBoard->getTileByType(TILE_WOODS);
	for(vector <Tile*>::iterator it = tileTypeList->begin(); it != tileTypeList->end(); ++it){
		random = rand() % (woodsList->size());
		(*it)->addWarningChit(woodsList->at(random));
		woodsList->erase(woodsList->begin() + random);
	}
	delete woodsList;

	//plopping valley tiles
	//TODO needs to change!!!!!!!!!! They should be randomly placed, this has to do with iteration 1 board.
	gameBoard->getTile("Evil Valley")->addWarningChit((Warning*) gameBoard->getChitByName("BONES V"));
	gameBoard->getTile("Awful Valley")->addWarningChit((Warning*) gameBoard->getChitByName("DANK V"));
	gameBoard->getTile("Dark Valley")->addWarningChit((Warning*) gameBoard->getChitByName("RUINS V"));
	gameBoard->getTile("Curst Valley")->addWarningChit((Warning*) gameBoard->getChitByName("SMOKE V"));
	gameBoard->getTile("Bad Valley")->addWarningChit((Warning*) gameBoard->getChitByName("STINK V"));	
}

void Game::setupSite(Site* mySite, vector<Treasure*>* lg,  vector<Treasure*>* sm)
{
    int numLarge = 0;
    int numSmall = 0;
    int random = -1;

	switch(mySite->getType()){
    case HOARD:
        numLarge = 5;
        numSmall = 4;
        break;
    case LAIR:
        numLarge = 3;
        numSmall = 4;
        break;
    case ALTAR:
        numLarge = 4;
        break;
    case SHRINE:
        numLarge = 2;
        numSmall = 2;
        break;
    case POOL:
        numLarge = 3;
        numSmall = 6;
		break;
    case VAULT:
        numLarge = 5;
        break;
    case CAIRNS:
        numLarge = 1;
        numSmall = 6;
        break;
    case STATUE:
        numLarge = 1;
        numSmall = 2;
		break;
    default:
        cout << "Err: Game::setupSite site unrecognized" <<endl;
        return;
    }

    vector <Treasure *> * stash = new vector<Treasure *>;
    for(int i=0; i < numLarge; i++){
        //get random large treasure
        random = rand() % (lg->size());
        
        //take the treasure add it to the site's stash.
        stash->push_back(lg->at(random));
        //remove it from the list of available treasures
        lg->erase(lg->begin() + random);
    }
    for(int i=0; i < numSmall; i++){
        //get random large treasure
        random = rand() % (sm->size());
        
        //take the treasure add it to the site's stash.
        stash->push_back(sm->at(random));
        //remove it from the list of available treasures
        sm->erase(sm->begin() + random);
    }

	mySite->storeTreasure(stash);
}

void Game::setupTiles()
{
	//path to be used to ccreate the connecting paths
	Path* p = NULL;
    cout << "Arranging Tiles..." <<endl;
	//getting the tiles
	Tile* borderLandTile = gameBoard->getTile("Border Land");
	Tile* oakWoodsTile = gameBoard->getTile("Oak Woods");
	Tile* badValleyTile = gameBoard->getTile("Bad Valley");
	Tile* mapleWoodsTile = gameBoard->getTile("Maple Woods");
	Tile* cavernTile = gameBoard->getTile("Cavern");
	Tile* highPassTile = gameBoard->getTile("High Pass");
	Tile* evilValleyTile = gameBoard->getTile("Evil Valley");
	Tile* ledgesTile = gameBoard->getTile("Ledges");
	Tile* cliffTile = gameBoard->getTile("Cliff");
    Tile* cragTile = gameBoard->getTile("Crag");
	Tile* darkValleyTile = gameBoard->getTile("Dark Valley");
	Tile* deepWoodsTile = gameBoard->getTile("Deep Woods");
	Tile* curstValleyTile = gameBoard->getTile("Curst Valley");
	Tile* nutWoodsTile = gameBoard->getTile("Nut Woods");
	Tile* awfulValleyTile = gameBoard->getTile("Awful Valley");
	Tile* lindenWoodsTile = gameBoard->getTile("Linden Woods");
	Tile* ruinsTile = gameBoard->getTile("Ruins");
	Tile* cavesTile = gameBoard->getTile("Caves");
	Tile* pineWoodsTile = gameBoard->getTile("Pine Woods");
	Tile* mountainTile = gameBoard->getTile("Mountain");

	//setting the orientation of the tiles on the board
	borderLandTile->setOrientation(EDGE_F);
	oakWoodsTile->setOrientation(EDGE_E);
	badValleyTile->setOrientation(EDGE_F);
	mapleWoodsTile->setOrientation(EDGE_C);
	cavernTile->setOrientation(EDGE_B);
	highPassTile->setOrientation(EDGE_C);
	evilValleyTile->setOrientation(EDGE_C);
	ledgesTile->setOrientation(EDGE_E);
	cliffTile->setOrientation(EDGE_F);
	cragTile->setOrientation(EDGE_D);
	darkValleyTile->setOrientation(EDGE_C);
	deepWoodsTile->setOrientation(EDGE_A);
	curstValleyTile->setOrientation(EDGE_A);
	nutWoodsTile->setOrientation(EDGE_D);
	awfulValleyTile->setOrientation(EDGE_A);
	lindenWoodsTile->setOrientation(EDGE_B);
	ruinsTile->setOrientation(EDGE_C);
	cavesTile->setOrientation(EDGE_C);
	pineWoodsTile->setOrientation(EDGE_A);
	mountainTile->setOrientation(EDGE_F);
    
    //setting up connected stuff and connected paths.	
    borderLandTile->addConnectedTile(oakWoodsTile, EDGE_A);
    p = new Path(borderLandTile->getClearing(2), oakWoodsTile->getClearing(2));
    borderLandTile->addConnectedTile(badValleyTile, EDGE_B);
    p = new Path(borderLandTile->getClearing(1), badValleyTile->getClearing(5));
    borderLandTile->addConnectedTile(cavernTile, EDGE_C);
    p = new Path(borderLandTile->getClearing(5), cavernTile->getClearing(2));
    borderLandTile->addConnectedTile(highPassTile, EDGE_D);
    p = new Path(borderLandTile->getClearing(1), highPassTile->getClearing(2));
    borderLandTile->addConnectedTile(evilValleyTile, EDGE_E);
    p = new Path(borderLandTile->getClearing(2), evilValleyTile->getClearing(4));
    borderLandTile->addConnectedTile(ledgesTile, EDGE_F);
    p = new Path(borderLandTile->getClearing(4), ledgesTile->getClearing(4));

    highPassTile->addConnectedTile(evilValleyTile, EDGE_C);
    p = new Path(highPassTile->getClearing(6), evilValleyTile->getClearing(5));
    highPassTile->addConnectedTile(cavernTile, EDGE_E);
    p = new Path(highPassTile->getClearing(3), cavernTile->getClearing(5));

    oakWoodsTile->addConnectedTile(badValleyTile, EDGE_D);
    p = new Path(oakWoodsTile->getClearing(5), badValleyTile->getClearing(1));
    oakWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_C);
    p = new Path(oakWoodsTile->getClearing(5), mapleWoodsTile->getClearing(5));
    oakWoodsTile->addConnectedTile(deepWoodsTile, EDGE_B);
    p = new Path(oakWoodsTile->getClearing(4), deepWoodsTile->getClearing(1));
    oakWoodsTile->addConnectedTile(ledgesTile, EDGE_F);
    p = new Path(oakWoodsTile->getClearing(2), ledgesTile->getClearing(5));

    evilValleyTile->addConnectedTile(cliffTile, EDGE_C);
    p = new Path(evilValleyTile->getClearing(2), cliffTile->getClearing(1));
    evilValleyTile->addConnectedTile(ledgesTile, EDGE_D);
    p = new Path(evilValleyTile->getClearing(4), ledgesTile->getClearing(2));
    
    ledgesTile->addConnectedTile(cliffTile, EDGE_F);
    p = new Path(ledgesTile->getClearing(3), cliffTile->getClearing(2));

    deepWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_B);
    p = new Path(deepWoodsTile->getClearing(5), mapleWoodsTile->getClearing(5));
    deepWoodsTile->addConnectedTile(cragTile, EDGE_D);
    p = new Path(deepWoodsTile->getClearing(1), cragTile->getClearing(2));
    deepWoodsTile->addConnectedTile(darkValleyTile, EDGE_E);
    p = new Path(deepWoodsTile->getClearing(2), darkValleyTile->getClearing(5));
    deepWoodsTile->addConnectedTile(curstValleyTile, EDGE_F);
    p = new Path(deepWoodsTile->getClearing(2), curstValleyTile->getClearing(2));

    curstValleyTile->addConnectedTile(nutWoodsTile, EDGE_B);
    p = new Path(curstValleyTile->getClearing(4), nutWoodsTile->getClearing(5));
    curstValleyTile->addConnectedTile(darkValleyTile, EDGE_D);
    p = new Path(curstValleyTile->getClearing(1), darkValleyTile->getClearing(1));

    nutWoodsTile->addConnectedTile(awfulValleyTile, EDGE_D);
    p = new Path(nutWoodsTile->getClearing(2), awfulValleyTile->getClearing(5));
    nutWoodsTile->addConnectedTile(ruinsTile, EDGE_E);
    p = new Path(nutWoodsTile->getClearing(4), ruinsTile->getClearing(1));
    nutWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_F);
    p = new Path(nutWoodsTile->getClearing(5), mapleWoodsTile->getClearing(2));

    mapleWoodsTile->addConnectedTile(ruinsTile, EDGE_E);
    p = new Path(mapleWoodsTile->getClearing(2), ruinsTile->getClearing(5));
    mapleWoodsTile->addConnectedTile(cavesTile, EDGE_F);
    p = new Path(mapleWoodsTile->getClearing(4), cavesTile->getClearing(5));

    badValleyTile->addConnectedTile(cavesTile, EDGE_B);
    p = new Path(badValleyTile->getClearing(2), cavesTile->getClearing(2));
    badValleyTile->addConnectedTile(mountainTile, EDGE_C);
    p = new Path(badValleyTile->getClearing(4), mountainTile->getClearing(5));
	badValleyTile->addConnectedTile(cavernTile, EDGE_D);
	p = new Path(badValleyTile->getClearing(4), cavernTile->getClearing(1));

    mountainTile->addConnectedTile(pineWoodsTile, EDGE_B);
    p = new Path(mountainTile->getClearing(2), pineWoodsTile->getClearing(4));

    cavesTile->addConnectedTile(pineWoodsTile, EDGE_F);
    p = new Path(cavesTile->getClearing(1), pineWoodsTile->getClearing(5));

    ruinsTile->addConnectedTile(awfulValleyTile, EDGE_D);
    p = new Path(ruinsTile->getClearing(2), awfulValleyTile->getClearing(1));
    ruinsTile->addConnectedTile(lindenWoodsTile, EDGE_E);
    p = new Path(ruinsTile->getClearing(2), lindenWoodsTile->getClearing(4));

    awfulValleyTile->addConnectedTile(lindenWoodsTile, EDGE_B);
    p = new Path(awfulValleyTile->getClearing(2), lindenWoodsTile->getClearing(5));
}

void Game::setupValleyStuff()
{
    
	vector<Tile*>* tileList = gameBoard->getTileByType(TILE_VALLEY);
	Clearing * destinationClearing = NULL;
	cout << "Placing Dwellings.." <<endl;
	for(vector<Tile*>::iterator it = tileList->begin(); it != tileList->end(); ++it){
		if((*it)->getWarningChit()->getName() == "BONES V") //mark as spot to place ghosts
			destinationClearing = (*it)->getClearing(5);
		else if((*it)->getWarningChit()->getName() == "RUINS V")
			gameBoard->addDwelling((*it)->getClearing(5)->buildDwelling(GUARD));
		else if((*it)->getWarningChit()->getName() == "DANK V")
			gameBoard->addDwelling((*it)->getClearing(5)->buildDwelling(CHAPEL));
		else if((*it)->getWarningChit()->getName() == "SMOKE V")
			gameBoard->addDwelling((*it)->getClearing(5)->buildDwelling(HOUSE));
		else if((*it)->getWarningChit()->getName() == "STINK V")
			gameBoard->addDwelling((*it)->getClearing(5)->buildDwelling(INN));
	}
	if(destinationClearing == NULL){
		cout << "ERR:: setupValleyStuff: Ghosts cannot find tile to spawn in BREAKING!!!" <<endl;
		return;
	}

	cout << "Setting up ghosts" <<endl;
	vector<Monster*>* ghostList = gameBoard->getSpawner()->getGhosts();
	for(vector<Monster*>::iterator iter = ghostList->begin(); iter != ghostList->end(); ++iter){
		(*iter)->move(destinationClearing);
		activeMonsters->push_back(*iter);
	}
	delete tileList;	
}

void Game::customSetup()
{
    cout << "Custom Setup Started...." <<endl;
    int listCount = 0;
    int chitIndex = -1;
    //master list of tiles
    vector<Tile*> * woodsMasterList = gameBoard->getTileByType(TILE_WOODS);
    vector<Tile*> * cavesMasterList = gameBoard->getTileByType(TILE_CAVES);
    vector<Tile*> * mountainMasterList = gameBoard->getTileByType(TILE_MOUNTAIN);
    vector<Tile*> * valleyMasterList = gameBoard->getTileByType(TILE_VALLEY);
    
    //list we will construct to work with.
    vector<Tile*> woodsList;
    vector<Tile*> cavesList;
    vector<Tile*> mountainList;
    vector<Tile*> valleyList;

    //list of warning chits
    //these are constructed and handed to us (not master list) 
    //therefore we can pop and delete from them.
    vector<Warning*>* woodsWarningList = gameBoard->getWarningsByType(TILE_WOODS);
    vector<Warning*>* valleyWarningList = gameBoard->getWarningsByType(TILE_VALLEY);
    vector<Warning*>* cavesWarningList = gameBoard->getWarningsByType(TILE_CAVES);
    vector<Warning*>* mountainWarningList = gameBoard->getWarningsByType(TILE_MOUNTAIN);

    //getting site and sound chit and populating a general siteAndSoundList.
    vector<Site*>* siteList = gameBoard->getSiteChits();

    vector<Sound*>* soundList = gameBoard->getSoundChits();
    vector<Chit*> siteAndSoundList;

    Lost* lostCity = (Lost*) gameBoard->getChitByName("Lost City");
    vector<Chit*>* lostCityList = new vector<Chit*>;
    Lost* lostCastle = (Lost*)gameBoard->getChitByName("Lost Castle");
    vector<Chit*>* lostCastleList = new vector<Chit*>;

    //populating our working lists.
    for(vector<Site*>::iterator iter = siteList->begin(); iter!= siteList->end(); ++iter){
        siteAndSoundList.push_back(*iter); 
    }
    for(vector<Sound*>::iterator iter = soundList->begin(); iter!= soundList->end(); ++iter){
        siteAndSoundList.push_back(*iter);
    }
    for(vector<Tile*>::iterator iter = woodsMasterList->begin(); iter!= woodsMasterList->end(); ++iter){
        woodsList.push_back(*iter);
    }
    for(vector<Tile*>::iterator iter = cavesMasterList->begin(); iter!= cavesMasterList->end(); ++iter){
        cavesList.push_back(*iter);
    }
    for(vector<Tile*>::iterator iter = mountainMasterList->begin(); iter!= mountainMasterList->end(); ++iter){
        mountainList.push_back(*iter);
    }
    for(vector<Tile*>::iterator iter = valleyMasterList->begin(); iter!= valleyMasterList->end(); ++iter){
        valleyList.push_back(*iter);
    }

    cout << "Setup Lost City" << endl;
    for(int i=0; i<5; i++){
        cout << "Please Select an Item from the list to add to the Lost City...." <<endl;
        //displaying the chits
        for(vector<Chit*>::iterator iter = siteAndSoundList.begin(); iter!= siteAndSoundList.end(); ++iter){
            cout << listCount << ": "<< (*iter)->getName() << endl;
            listCount++;
        }
        while(chitIndex >= siteAndSoundList.size() || chitIndex < 0){
            cout << "Chit you wish to add to Lost City: ";
            cin >> chitIndex;
        }
		lostCityList->push_back(siteAndSoundList.at(chitIndex));
        siteAndSoundList.erase(siteAndSoundList.begin() + chitIndex);
        chitIndex = -1;
        listCount = 0;
    }
    lostCity->populateCity(lostCityList);

    cout << "Setup Lost Castle" <<endl;
    for(int i=0; i<5; i++){
        cout << "Please Select an Item from the list to add to the Lost Castle...." <<endl;
        //displaying the chits
        for(vector<Chit*>::iterator iter = siteAndSoundList.begin(); iter!= siteAndSoundList.end(); ++iter){
            cout << listCount << ": "<< (*iter)->getName() << endl;
            listCount++;
        }
        while(chitIndex >= siteAndSoundList.size() || chitIndex < 0){
            cout << "Chit you wish to add to Lost Castle: ";
            cin >> chitIndex;
        }
		lostCastleList->push_back(siteAndSoundList.at(chitIndex));
        siteAndSoundList.erase(siteAndSoundList.begin() + chitIndex);
        chitIndex = -1;
        listCount = 0;
    }
    lostCastle->populateCity(lostCastleList);
    siteAndSoundList.push_back(lostCity);
    siteAndSoundList.push_back(lostCastle);

    cout << "Setup Mountain Tiles" <<endl;
	for(vector<Tile*>::iterator iter = mountainList.begin(); iter != mountainList.end(); ++iter)
		customTileSetup(*iter, mountainWarningList, &siteAndSoundList);

    cout << "Setup Caves Tiles" <<endl;
	for(vector<Tile*>::iterator iter = cavesList.begin(); iter != cavesList.end(); ++iter)
		customTileSetup(*iter, cavesWarningList, &siteAndSoundList);

    cout << "Setup Woods Tiles" <<endl;
	for(vector<Tile*>::iterator iter = woodsList.begin(); iter != woodsList.end(); ++iter)
		customTileSetup(*iter, woodsWarningList, NULL);
	

    cout << "Setup Valley Tiles" <<endl;
	for(vector<Tile*>::iterator iter = valleyList.begin(); iter != valleyList.end(); ++iter)
		customTileSetup(*iter, valleyWarningList, NULL);

	cout << "Custom Setup Complete" <<endl;
	
}

void Game::customTileSetup(Tile* tile, vector<Warning*>* warningList, vector<Chit*>* siteAndSoundList)
{
	int count = 0;
	int index = -1;
	cout << "Choose a Warning From the List" <<endl;
	for(vector<Warning*>::iterator iter = warningList->begin(); iter != warningList->end(); ++iter){
		cout << count << ": " <<(*iter)->getName() << endl;
		count++;
	}

	while(index >= warningList->size() || index < 0){
            cout << "Warning you wish to add to " << tile->getName() <<": ";
            cin >> index;
	}
	tile->addWarningChit(warningList->at(index));
    warningList->erase(warningList->begin() + index);
	count = 0;
	index = -1;
	//checking to see if its a woods or valley, if it is we can skip siteAndSound setup
	if(!siteAndSoundList == NULL){
		cout << "Choose a Warning/sound From the List" <<endl;
		for(vector<Chit*>::iterator iter = siteAndSoundList->begin(); iter != siteAndSoundList->end(); ++iter){
			cout << count << ": " <<(*iter)->getName() << endl;
			count++;
		}
		while(index >= siteAndSoundList->size() || index < 0){
            cout << "Chit you wish to add to " << tile->getName() <<": ";
            cin >> index;
			}
		tile->addSiteOrSoundChit(siteAndSoundList->at(index));
		siteAndSoundList->erase(siteAndSoundList->begin() + index);
	}
}
Board* Game::getBoard()
{
	return gameBoard;
}

void Game::testGame()
{
    cout << "Game Run Tests..." << endl;
    cout << "WARN: This should not be run with a normal GAME, unexpected behaviour" << endl;

    cout << "Testing Combat Manager" <<endl;
	Character* attacker = new Character(Amazon);
    Character* defender = new Character(Elf);
    Counter* attackerMoveCounter = NULL;
    Counter* defenderMoveCounter = NULL;
    Counter* attackerFightCounter = NULL;
    Counter* defenderFightCounter = NULL;
    CombatManager* rumble = new CombatManager(attacker, defender);
    

    //getting the desired move chit
    for(vector<Counter*>::iterator iter = attacker->getCounters()->begin(); iter != attacker->getCounters()->end(); ++iter){
        if((*iter)->getType() == COUNTER_MOVE && (*iter)->getSpeed() == 4)
            attackerMoveCounter = *iter;
    }

    for(vector<Counter*>::iterator iter = defender->getCounters()->begin(); iter != defender->getCounters()->end(); ++iter){
        if((*iter)->getType() == COUNTER_MOVE && (*iter)->getSpeed() == 3)
            defenderMoveCounter = *iter;
    }
	//getting combat chits
	for(vector<Counter*>::iterator iter = attacker->getCounters()->begin(); iter != attacker->getCounters()->end(); ++iter){
        if((*iter)->getType() == COUNTER_FIGHT && (*iter)->getSpeed() == 3)
            attackerFightCounter = *iter;
    }

    for(vector<Counter*>::iterator iter = defender->getCounters()->begin(); iter != defender->getCounters()->end(); ++iter){
        if((*iter)->getType() == COUNTER_FIGHT && (*iter)->getSpeed() == 4)
            defenderFightCounter = *iter;
    }

    	
	cout << "Active Combat Test"  <<endl;
	for(int i=0; i <2; i++){
		cout << endl <<"=== New Round of Combat Started ===" << endl <<endl;
		cout << "Testing No One Flees" <<endl;
		rumble->submitEncounter(attacker, false, attackerMoveCounter);
		rumble->submitEncounter(defender, false, defenderMoveCounter);
		rumble->runEncounter();
		if(rumble->EncounterVictorRun()){
			cout << "A Combatant Fled" << endl;
		}
		else{
			cout << "No one Fled" <<endl;
		}

		rumble->submitMelee(attacker, attackerFightCounter, FIGHT_SMASH, attackerMoveCounter, MOVE_DUCK , SHIELD_NONE);
		rumble->submitMelee(defender, defenderFightCounter, FIGHT_SMASH, defenderMoveCounter, MOVE_DUCK, SHIELD_NONE);
		rumble->runMelee();
		rumble->runResolve();

		if(rumble->getResult(attacker) == ACTION_MISS)
			cout << "Defender missed on the Attacker" <<endl;

		if(rumble->getResult(defender) == ACTION_MISS)
			cout << "Attacker missed on the  Defender" <<endl;

		if(rumble->getResult(attacker) == ACTION_DAMAGED)
			cout << "Defender damages Attacker's armor" <<endl;

		if(rumble->getResult(defender) == ACTION_DAMAGED)
			cout << "Attacker damages Defender armor" <<endl;

		if(rumble->getResult(attacker) == ACTION_WOUND)
			cout << "Defender wounds Attacker for: "<<rumble->getWounds(attacker) <<endl;

		if(rumble->getResult(defender) == ACTION_WOUND)
			cout << "Attacker wounds Defender for: " <<rumble->getWounds(defender) <<endl;

		if(rumble->getResult(attacker) == ACTION_DEAD)
			cout << "Defender kills Attacker" <<endl;

		if(rumble->getResult(defender) == ACTION_DEAD)
			cout << "Attacker kils Defender" <<endl;	
	}

	if(rumble->getCurrentPhase() == PHASE_MISSED){
		cout << "Combat Ended Since you guys couldnt hit shit" <<endl;
	}


    cout << "Combat Manager Tested" << endl;

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
	cout << "Rolling Hide Request" <<endl;
    int d1 = rollDice();
    int d2 = rollDice();
    int diceUsed = (d1>d2) ? d1 : d2;

    if(diceUsed == 6)
        return false;
    
    if(player->isHidden())
        return true;
    player->toggleHide();
    return true;
}

DiscoveryType Game::searchPeerRequest() {
	cout << "Rolling Peer Request" <<endl;
	int d1 = rollDice();
	int d2 = rollDice();
	int diceUsed = (d1>d2) ? d1 : d2;
	
	switch (diceUsed) {
	case 1: return DISCOVER_CHOICE;
	case 2: return DISCOVER_PATHACLUES;
	case 3: return DISCOVER_ENEMAPATH;
	case 4: return DISCOVER_HENEMIES;
	case 5: return DISCOVER_CLUES;
	default: return DISCOVER_NOTHING;
	}
}

DiscoveryType Game::searchLocateRequest() {
	cout << "Rolling LOCATE" <<endl;
	int d1 = rollDice();
	int d2 = rollDice();
	int diceUsed = (d1>d2) ? d1 : d2;

	switch (diceUsed) {
	case 1: return DISCOVER_CHOICE;
	case 2: return DISCOVER_PASSACLUES;
	case 3: return DISCOVER_SPASS;
	case 4: return DISCOVER_CHIT;
	default: return DISCOVER_NOTHING;
	}
}

Treasure* Game::searchLootRequest(Character* player) {
    cout << "Rolling Loot Request: " <<endl;
	int d1 = rollDice();
	int d2 = rollDice();
	int diceUsed = (d1>d2) ? d1 : d2;

	Chit* chit = player->getCurrentLocation()->getTile()->getSiteOrSoundChit();
	if (chit->getType() == CHIT_LOST) {
		int i = 0;
		vector<Chit*> *contents = chit->getContents();
		do {
			chit = contents->at(i);
			++i;
		} while((i < contents->size()) 
			&& ((chit->getType() != CHIT_SITE)
				&&(chit->getClearingNum() != player->getCurrentLocation()->getClearingNum())));
	}
	return chit->loot(diceUsed);
}

bool Game::canLoot(Character* player) {
	Clearing *location = player->getCurrentLocation();
	if (location->getTile()->getSiteOrSoundChit() == NULL)
		return false;
	if (location->getClearingNum() == location->getTile()->getSiteOrSoundChit()->getClearingNum()) {
		if (player->hasDiscovered(location->getTile()->getSiteOrSoundChit())) {
			return true;
		}
	}
	return false;
	//todo finish this when clearing have sites, and players have disoveries
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

    if(player->isBlocked()){
        cout << "Player is blocked" <<endl;
        return false;
    }
    
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
	int num =0;
	if(!cheatMode)
		num = rand() % 6 + 1;
	else{
		while(num < 1 || num > 6){
			cout << "Game::rollDice CHEATMODE Enter Roll (1-6)";
			cin >> num;
		}
	}
	cout <<"Returning Dice Roll: " <<num << endl;
	return num;

}
Dwelling* Game::getDwelling(DwellingType dwellingType)
{
	return gameBoard->getDwelling(dwellingType);
}

void Game::spawnMonsters(int diceUsed)
{
    MonsterSpawner* lookupTable = gameBoard->getSpawner();
    vector<Monster*>* spawnedMonsters;
	Chit* siteSoundChit = NULL;
	vector<Chit*>* lostList = NULL;
    //looping over players to check if any monsters spawned around them.
    for(int i=0; i < MAXPLAYERS; i++){
        if(players[i] == NULL) //if there is not a player there dont do anything
            continue;

        //getting list of monsters that spawned
		siteSoundChit = players[i]->getCurrentLocation()->getTile()->getSiteOrSoundChit();
		if(siteSoundChit != NULL && siteSoundChit->getType() == CHIT_LOST){
			lostList = siteSoundChit->getContents();
			for(vector<Chit*>::iterator iter = lostList->begin(); iter != lostList->end(); ++iter){
				spawnedMonsters = lookupTable->spawn(players[i]->getCurrentLocation(), *iter, diceUsed);
				if(spawnedMonsters == NULL) //if there are no monsters to spawn we can skip
					continue;
				for(vector<Monster*>::iterator it = spawnedMonsters->begin(); it != spawnedMonsters->end(); ++it){
					activeMonsters->push_back(*it);
				}
			}
		}
		else{
			spawnedMonsters = lookupTable->spawn(players[i]->getCurrentLocation(), siteSoundChit, diceUsed);
				if(spawnedMonsters == NULL) //if there are no monsters to spawn we can skip
					continue;
			for(vector<Monster*>::iterator it = spawnedMonsters->begin(); it != spawnedMonsters->end(); ++it){
				activeMonsters->push_back(*it);
			}
		}
        

        //adding our spawned monsters to the active monster list.
        
    }
}

void Game::moveMonsters()
{
	for(int i=0; i<MAXPLAYERS; i++){
		if(players[i] == NULL)
			continue;
		for(vector<Monster*>::iterator iter = activeMonsters->begin(); iter!=activeMonsters->end(); ++iter){
			if(players[i]->getCurrentLocation()->getTile() == (*iter)->getLocation()->getTile())
				(*iter)->move(players[i]->getCurrentLocation());
		}
	}

}

vector<Monster*>* Game::getActiveMonsters()
{
    return activeMonsters;
}

void Game::checkBlocks()
{
	Clearing* currentClearing = NULL;
	for(int i=0; i <MAXPLAYERS; i++){
		if(players[i] == NULL)
			continue;
		Clearing* currentClearing = players[i]->getCurrentLocation();
		//checking to see if any monsters are in the current position to block those monsters and the player.
		if(players[i]->isHidden())
			return;

		for(vector<Monster*>::iterator iter = activeMonsters->begin(); iter != activeMonsters->end(); ++iter){
			if((*iter)->getLocation() == currentClearing && !(*iter)->isBlocked()){
				(*iter)->setBlock(true);
				if(!players[i]->isBlocked())
				players[i]->setBlock(true);
				return;
			}
		}

		//NOTE HANDLE OTHER PLAYER BLOCKING HERE????

		//did not find a monster anymore, if they are blocked unblock.
		if(players[i]->isBlocked())
			players[i]->setBlock(false);
	}
}

void Game::killMonster(Monster* deadMonster, Character* player)
{
	for(vector<Monster*>::iterator iter = activeMonsters->begin(); iter!= activeMonsters->end(); ++iter){
		if((*iter)->getID() == deadMonster->getID()){
			activeMonsters->erase(iter);
			deadMonster->kill();
			deadMonster->setBlock(false);
			player->setBlock(false);
			player->addFame(deadMonster->getFame());
			player->addNotoriety(deadMonster->getNotoriety());
            return;
		}
	}
}

void Game::restCounter(Counter* aCounter){
    aCounter->heal();
}