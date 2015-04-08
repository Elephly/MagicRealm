#include "combatdialog.h"
#include <QDebug>

CombatDialog::CombatDialog(Character* myChar, Character* enemyChar, QPixmap* myPix, QPixmap* enemyPix, QWidget* parentWindow)
{
	myCharacter = myChar;
	enemyCharacter = enemyChar;

	QDialog* dialog = new QDialog(parentWindow);
	Ui::CombatDialog* combatDialog = new Ui::CombatDialog();
	combatDialog->setupUi(dialog);
	combatDialog->myCharacter->setPixmap(*myPix);
	combatDialog->enemyCharacter->setPixmap(*enemyPix);
	combatDialog->submitButton->setText("Select move chit");
	vector<Counter*>* counters = myCharacter->getCounters();
	for (vector<Counter*>::iterator it = counters->begin(); it != counters->end(); ++it)
	{
		if ((*it)->getType() == COUNTER_MOVE)
		{
			
		}
	}
	dialog->exec();
}


CombatDialog::~CombatDialog()
{
}
void subEncounter(CharacterType character, bool run, int counter);
void subMelee(CharacterType,int, CombatFightType, int, CombatMoveType, CombatShieldBlock);