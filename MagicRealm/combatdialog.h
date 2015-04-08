#ifndef COMBATDIALOG_H
#define COMBATDIALOG_H

#include <QDialog>
#include <QEvent>
#include "ui_combatdialog.h"
#include "shared.h"
#include "character.h"
#include "serverCommThread.h"

class CombatDialog : public QDialog
{
	Q_OBJECT

public:
	CombatDialog(Character* myChar, Character* enemyChar, QPixmap* myPix, QPixmap* enemyPix, ServerCommThread* serv, QWidget* parent = 0);
	~CombatDialog();

private slots:
	void on_submitButton_clicked();
	void on_moveCounterList_currentRowChanged(int row);

private:
	Ui::CombatDialog ui;
	Character* myCharacter;
	Character* enemyCharacter;
	ServerCommThread* server;
	int state;

	void subEncounter(CharacterType character, bool run, int counter);
	void subMelee(CharacterType,int, CombatFightType, int, CombatMoveType, CombatShieldBlock);
};

#endif // COMBATDIALOG_H