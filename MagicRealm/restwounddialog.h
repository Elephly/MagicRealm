#ifndef RESTWOUNDDIALOG_H
#define RESTWOUNDDIALOG_H

#include <QDialog>
#include "ui_restwounddialog.h"
#include "character.h"

enum RestWoundActionType { RESTWOUND_REST, RESTWOUND_WOUND };

class RestWoundDialog : public QDialog
{
	Q_OBJECT

public:
	RestWoundDialog(Character* character, QPixmap* myPix, RestWoundActionType actionType, QWidget *parent = 0);
	~RestWoundDialog();

	virtual int exec();

private slots:
	void on_submitButton_clicked();
	void on_counterList_currentRowChanged(int row);

private:
	Ui::RestWoundDialog ui;
	int formsToFill;
	bool defaultCounter;
	bool dead;
	Character* myCharacter;
};

#endif // RESTWOUNDDIALOG_H
