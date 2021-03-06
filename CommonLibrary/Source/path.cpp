#include "path.h"
#include <sstream>


Path::Path(Clearing *c1, Clearing *c2, PathType pt){
	myType = pt;
    border = false;
	clearing1 = c1;
	clearing2 = c2;
    bordering = EDGE_NONE;
    clearing1->addPath(this);
    clearing2->addPath(this);
}

Path::Path(Clearing *c1, Clearing *c2){
	myType = NORMAL;
    border = false;
	clearing1 = c1;
	clearing2 = c2;
    bordering = EDGE_NONE;
    clearing1->addPath(this);
    clearing2->addPath(this);
}

//for a path that leaves a tile. DEPRECIATED
Path::Path(Clearing* c1, Direction dir)
{
    //border paths cannot be secret passages or hidden paths
    myType = NORMAL;
    border = true;
    clearing1 = c1;
    clearing2 = NULL;
    bordering = dir;
    clearing1->addPath(this);
}

Path::Path(string* serialString) {
	//TODO implement deserializer
}

Path::~Path()
{
    cout << "Destructor called for Path" << endl;
    if(clearing1)
        clearing1->removePath(this);
    if(clearing2)
        clearing2->removePath(this);

}

void Path::getBothEndPoints(Clearing* c1, Clearing* c2)
{
    if(c1 == NULL || c2 == NULL)
        cout << "WARN: getBothEndPoints(c1, c2) c1 || c2 not Null, overwriting pointer" << endl; 
    c1 = clearing1;
    c2 = clearing2;
}

Clearing* Path::getEnd(Clearing* startPoint)
{
     return startPoint == clearing1 ? clearing2 : clearing1;
}

PathType Path::getType()
{
    return myType;
}

bool Path::isBorder()
{
    return border;
}

Direction Path::borderingSide()
{
    return bordering;
}

string* Path::serialize() {
	stringstream s;
	s << "Path";
	s << CLASSDELIM;
	s << *(clearing1->toString());
	s << VARDELIM;
	s << *(clearing2->toString());
	s << VARDELIM;
	s << myType;

	return new string(s.str());
}