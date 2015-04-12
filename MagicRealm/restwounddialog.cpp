#include "restwounddialog.h"

RestWoundDialog::RestWoundDialog(Character* character, QPixmap* myPix, RestWoundActionType actionType, QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
	formsToFill = 1;
	defaultCounter = false;
	dead = false;
	myCharacter = character;

	ui.myCharacter->setPixmap(*myPix);
	vector<Counter*>* counters = myCharacter->getCounters();
	if (actionType == RESTWOUND_REST)
	{
		setWindowTitle("Rest up!");
		ui.counterGroupBox->setTitle("Select a counter to heal");
		for (vector<Counter*>::iterator it = counters->begin(); it != counters->end(); ++it)
		{
			if (!(*it)->isAvailable())
			{
				formsToFill = 0;
				ui.submitButton->setEnabled(false);
				QString cntr;
				if ((*it)->getType() == COUNTER_FIGHT)
				{
					cntr.sprintf("Fight: %c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				else if ((*it)->getType() == COUNTER_MOVE)
				{
					cntr.sprintf("Move: %c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				else if ((*it)->getType() == COUNTER_DUCK)
				{
					cntr.sprintf("Duck:%c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				else
				{
					cntr.sprintf("%c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				for (int i = 0; i < (*it)->getFatigue(); i++)
				{
					cntr.append("*");
				}
				QListWidgetItem* item = new QListWidgetItem(cntr);
				item->setData(Qt::UserRole, (*it)->getID());
				ui.counterList->addItem(item);
			}
		}
		if (formsToFill == 1)
		{
			defaultCounter = true;
			ui.counterGroupBox->setTitle("No counters to heal");
		}
		ui.submitButton->setText("Heal");
	}
	else if (actionType == RESTWOUND_WOUND)
	{
		setWindowTitle("You have taken damage!");
		ui.counterGroupBox->setTitle("Select a counter to wound");
		for (vector<Counter*>::iterator it = counters->begin(); it != counters->end(); ++it)
		{
			if ((*it)->isAvailable())
			{
				formsToFill = 0;
				ui.submitButton->setEnabled(false);
				QString cntr;
				if ((*it)->getType() == COUNTER_FIGHT)
				{
					cntr.sprintf("Fight: %c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				else if ((*it)->getType() == COUNTER_MOVE)
				{
					cntr.sprintf("Move: %c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				else if ((*it)->getType() == COUNTER_DUCK)
				{
					cntr.sprintf("Duck:%c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				else
				{
					cntr.sprintf("%c%d", (*it)->getSize(), (*it)->getSpeed());
				}
				for (int i = 0; i < (*it)->getFatigue(); i++)
				{
					cntr.append("*");
				}
				QListWidgetItem* item = new QListWidgetItem(cntr);
				item->setData(Qt::UserRole, (*it)->getID());
				ui.counterList->addItem(item);
			}
		}
		if (formsToFill == 1)
		{
			dead = true;
			ui.counterGroupBox->setTitle("No counters to wound");
		}
		ui.submitButton->setText("Wound");
	}
}

RestWoundDialog::~RestWoundDialog()
{

}

void RestWoundDialog::on_submitButton_clicked()
{
	int counter;
	if (defaultCounter) counter = -1;
	else counter = ui.counterList->currentItem()->data(Qt::UserRole).toInt();
	
	vector<Counter*>* counters = myCharacter->getCounters();
	for (vector<Counter*>::iterator it = counters->begin(); it != counters->end(); ++it)
	{
		if ((*it)->getID() == counter)
		{
			(*it)->wound();
		}
	}

	done(counter);
}

void RestWoundDialog::on_counterList_currentRowChanged(int row)
{
	ui.submitButton->setEnabled(true);
}

int RestWoundDialog::exec()
{
	if (dead)
	{
		return -2;
	}
	return QDialog::exec();
}