#ifndef LOST_H
#define LOST_H

#include "shared.h"
#include "commonlibrary_global.h"
#include "chit.h"

class COMMONLIBRARY_EXPORT Lost: public Chit{
public:
    Lost(string n, bool hide, TileType myTileType);
	virtual ChitType getType();
	virtual vector<Chit*>* getContents();

	void populateCity(vector<Chit*>* inside);
private:
	vector<Chit*> * contains;
};

#endif //SITE_H