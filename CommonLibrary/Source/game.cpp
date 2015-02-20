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
    oakWoodsTile->addConnectedTile(badValleyTile, EDGE_D);
    oakWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_C);

    //plopping character
    cout << "Placing Character in Bad Valley Clearing #4..." <<endl <<endl;
    if(moveRequest(p1, gameBoard->getTile("Bad Valley")->getClearing(4))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }
    cout << "Finished Setup..." <<endl <<endl;
}
void Game::runGame()
{
    cout << "Game Run..." << endl;
    string *resultString = NULL;
    Tile* theTile= gameBoard->getTile("Bad Valley");

    resultString = p1->getCurrentLocation()->toString();
    cout << "player1 starts at: " << *resultString << endl;

    delete resultString;
    resultString = NULL;
    cout << "#1: Attempting to move p1 to clearing 5 (Should Fail)" << endl;
    if(moveRequest(p1, theTile->getClearing(5))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved INCORRECTLY TO: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }
    else{
        cout << "Player Correctly rejected from moving (TEST FAILED)" <<endl;
    }

    cout << "#2: Attempting to move p1 to clearing 1 (Should Pass)" << endl;
    if(moveRequest(p1, theTile->getClearing(1))){
        resultString = p1->getCurrentLocation()->toString();
        cout << "player1 moved to clearing: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }

    //moving to different tiles
    if(moveRequest(p1, gameBoard->getTile("Oak Woods")->getClearing(5))){
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
    
    if(playerLoc->getTile() != requestedClearing->getTile())
    {
        cout << "TRACK: Player Requested the location in another tile.." <<endl;
        return moveBetweenTileRequest(player, requestedClearing);
        //do things that require border checking.
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

bool Game::moveBetweenTileRequest(Character* player, Clearing* requestedClearing)
{
    //determining if the player is connected.
    Clearing* connectedClearing = player->getCurrentLocation()->getTile()->getConnectedClearing(requestedClearing->getTile());
    if(connectedClearing != NULL){
        cout << "TRACK: Tiles are Connected. "<< endl;
        string* resultString = connectedClearing->toString();
        cout << "The Connected Clearing is: " << *resultString << endl;
        delete resultString;
        resultString = NULL;
    }
    return false;
}
void Game::doTurn()
{
}