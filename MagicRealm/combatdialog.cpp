#include "combatdialog.h"
#include <QDebug>
#include <QtNetwork>

CombatDialog::CombatDialog(Character* myChar, Character* enemyChar, QPixmap* myPix, QPixmap* enemyPix, ServerCommThread* serv, QWidget* parentWindow)
{
	myCharacter = myChar;
	enemyCharacter = enemyChar;
	server = serv;
	state = 1;

	ui.setupUi(this);
	ui.myCharacter->setPixmap(*myPix);
	ui.enemyCharacter->setPixmap(*enemyPix);
	ui.submitButton->setText("Submit Encounter Decisions");

	vector<Counter*>* counters = myCharacter->getCounters();
	for (vector<Counter*>::iterator it = counters->begin(); it != counters->end(); ++it)
	{
		if ((*it)->getType() == COUNTER_MOVE && (*it)->isAvailable())
		{
			QString cntr;
			cntr.sprintf("%c%d", (*it)->getSize(), (*it)->getSpeed());
			for (int i = 0; i < (*it)->getFatigue(); i++)
			{
				cntr.append("*");
			}
			QListWidgetItem* item = new QListWidgetItem(cntr);
			item->setData(Qt::UserRole, (*it)->getID());
			ui.moveCounterList->addItem(item);
		}
	}
}


CombatDialog::~CombatDialog()
{
}

void CombatDialog::on_submitButton_clicked()
{
	if (state == 1)
	{
		subEncounter(myCharacter->getType(), ui.yesRun->isChecked(), ui.moveCounterList->currentItem()->data(Qt::UserRole).toInt());
		state++;
	}
}

void CombatDialog::on_moveCounterList_currentRowChanged(int row)
{
	ui.submitButton->setEnabled(true);
}

void CombatDialog::subEncounter(CharacterType character, bool run, int counter)
{
	ui.submitButton->setEnabled(false);
	QString serializedCombat;
	serializedCombat.sprintf("SubEncounter%s%d%s%d%s%d", CLASSDELIM, (int)character, VARDELIM, (int)run, VARDELIM, counter);
	server->writeMessage(&serializedCombat);
}

void CombatDialog::subMelee(CharacterType,int, CombatFightType, int, CombatMoveType, CombatShieldBlock)
{

}