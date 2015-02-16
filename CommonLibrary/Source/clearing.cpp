#include "clearing.h"

Clearing::Clearing(int clNum, Tile* parentTile) {
	ID= clNum;
    myTile = parentTile;
}

void Clearing::addCharacterToClearing(Character* player)
{
    //checking to see if the player is already in this clearing.
    for(vector<Character*>::iterator it = characters.begin(); it != characters.end(); ++it){
        if(*it == player){
            cout << "WARN: character already registered in clearing, not registering character" <<endl;
            return;
        }
    }
    characters.push_back(player);
}

void Clearing::chartPath(Path* newPath)
{
    //checking to see if the player is already in this clearing.
    for(vector<Path*>::iterator it = pathways.begin(); it != pathways.end(); ++it){
        if(*it == newPath){
            cout << "WARN: path already registered in clearing, not registering path" <<endl;
            return;
        }
    }
    pathways.push_back(newPath);
}