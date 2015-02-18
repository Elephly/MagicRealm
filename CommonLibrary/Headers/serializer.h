#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "shared.h"
#include "action.h"
#include "recordedTurn.h"
#include <string>

string* COMMONLIBRARY_EXPORT serialzeAction(Action*);
Action* COMMONLIBRARY_EXPORT deserializeAction(string*);

string* COMMONLIBRARY_EXPORT serializeTurn(RecordedTurn*);
RecordedTurn* COMMONLIBRARY_EXPORT deserializeTurn(string*);

#endif // SERIALIZER_H