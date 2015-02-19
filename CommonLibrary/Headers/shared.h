#ifndef SHARED_H
#define SHARED_H

#define GAMEPORT 42730
#define ADJACENT_LENGTH 6
#define DECLINECONN "connection declined"
#define ACCEPTCONN "connection accepted"

#define CLASSDELIM "**"
#define VARDELIM "^"
#define LISTDELIM "+"

#include <iostream>
#include <string>
#include "commonlibrary_global.h"

using namespace std;

enum COMMONLIBRARY_EXPORT Direction {EDGE_NONE =-1, EDGE_A=0, EDGE_B, EDGE_C, EDGE_D, EDGE_E, EDGE_F};

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

enum COMMONLIBRARY_EXPORT ArmorType
{
	Helmet,
	Breastplate,
	Shield,
	Suit
};

enum COMMONLIBRARY_EXPORT WeaponType
{
	MediumBow,
	LightBow,
	CrossBow,
	Spear,
	Staff,
	GreatSword,
	BroadSword,
	MorningStar,
	GreatAxe,
	ThrustingSword,
	ShortSword,
	Axe,
	Mace
};

enum COMMONLIBRARY_EXPORT AttackType
{
	Missile,
	Striking
};

enum COMMONLIBRARY_EXPORT ActionType
{
	MoveAction,
	SearchAction,
	TradeAction,
	HideAction,
	PeerAction
};

enum COMMONLIBRARY_EXPORT PhaseType
{
	MovePhase,
	BasicPhase,
	SunlightPhase
};
#endif