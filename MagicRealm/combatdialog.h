#ifndef COMBATDIALOG_H
#define COMBATDIALOG_H

#include <QDialog>
#include "ui_combatdialog.h"
#include "shared.h"
#include "character.h"

class CombatDialog
{
public:
	CombatDialog(Character* myChar, Character* enemyChar, QPixmap* myPix, QPixmap* enemyPix, QWidget* parent = 0);
	~CombatDialog();

private:
	Ui::CombatDialog ui;
	Character* myCharacter;
	Character* enemyCharacter;
};

#endif // COMBATDIALOG_H