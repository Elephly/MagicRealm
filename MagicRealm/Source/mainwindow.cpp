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
	//this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
	ui.statusBar->setSizeGripEnabled(false);

	gameWindow = new GameWindow(this, ui);

	gameWindow->changeScreenState(ui.menuWidget);
}

MainWindow::~MainWindow()
{
	delete gameWindow;
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
	gameWindow->changeScreenState(ui.characterSelectWidget);
}

void MainWindow::on_menuQuitButton_clicked()
{
	QApplication::quit();
}

void MainWindow::on_characterSelectButton_clicked()
{
	QString hostIP = QInputDialog::getText(ui.centralWidget, "Connect to Host", "Please input the host IP address.");
	if (!hostIP.isEmpty())
	{
		if (gameWindow->initialize(hostIP, ui.characterListView->currentRow()))
		{
			QMessageBox::about(ui.centralWidget, "Error", "Failed to initialize game.");
			return;
		}
	}
}

void MainWindow::on_characterQuitButton_clicked()
{
	gameWindow->changeScreenState(ui.menuWidget);
}

void MainWindow::on_characterListView_currentRowChanged(int row)
{
	ui.characterDetailView->setPixmap(QPixmap(characterDetailPaths[row]));
}

void MainWindow::on_gameMoveActionButton_clicked()
{

}

void MainWindow::on_gameSearchActionButton_clicked()
{

}

void MainWindow::on_gameTradeActionButton_clicked()
{

}

void MainWindow::on_gameHideActionButton_clicked()
{

}

void MainWindow::on_gamePeerActionButton_clicked()
{

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