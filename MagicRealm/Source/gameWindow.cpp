#include "gameWindow.h"

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	server = new ServerCommThread(this);
}

GameWindow::~GameWindow()
{
	if (server != 0)
	{
		delete server;
		server = 0;
	}
}

errno_t GameWindow::initialize(QString &hostIP)
{
	errno_t err = 0;
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		return err;
	}

	return err;
}

errno_t GameWindow::cleanup()
{
	errno_t err = 0;

	err = server->threadDisconnect();

	return err;
}