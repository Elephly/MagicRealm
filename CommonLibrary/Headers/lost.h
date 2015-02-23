#ifndef LOST_H
#define LOST_H

#include "shared.h"
#include "commonlibrary_global.h"
#include "chit.h"

class COMMONLIBRARY_EXPORT Lost: public Chit{
public:
    Lost(string n, bool hide, vector<Chit* >* inside);
	virtual ChitType getType();
	virtual vector<Chit*>* getContents();
private:
	vector<Chit*> * contains;
};

#endif //SITE_H