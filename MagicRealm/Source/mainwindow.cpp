#include "mainwindow.h"
#include "qapplication.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
	ui.statusBar->setSizeGripEnabled(false);
	ui.menuWidget->setVisible(true);
	ui.gameWidget->setVisible(false);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_menuPlayButton_clicked()
{
	ui.menuWidget->setVisible(false);
	ui.gameWidget->setVisible(true);
}

void MainWindow::on_menuQuitButton_clicked()
{
	QApplication::quit();
}

void MainWindow::on_gameQuitButton_clicked()
{
	ui.menuWidget->setVisible(true);
	ui.gameWidget->setVisible(false);
}