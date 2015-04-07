#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include "shared.h"
#include "character.h"
#include "counter.h"
#include "commonlibrary_global.h"


class COMMONLIBRARY_EXPORT CombatManager
{
public:
    CombatManager(Character* attacker, Character* defender);
	
	Character* getAttacker();
	Character* getDefender();
	CombatPhaseType getCurrentPhase();
	
	//returns true if attacker won, false if defender won step
	void runEncounter();
	Character* getPhaseWinner();
	bool EncounterVictorRun();
	void submitEncounter(Character* combatant, bool run,  Counter* counterUsed);
	void submitMelee(Character* combatant, Counter* fightCounter, CombatFightType fightType, Counter* moveCounter, CombatMoveType moveType);

private:
	Character* attacker;
	Character* defender;

	Counter* attackerMoveCounter;
	Counter* defenderMoveCounter;

	Counter* attackerFightCounter;
	Counter* defenderFightCounter;

	CombatFightType attackerFightType;
	CombatFightType defenderFightType;

	CombatMoveType attackerMoveType;
	CombatMoveType defenderMoveType;

	void setupFightCounter(Character* combatant, Counter* fCounter);
	void setupMoveCounter(Character* combatant, Counter* mCounter);


	bool stageWinAttacker;

	bool attackerFlee;
	bool defenderFlee;

	CombatPhaseType currentPhase;
};

#endif //COUNTER_H