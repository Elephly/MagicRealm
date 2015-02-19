#ifndef GAME_H
#define GAME_H

#include "shared.h"
#include "Board.h"
#include "Tile.h"
#include "Clearing.h"
#include "Path.h"
#include "Character.h"


class COMMONLIBRARY_EXPORT Game{

public:
	Game();
    ~Game();
    void runGame();
    void setupGame();
    /*
    *   MoveRequest
    *   In:     Pointer of the Character wishing to move
                Pointer of Clearing they wish to move to
    *   Out:    boolean whether move was successful or not
    */
    bool moveRequest(Character* player, Clearing* requestedClearing);
private:
    Board* gameBoard;
    Character* p1;
};

#endif // GAME_H