#include "game.h"

Game::Game()
{
    //initalizing players list
    for(int i=0; i < MAXPLAYERS; i ++)
        players[i] = NULL;

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
	Dwelling* chapel = new Dwelling(CHAPEL, gameBoard->getTile("Awful Valley")->getClearing(5), false);
	dwellings[0] = chapel;
    gameBoard->addDwelling(chapel);
	Dwelling* guard = new Dwelling(GUARD, gameBoard->getTile("Dark Valley")->getClearing(5), false);
	dwellings[1] = guard;
    gameBoard->addDwelling(guard);
	Dwelling* house = new Dwelling(HOUSE, gameBoard->getTile("Curst Valley")->getClearing(5), false);
	dwellings[2] = house;
    gameBoard->addDwelling(house);
	Dwelling* inn = new Dwelling(INN, gameBoard->getTile("Bad Valley")->getClearing(5), false);
	dwellings[3] = inn;
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

bool Game::addPlayer(CharacterTypes newPlayerType)
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

void Game::removePlayer(CharacterTypes oldPlayerType)
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

Character* Game::getPlayer(CharacterTypes charType)
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

Dwelling* Game::getDwelling(DwellingType dwellingType)
{
	// I realize that the dwellings array is setup such that each DwellingType
	// value maps onto its proper corresponding array index, but this way
	// is safer I believe.
	for (int i = 0; i < MAXDWELLINGS; i++)
	{
		if (dwellings[i]->getType() == dwellingType)
		{
			return dwellings[i];
		}
	}
	return NULL;
}

void Game::doTurn()
{
}