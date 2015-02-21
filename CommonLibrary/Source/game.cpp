#include "game.h"

Game::Game()
{
    gameBoard = new Board();
    cout << "Game Initialized" <<endl;
}

Game::~Game()
{
	if (p1 != 0)
	{
		delete p1;
		p1 = NULL;
	}
	if (gameBoard != 0)
	{
		delete gameBoard;
		gameBoard = NULL;
	}
    cout << "Game Destroyed" << endl;
}

void Game::setupGame(bool cm, Character* p)
{
    cheatMode = cm;
	p1 = p;
    cout << "Setting Up Game..." <<endl;
    setupTiles();
    string * resultString;

    //plopping character
    cout << "Placing Character in Bad Valley Clearing #4..." <<endl <<endl;
    if(moveRequest(p1, gameBoard->getTile("Border Land")->getClearing(1))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }


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

    //setting up connected stuff and connected paths.	
    borderLandTile->addConnectedTile(oakWoodsTile, EDGE_A);
    p = new Path(borderLandTile->getClearing(2), oakWoodsTile->getClearing(2), false);
    borderLandTile->addConnectedTile(badValleyTile, EDGE_B);
    p = new Path(borderLandTile->getClearing(1), badValleyTile->getClearing(5), false);
    oakWoodsTile->addConnectedTile(badValleyTile, EDGE_D);
    p = new Path(oakWoodsTile->getClearing(5), badValleyTile->getClearing(1), false);
    oakWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_C);
    p = new Path(oakWoodsTile->getClearing(5), mapleWoodsTile->getClearing(5), false);
}

Board* Game::getBoard()
{
	return gameBoard;
}

void Game::runGame()
{
    cout << "Game Run..." << endl;
    string *resultString = NULL;
    Tile* theTile= gameBoard->getTile("Border Land");

    resultString = p1->getCurrentLocation()->toString();
    cout << "player1 starts at: " << *resultString << endl;

    delete resultString;
    resultString = NULL;
    cout << "#1: Attempting to move p1 to clearing 6 (Should Fail)" << endl;
    if(moveRequest(p1, theTile->getClearing(5))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved INCORRECTLY TO: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }
    else
        cout << "Player Correctly rejected from moving (TEST FAILED)" <<endl;

    cout << "#2: Attempting to move p1 to clearing 6 (Should Pass)" << endl;
    if(moveRequest(p1, theTile->getClearing(6))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }

    cout << "#2: Attempting to move p1 to back clearing 1 (Should Pass)" << endl;
    if(moveRequest(p1, theTile->getClearing(1))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }

    //moving to different tiles
    if(moveRequest(p1, gameBoard->getTile("Bad Valley")->getClearing(5))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }

    cout << "player1 moved to Oak Woods Clearing 5 (Should fail): " << endl;
    //moving to another tile
    if(moveRequest(p1, gameBoard->getTile("Oak Woods")->getClearing(5)))
        cout << "Move Passed THIS SHOULD NEVER BE VISIBLE"<< endl;
    else
        cout << "Move Failed (Test Passed)"<< endl;
    
    cout << "player1 moved to One they already in " << endl;
    if(moveRequest(p1, gameBoard->getTile("Bad Valley")->getClearing(5)))
        cout << "Move Passed THIS SHOULD NEVER BE VISIBLE"<< endl;
    else
        cout << "Move Failed (Test Passed)"<< endl;

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

void Game::doTurn()
{
}