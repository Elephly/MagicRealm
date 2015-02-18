#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "shared.h"
#include <string>

class COMMONLIBRARY_EXPORT Serializer {
public:
	virtual ~Serializer() {};
	virtual string* serialize() = 0;
};

#endif // SERIALIZER_H