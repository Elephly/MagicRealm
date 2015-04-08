#include "combatdialog.h"
#include <QDebug>
#include <QtNetwork>

CombatDialog::CombatDialog(Character* myChar, Character* enemyChar, QPixmap* myPix, QPixmap* enemyPix,
						   CombatState state, ServerCommThread* serv, QWidget* parentWindow)
{
	myCharacter = myChar;
	enemyCharacter = enemyChar;
	server = serv;
	combatState = state;

	ui.setupUi(this);
	ui.myCharacter->setPixmap(*myPix);
	ui.enemyCharacter->setPixmap(*enemyPix);

	if (combatState == ENCOUNTER)
	{
		ui.encounter_moveGroupBox->setEnabled(true);
		ui.encounter_moveGroupBox->setVisible(true);
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
		ui.encounter_runGroupBox->setEnabled(true);
		ui.encounter_runGroupBox->setVisible(true);
		ui.submitButton->setText("Submit Encounter Decisions");
	}
	else if (combatState == MELEE)
	{
		
		ui.submitButton->setText("Submit Melee Decisions");
	}
}


CombatDialog::~CombatDialog()
{
}

void CombatDialog::on_submitButton_clicked()
{
	if (combatState == ENCOUNTER)
	{
		subEncounter(myCharacter->getType(), ui.yesRun->isChecked(), ui.moveCounterList->currentItem()->data(Qt::UserRole).toInt());
	}
}

void CombatDialog::on_moveCounterList_currentRowChanged(int row)
{
	ui.submitButton->setEnabled(true);
}

void CombatDialog::subEncounter(CharacterType character, bool run, int counter)
{
	QString serializedCombat;
	serializedCombat.sprintf("SubEncounter%s%d%s%d%s%d", CLASSDELIM, (int)character, VARDELIM, (int)run, VARDELIM, counter);
	server->writeMessage(&serializedCombat);
	done(1);
}

void CombatDialog::subMelee(CharacterType character ,int, CombatFightType, int, CombatMoveType, CombatShieldBlock)
{
	QString serializedCombat;
	//serializedCombat.sprintf("SubMelee%s%d%s%d%s%d", CLASSDELIM, (int)character, VARDELIM, (int)run, VARDELIM, counter);
	server->writeMessage(&serializedCombat);
	done(1);
}