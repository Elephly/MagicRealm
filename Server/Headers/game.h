#ifndef GAME_H
#define GAME_H

#include "shared.h"
#include "Board.h"
#include "Tile.h"
#include "Clearing.h"
#include "Path.h"
#include "Character.h"


class Game{

public:
	Game();
    ~Game();
    void runGame();
private:
    Board* gameBoard;
    Character* p1;
};

#endif // GAME_H