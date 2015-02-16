#ifndef PATH_H
#define PATH_H

#include "commonlibrary_global.h"
#include "shared.h"
#include "clearing.h"

//forward declare
class Clearing;


class COMMONLIBRARY_EXPORT Path {
public:
	Path(Clearing *c1, Clearing *c2, bool isHidden);
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
    bool isHidden();

private:
	bool hidden;
	Clearing *clearing1;
	Clearing *clearing2;
};

#endif // PATH_H