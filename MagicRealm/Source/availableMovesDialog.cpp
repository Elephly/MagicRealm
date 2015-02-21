#include <QtGui>

#include "availableMovesDialog.h"


AvailableMovesDialog::AvailableMovesDialog(QWidget* parent)
{
	label = new QLabel("Available clearings");

	options = new QList<QRadioButton*>();

	moveButton = new QPushButton("Move");
	moveButton->setDefault(true);
	moveButton->setEnabled(false);

	cancelButton = new QPushButton("Cancel");

	connect(moveButton, SIGNAL(clicked()), this, SLOT(move()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

	buttonsLayout = new QHBoxLayout();
	buttonsLayout->addWidget(moveButton);
	buttonsLayout->addWidget(cancelButton);

	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addWidget(label);
	mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);

	setWindowTitle("Move");
}

void AvailableMovesDialog::addOption(QString text)
{
	QRadioButton* newOption = new QRadioButton(text);
	options->append(newOption);
	connect(newOption, SIGNAL(clicked()), this, SLOT(enableMoveButton()));
	QLayout* l = layout();
	l->removeItem(buttonsLayout);
	l->addWidget(newOption);
	l->addItem(buttonsLayout);
}

void AvailableMovesDialog::enableMoveButton()
{
	moveButton->setEnabled(true);
}

void AvailableMovesDialog::move()
{
	close();
}

void AvailableMovesDialog::cancel()
{
	close();
}