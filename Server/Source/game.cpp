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

    gameBoard->addTile(oakWoodsTile);

    if(gameBoard->getTile("Oak Woods") != NULL)
        cout << "Tile Found!!!" << endl;
    
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