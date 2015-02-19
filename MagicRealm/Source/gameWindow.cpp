#include "gameWindow.h"
#include <Windows.h>

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

	ui.menuWidget->setVisible(false);
	ui.loadingWidget->setVisible(true);
	qApp->processEvents();
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		return err;
	}

	int i = 0;
	while (!server->isConnected())
	{
		if (i++ >= 10)
		{
			ui.loadingWidget->setVisible(false);
			cleanup();
			return 1;
		}
		Sleep(1000);
	}
	
	ui.loadingWidget->setVisible(false);
	ui.gameWidget->setVisible(true);

	return err;
}

errno_t GameWindow::cleanup()
{
	errno_t err = 0;

	err = server->threadDisconnect();
	
	ui.menuWidget->setVisible(true);
	ui.gameWidget->setVisible(false);

	return err;
}