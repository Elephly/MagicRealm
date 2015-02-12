#include "mainwindow.h"
#include "qapplication.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
