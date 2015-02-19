#include "mainwindow.h"
#include "qapplication.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
	ui.statusBar->setSizeGripEnabled(false);
	ui.menuWidget->setVisible(true);
	ui.gameWidget->setVisible(false);

	gameWindow = new GameWindow(ui);
}

MainWindow::~MainWindow()
{
	delete gameWindow;
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
	QString hostIP = QInputDialog::getText(ui.centralWidget, "Connect to Host", "Please input the host IP address.");
	if (!hostIP.isEmpty())
	{
		if (gameWindow->initialize(hostIP))
		{
			QMessageBox::about(ui.centralWidget, "Error", "Failed to initialize game. Quitting.");
			return;
		}
		ui.menuWidget->setVisible(false);
		ui.gameWidget->setVisible(true);
	}
}

void MainWindow::on_menuQuitButton_clicked()
{
	QApplication::quit();
}

void MainWindow::on_gameQuitButton_clicked()
{
	if (gameWindow->cleanup())
	{
		QMessageBox::about(ui.centralWidget, "Hello World!", "Hi!");
	}
	ui.menuWidget->setVisible(true);
	ui.gameWidget->setVisible(false);
}