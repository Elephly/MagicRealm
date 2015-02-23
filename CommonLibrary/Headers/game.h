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
#include "chit.h"
#include "sound.h"
#include "warning.h"
#include "site.h"
#include "treasure.h"
#include "lost.h"

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
    bool addPlayer(CharacterType newPlayerType);
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
    void removePlayer(CharacterType oldPlayerType);

    /*
    *   getPlayer
    *   returns the player object playing that CharacterType
    */
    Character* getPlayer(CharacterType charType);

	Board* getBoard();
    /*
    *   MoveRequest
    *   In:     Pointer of the Character wishing to move
                Pointer of Clearing they wish to move to
    *   Out:    boolean whether move was successful or not
    */
    bool moveRequest(Character* player, Clearing* requestedClearing);
    /*
    *   hideRequest
    *   In:     Player Wishing to hide
    *   Out:    boolean whether hide was successful or not
    */
    bool hideRequest(Character* player);

	/*
	*	searchRequest, Locate or Loot table
	*	In:		Player attempting to search
	*			Type of search to perform
	*	Out:	
	*/
	void searchRequest(Character* player, SearchType type, Clearing* target);

	/*
	*	canLoot
	*	In:		Player that we are checking
	*	Out:	boolean whether player can loot their location or not
	*/
	bool canLoot(Character* player);

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

    /*
	*	rollDice
	*	Out:	Number you rolled.
	*/
	int rollDice();

private:
    enum siteType{
        HOARD,
        LAIR,
        ALTAR,
        SHRINE,
        POOL,
        VAULT,
        CAIRNS,
        STATUE
    };

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
    /*
    *   dealChits
    *   goes through and deals all the chits
    */
    void dealChits();
    /*
    *   setupSite
    *   sets up the sites and returns it
    *   helper for dealChits.
    */
    Site* setupSite(siteType sType, vector<Treasure*>* lg,  vector<Treasure*>* sm);

    Board* gameBoard;
    Character* players[MAXPLAYERS];
    int day;
    TimeOfDay currentTime;
    bool cheatMode;

    
};

#endif // GAME_H