#ifndef COUNTER_H
#define COUNTER_H

#include "shared.h"
#include "commonlibrary_global.h"


class COMMONLIBRARY_EXPORT Counter
{
public:
    Counter(CounterType counterType, char size, int speed, int fatigue);
	
	CounterType getType();
	char getSize();
	int getSpeed();
	int getFatigue();
	int getID();
	bool isAvailable();
	void wound();
	void heal();
	bool isResting();
	void setRest(bool rest);

private:
	static int currID;
	CounterType type;
	char size;
	int speed;
	int fatigue;
	int id;
	bool wounded;
	bool resting;
};

#endif //COUNTER_H