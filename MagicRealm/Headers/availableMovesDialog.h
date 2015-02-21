#ifndef AVAILABLEMOVESDIALOG_H
#define AVAILABLEMOVESDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class AvailableMovesDialog : public QDialog
{
	Q_OBJECT

public:
	AvailableMovesDialog(QWidget* parent = 0);
	void addOption(QString text);

private slots:
	void enableMoveButton();
	void move();
	void cancel();

private:
	QLabel* label;
	QList<QRadioButton*>* options;
	QPushButton* moveButton;
	QPushButton* cancelButton;
	QHBoxLayout* buttonsLayout;
};

#endif // AVAILABLEMOVESDIALOG_H