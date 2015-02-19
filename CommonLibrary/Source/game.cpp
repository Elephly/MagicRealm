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

void Game::setupGame()
{
    cout << "Setting Up Game..." <<endl;

    Clearing* c1 = NULL;
    Clearing* c2 = NULL;
    Clearing* c3 = NULL;
    Clearing* c4 = NULL;
    Path* p = NULL;

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
    p1->moveToClearing(c1);
    string *resultString = p1->getCurrentLocation()->toString();
    cout << "player1 moved to clearing: " << *resultString << endl;
    delete resultString;
    //resetting the clearings
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    /* Adding More Tiles
    //setting up the Bad Valley Tile.
    Tile* badValleyTile = new Tile();

    //Setting up the Maple Woods Tile
    Tile* mapleWoodsTile;
    */
}
void Game::runGame()
{
    cout << "Game Run..." << endl;
}

bool Game::moveRequest(Character* player, Clearing* requestedClearing)
{
    Clearing* playerLoc = player->getCurrentLocation();
    vector<Path*>* pathsAvailable = playerLoc->getPaths();
    if(playerLoc == requestedClearing){
        cout << "ERR: Player Requested the location they are already in" <<endl;
        return false;
    }
    //TODO Check if Player Can move!!!!s
    else if(playerLoc->getTile() != requestedClearing->getTile())
    {
        return false;
        //do things that require border checking.
    }
    else //standard path checking
    {
        for(vector<Path*>::iterator it = pathsAvailable->begin(); it != pathsAvailable->end(); ++it){
            if((*it)->getEnd(playerLoc) == requestedClearing){
                //Found a path, we can move.
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