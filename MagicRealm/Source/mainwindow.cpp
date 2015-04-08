#include "mainwindow.h"
#include "qapplication.h"
#include <QMessageBox>
#include <QInputDialog>

QString MainWindow::characterDetailPaths[] = { ":/images/characterdetail/amazon.jpg",
												":/images/characterdetail/black_knight.jpg",
												":/images/characterdetail/captain.jpg",
												":/images/characterdetail/dwarf.jpg",
												":/images/characterdetail/elf.jpg",
												":/images/characterdetail/swordsman.jpg" };

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
	ui.statusBar->setSizeGripEnabled(false);

	gameWindow = new GameWindow(this, ui);

	gameWindow->changeScreenState(ui.menuWidget);
	gameWindow->disableActions();
	QLineEdit* lineEdit = new QLineEdit();
	lineEdit->setPlaceholderText("No Phases");
	lineEdit->setReadOnly(true);
	ui.gamePhaseComboBox->setLineEdit(lineEdit);
}

MainWindow::~MainWindow()
{
	delete gameWindow;
}

void MainWindow::resetActionStyles()
{
	ui.gameMoveActionButton->setStyleSheet("");
	ui.gameSearchActionButton->setStyleSheet("");
	ui.gameTradeActionButton->setStyleSheet("");
	ui.gameHideActionButton->setStyleSheet("");
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);
	
	QRect geo = ui.centralWidget->geometry();

	// Dont know WHY this bit is necessary...but it is.
	// Without it, the bottom gets chopped off.
	int h = geo.height();
	geo.setY(0);
	geo.setHeight(h);
	///////////////////////////////////////////////////

	ui.menuWidget->setGeometry(geo);
	ui.loadingWidget->setGeometry(geo);
	ui.characterSelectWidget->setGeometry(geo);
	ui.gameWidget->setGeometry(geo);
}

void MainWindow::on_actionExit_triggered()
{
	if (QMessageBox::question(ui.centralWidget, "Are you sure?", "Do you really want to quit?") == QMessageBox::Yes)
	{
		gameWindow->cleanup();
		QApplication::quit();
	}
}

void MainWindow::on_menuPlayButton_clicked()
{
	/*
	 * I'd like to briefly boast about my commenting expertise.
	 * What follows this block comment is another strategically placed, ease of use
	 * comment designed for "one-click simplicity", if you will...
	 * Below, you will see two blocks of code which I wish to frequently alternate
	 * in terms of comment state. I've designed the comments such that all that's
	 * necessary the comment out the first block and uncomment the second block
	 * (like a toggle) is to remove the very first forward slash at the beginning
	 * of the comment. Likewise, put that forward slash back if you wish to flip it
	 * back.
	 * It's simply magnificent isn't it? Truly innovative. This alone should give me
	 * 100% on my portion of the assignment. And with that, I leave you. Enjoy.
	 */
	//*
	QString hostIP = QInputDialog::getText(ui.centralWidget, "Connect to Host", "Please input the host IP address.");
	if (!hostIP.isEmpty())
	{
		if (gameWindow->initializeConnection(hostIP))
		{
			QMessageBox::about(ui.centralWidget, "Error", "Failed to connect to host.");
			return;
		}
	}
	/*/
	// FOR TESTING!!!
	if (gameWindow->initializeConnection(QString("localhost")))
	{
		QMessageBox::about(ui.centralWidget, "Error", "Failed to connect to host.");
		return;
	}
	/*
	*/
}

void MainWindow::on_menuQuitButton_clicked()
{
	QApplication::quit();
}

void MainWindow::on_characterSelectButton_clicked()
{
	DwellingType startLoc;
	if (ui.characterStartLocationListView->currentItem()->text() == Dwelling::getTypeString(CHAPEL))
	{
		startLoc = CHAPEL;
	}
	else if (ui.characterStartLocationListView->currentItem()->text() == Dwelling::getTypeString(GUARD))
	{
		startLoc = GUARD;
	}
	else if (ui.characterStartLocationListView->currentItem()->text() == Dwelling::getTypeString(HOUSE))
	{
		startLoc = HOUSE;
	}
	else if (ui.characterStartLocationListView->currentItem()->text() == Dwelling::getTypeString(INN))
	{
		startLoc = INN;
	}
	gameWindow->requestCharacter((CharacterType)ui.characterListView->currentRow(), startLoc);
}

void MainWindow::on_characterQuitButton_clicked()
{
	gameWindow->changeScreenState(ui.menuWidget);
}

void MainWindow::on_characterListView_currentRowChanged(int row)
{
	ui.characterDetailView->setPixmap(QPixmap(characterDetailPaths[row]));
	ui.characterStartLocationListView->clear();
	vector<DwellingType>* startLocations = Character::getStartLocations((CharacterType)row);
	for (vector<DwellingType>::iterator it = startLocations->begin(); it != startLocations->end(); ++it)
	{
		DwellingType dwelling = *it;
		ui.characterStartLocationListView->addItem(Dwelling::getTypeString(dwelling));
	}
	ui.characterStartLocationListView->setCurrentRow(0);
	delete startLocations;
}

void MainWindow::on_gameMoveActionButton_clicked()
{
	ui.gameMoveActionButton->setStyleSheet("background-color: rgb(250, 255, 187);");
	gameWindow->selectAction(MoveAction);
	ui.gameMoveActionButton->setStyleSheet("");
}

void MainWindow::on_gameSearchActionButton_clicked()
{
	resetActionStyles();
	ui.gameSearchActionButton->setStyleSheet("background-color: rgb(250, 255, 187);");
	gameWindow->selectAction(SearchAction);
	ui.gameSearchActionButton->setStyleSheet("");
}

void MainWindow::on_gameTradeActionButton_clicked()
{
	resetActionStyles();
	ui.gameTradeActionButton->setStyleSheet("background-color: rgb(250, 255, 187);");
	gameWindow->selectAction(TradeAction);
	ui.gameTradeActionButton->setStyleSheet("");
}

void MainWindow::on_gameHideActionButton_clicked()
{
	resetActionStyles();
	ui.gameHideActionButton->setStyleSheet("background-color: rgb(250, 255, 187);");
	gameWindow->selectAction(HideAction);
	ui.gameHideActionButton->setStyleSheet("");
}

void MainWindow::on_gameRestActionButton_clicked()
{
	resetActionStyles();
	ui.gameRestActionButton->setStyleSheet("background-color:rgb(250, 255, 187);");
	gameWindow->selectAction(RestAction);
	ui.gameRestActionButton->setStyleSheet("");
}

void MainWindow::on_gameSubmitTurnButton_clicked()
{
	gameWindow->submitTurn();
}

void MainWindow::on_gameQuitButton_clicked()
{
	if (QMessageBox::question(ui.centralWidget, "Are you sure?", "Do you really want to quit?") == QMessageBox::Yes)
	{
		if (gameWindow->cleanup())
		{
			QMessageBox::about(ui.centralWidget, "Error", "Failed to cleanup game.");
		}
	}
}

void MainWindow::on_gamePhaseComboBox_currentIndexChanged(const QString& text)
{
	gameWindow->setCurrentPhaseType(text);
}