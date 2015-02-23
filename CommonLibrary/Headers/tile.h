#ifndef TILE_H
#define TILE_H

#include "clearing.h"
#include "shared.h"
#include <vector>
#include "path.h"
#include "serializer.h"
#include "chit.h"

class Board;

//Abstract class, extend this with all different tile types
class COMMONLIBRARY_EXPORT Tile : public Serializer {
public:
	Tile(Direction orient, string n, TileType type);
	Tile(string* serialString);
    ~Tile();

    /*
    *   getName()
    *   out:    The name of the Tile as a String
    */
    string getName();

    /*
    *   getAdjacentTiles
    *   out:   Tile Adjacent to that edge
    */
    Tile* getConnected(Direction edge);
    
    /*
    *   getOrientation
    *   out:    Direction enum of the orientation
    */
    Direction getOrientation();

    /*
    *   getClearing
    *   in: Id of the Clearing
    *   out: Pointer to the clearing
    */
    Clearing* getClearing(int id);
    /*
    *   addClearing
    *   in: new Clearing Pointer
    */
    void addClearing(Clearing* newClearing);

    /*
    *   addConnectedTile
    *   in:         Pointer of an adjacentTile
        in:         Edge that the path is on.
        Purpose:    Runs through current list of tiles and determines if exists, or if already full
    */
    void addConnectedTile(Tile* newTile, Direction edge);

    /*
    *   getEdge
    *   in:         Pointer to the tile that is on the connected list
        out:        Clearing that the path to the edge is connected to, null if nothing
    */
    Clearing* getConnectedClearing(Tile* aTile);

	void addWarningChit(Chit* newChit);
	void addSiteOrSoundChit(Chit* newChit);

	Chit* getWarningChit();
	Chit* getSiteOrSoundChit();

	TileType getType();

	virtual string* serialize();

private:
	vector<Clearing*>* clearings;

    //The offset of a rotated tile, the standard is EDGE_A(0), when the name of the tile is orientated correctly.
    Direction orientation;
    
    //helper to determine if something is connected
    Direction findConnectingEdge(Tile *aTile);

    //name of the string
    string name;

    Tile* connectedTiles [CONNECTED_LENGTH];

	TileType myType;

	Chit* warningChit;
	Chit* siteSoundChit;
};

#endif // TILE_H