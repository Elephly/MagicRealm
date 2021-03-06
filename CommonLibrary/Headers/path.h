#ifndef PATH_H
#define PATH_H

#include "commonlibrary_global.h"
#include "shared.h"
#include "clearing.h"
#include "serializer.h"

//forward declare
class Clearing;


class COMMONLIBRARY_EXPORT Path : public Serializer{
public:
	Path(Clearing *c1, Clearing *c2, PathType myType);
	//used for normal paths
	Path(Clearing *c1, Clearing *c2);
	Path(string* serialString);

    //for a path that leaves a tile (connects two tiles)]
    //DEPRECIATED
    Path(Clearing *c1, Direction d);
    ~Path();
    /*
    *   getBothEndPoints
    *   In/Out: 2 Clearing pointers(initially should be null) 
                Will point these pointers to the clearings at each end of the path
    */
    void getBothEndPoints(Clearing* c1, Clearing* c2);

    /*
    *   getEnd
    *   In: The StartPoint of the path as a clearing pointer
    *   Out:    The Clearing (pointer) at the other end of the path.
    */
    Clearing* getEnd(Clearing* startPoint);

    /*
    *   isHidden()
    *   out:    path is hidden or not (secret passageway / hidden path)
    */
    PathType getType();

    /*
    *   isBorder
    *   out: path is border or not.
    */
    bool isBorder();

    /*
    *   borderingSide()
    *   out: the Side that it is bordering as a Direction
    */
    Direction borderingSide();

	virtual string* serialize();

private:
	PathType myType;
    bool border;
	Clearing *clearing1;
	Clearing *clearing2;
    Direction bordering;
};

#endif // PATH_H