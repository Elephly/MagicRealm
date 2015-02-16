#ifndef SHARED_H
#define SHARED_H

using namespace std;

enum COMMONLIBRARY_EXPORT Direction {SOUTH=0, SOUTHWEST, NORTHWEST, NORTH, NORTHEAST, SOUTHEAST};

enum COMMONLIBRARY_EXPORT CharAdvantages
{
	AIM,
	REPUTATION,
	BARTER,
	CLEAVER,
	STAMINA,
	SHORTLEGS,
	CAVEKNOWLEGDE,
	ELUSIVNESS,
	ARCHER,
	FEAR
};

enum COMMONLIBRARY_EXPORT CharacterTypes
{
	Amazon,
	BlackKnight,
	Captain,
	Dwarf,
	Elf,
	Swordsman
};

#endif