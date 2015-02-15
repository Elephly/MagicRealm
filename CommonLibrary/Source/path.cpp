#include "path.h"

Path::Path(Clearing *c1, Clearing *c2, bool isHidden){
	hidden = isHidden;
	clearing1 = c1;
	clearing2 = c2;
}