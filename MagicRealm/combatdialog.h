#ifndef COMBATDIALOG_H
#define COMBATDIALOG_H

#include <QDialog>
#include <QEvent>
#include "ui_combatdialog.h"
#include "shared.h"
#include "character.h"
#include "serverCommThread.h"

enum CombatState { ENCOUNTER, MELEE };

class CombatDialog : public QDialog
{
	Q_OBJECT

public:
	CombatDialog(Character* myChar, Character* enemyChar, QPixmap* myPix, QPixmap* enemyPix, CombatState state,
		ServerCommThread* serv, QWidget* parent = 0);
	~CombatDialog();

private slots:
	void on_submitButton_clicked();
	void on_moveCounterList_currentRowChanged(int row);
	void on_fightCounterList_currentRowChanged(int row);
	void on_blockTypeList_currentRowChanged(int row);

private:
	Ui::CombatDialog ui;
	Character* myCharacter;
	Character* enemyCharacter;
	ServerCommThread* server;
	CombatState combatState;
	int formsToFill[3];
	bool defaultMoveCounter;
	bool defaultFightCounter;
	bool defaultShieldType;

	void subEncounter(CharacterType character, bool run, int counter);
	void subMelee(CharacterType, int fightCounter, CombatFightType, int moveCounter, CombatMoveType, CombatShieldBlock);
};

#endif // COMBATDIALOG_H