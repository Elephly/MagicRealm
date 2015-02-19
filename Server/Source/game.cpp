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
}
void Game::runGame()
{
    cout << "Game Run..." << endl;
}