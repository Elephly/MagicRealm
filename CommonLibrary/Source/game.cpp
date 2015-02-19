#include "game.h"

Game::Game()
{
    p1 = new Character(Elf);
    gameBoard = new Board();
    cout << "Game Initialized" <<endl;
}

Game::~Game()
{
    delete p1;
    delete gameBoard;
    p1 = NULL;
    gameBoard = NULL;
    cout << "Game Destroyed" << endl;
}

void Game::setupGame(bool cm)
{
    cheatMode = cm;
    cout << "Setting Up Game..." <<endl;

    Clearing* c1 = NULL;
    Clearing* c2 = NULL;
    Clearing* c3 = NULL;
    Clearing* c4 = NULL;
    Path* p = NULL;
    string *resultString = NULL;

    //setting up the Oak Woods Tile
    Tile* oakWoodsTile = new Tile(EDGE_E, "Oak Woods");
    c1 = new Clearing(2, oakWoodsTile);
    c2 = new Clearing(4, oakWoodsTile);
    c3 = new Clearing(5, oakWoodsTile);
    p = new Path(c1, c2, false);
    p = new Path(c1, EDGE_B);
    p = new Path(c3, EDGE_C);
    p = new Path(c3, EDGE_D);
    p = new Path(c1, EDGE_E);
    p = new Path(c1, EDGE_F);
    gameBoard->addTile(oakWoodsTile);

    if(gameBoard->getTile("Oak Woods") != NULL)
        cout << "Tile Found!!!" << endl;

    cout << "Attempting to placing player1 in Oak Woods Clearing 2" <<endl;
    if(moveRequest(p1, c1)){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }
    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //setting up the Bad Valley Tile.
    Tile* badValleyTile = new Tile(EDGE_F, "Bad Valley");
    c1 = new Clearing(1, badValleyTile);
    c2 = new Clearing(2, badValleyTile);
    c3 = new Clearing(4, badValleyTile);
    c4 = new Clearing(5, badValleyTile);

    //regular paths
    p = new Path(c1, c3, false);
    p = new Path(c2, c4, false);

    //border paths
    p = new Path(c1, EDGE_F);
    p = new Path(c2, EDGE_B);
    p = new Path(c3, EDGE_C);
    p = new Path(c3, EDGE_D);
    p = new Path(c4, EDGE_E);

    gameBoard->addTile(badValleyTile);
    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //Setting up the Maple Woods Tile
    Tile* mapleWoodsTile = new Tile(EDGE_C, "Maple Woods");

    c1 = new Clearing(2, mapleWoodsTile);
    c2 = new Clearing(4, mapleWoodsTile);
    c3 = new Clearing(5, mapleWoodsTile);

    p = new Path(c1, c2, false);
    
    p = new Path(c1, EDGE_D);
    p = new Path(c1, EDGE_E);
    p = new Path(c2, EDGE_F);
    p = new Path(c3, EDGE_B);
    p = new Path(c3, EDGE_C);

    gameBoard->addTile(mapleWoodsTile);

    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //setting up adjacent stuff
    oakWoodsTile->addAdjacentTile(badValleyTile);
    oakWoodsTile->addAdjacentTile(mapleWoodsTile);

    badValleyTile->addAdjacentTile(mapleWoodsTile);
}
void Game::runGame()
{
    cout << "Game Run..." << endl;
    string *resultString = NULL;
    Tile* theTile= gameBoard->getTile("Oak Woods");
    cout << "Attempting to move p1 to clearing 4" << endl;
    if(moveRequest(p1, theTile->getClearing(4))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }
}

bool Game::moveRequest(Character* player, Clearing* requestedClearing)
{
    Clearing* playerLoc = NULL;
    vector<Path*>* pathsAvailable =  NULL;
    //checking to see our data is valid
    if(requestedClearing == NULL){
        cout << "ERR moveRequest: Requested clearing NULL" <<endl;
        return false;
    }
    if (playerLoc == NULL){
        requestedClearing->addCharacter(player);
        player->moveToClearing(requestedClearing);
        return true;
    }
    //data valid we can populate
    playerLoc = player->getCurrentLocation();
    pathsAvailable = playerLoc->getPaths();

    //TODO Check if Player Can move!!!!
    
    //going through possible cases of different types of move
    if(playerLoc == requestedClearing){
        cout << "ERR: Player Requested the location they are already in" <<endl;
        return false;
    }
    
    if(playerLoc->getTile() != requestedClearing->getTile())
    {
        return false;
        //do things that require border checking.
    }
    else //standard path checking
    {
        for(vector<Path*>::iterator it = pathsAvailable->begin(); it != pathsAvailable->end(); ++it){
            if((*it)->getEnd(playerLoc) == requestedClearing){
                //Found a path, Check if .
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