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

	ui.moveGroupBox->setEnabled(true);
	ui.moveGroupBox->setVisible(true);
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

	if (combatState == ENCOUNTER)
	{
		ui.encounter_runGroupBox->setEnabled(true);
		ui.encounter_runGroupBox->setVisible(true);
		ui.submitButton->setText("Submit Encounter Decisions");

		ui.melee_fightGroupBox->setEnabled(false);
		ui.melee_fightGroupBox->setVisible(false);
	}
	else if (combatState == MELEE)
	{
		QRect geo = ui.moveGroupBox->geometry();
		ui.moveGroupBox->setGeometry(50, geo.y(), geo.width(), geo.height());
		ui.melee_fightGroupBox->setEnabled(true);
		ui.melee_fightGroupBox->setVisible(true);
		ui.submitButton->setText("Submit Melee Decisions");
		
		ui.encounter_runGroupBox->setEnabled(false);
		ui.encounter_runGroupBox->setVisible(false);
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