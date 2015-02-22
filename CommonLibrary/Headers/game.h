#ifndef GAME_H
#define GAME_H

#include "shared.h"
#include "Board.h"
#include "Tile.h"
#include "Clearing.h"
#include "Path.h"
#include "Character.h"
#include "action.h"
#include "recordedTurn.h"
#include "dwelling.h"

class COMMONLIBRARY_EXPORT Game{

public:
	Game();
    ~Game();
    void runGame();
    void setupGame(bool cm);
    void doTurn();

    /*
    *   addPlayer
    *   in:     CharacterType to be added to the array
    *   out:    successfully added or not (list full)
    */
    bool addPlayer(CharacterTypes newPlayerType);
    /*
    *   addPlayer
    *   in:     Character pointer to be added to the array
    *   out:    successfully added or not (list full)
    */
    bool addPlayer(Character* newPlayer);

    /*
    *   removePlayer
    *   in:     Character point to be removed AND DESTROYED.
    */
    void removePlayer(CharacterTypes oldPlayerType);

    /*
    *   getPlayer
    *   returns the player object playing that CharacterType
    */
    Character* getPlayer(CharacterTypes charType);

	Board* getBoard();
    /*
    *   MoveRequest
    *   In:     Pointer of the Character wishing to move
                Pointer of Clearing they wish to move to
    *   Out:    boolean whether move was successful or not
    */
    bool moveRequest(Character* player, Clearing* requestedClearing);

    /*
    *   move
    *   Pointer of the Character wishing to move
    *   Pointer of Clearing they wish to move to
    */
    void move(Character* player, Clearing* requestedClearing);

	/*
	*	getDwelling
	*	In:		DwellingType for requested Dwelling
	*	Out:	Pointer of requester Dwelling
	*/
	Dwelling* getDwelling(DwellingType dwellingType);
private:

    /*
    *   setupTiles
    *   Purpose:    Populates the board with tiles.
    */
    void setupTiles();
    /*
    *   placePlayers
    *   Purpose: Sets the players
    */
    void placePlayers();
    /*
    *   plopDwellings
    *   Purpose: place Dwellings
    */
    void plopDwellings();
    Board* gameBoard;
    Character* players[MAXPLAYERS];
    int day;
    TimeOfDay currentTime;
    bool cheatMode;
	Dwelling* dwellings[MAXDWELLINGS];
};

#endif // GAME_H