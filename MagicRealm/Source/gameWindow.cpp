#include "gameWindow.h"

GameWindow::GameWindow(Ui::MainWindowClass mainWindow)
	: ui(mainWindow)
{

}

GameWindow::~GameWindow()
{

}

errno_t GameWindow::initialize(QString &hostIP)
{
	errno_t ret = 0;
	
	server = new ServerCommThread(hostIP, GAMEPORT, this);

	return ret;
}

errno_t GameWindow::cleanup()
{
	errno_t ret = 0;

	delete server;
	server = 0;

	return ret;
}