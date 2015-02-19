#include "gameWindow.h"
#include <Windows.h>

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	server = new ServerCommThread(this);
	selectedCharacter = 0;
}

GameWindow::~GameWindow()
{
	if (server != 0)
	{
		delete server;
		server = 0;
	}
}

errno_t GameWindow::initialize(QString &hostIP, int character)
{
	errno_t err = 0;

	selectedCharacter = new Character((CharacterTypes)character);

	changeScreenState(ui.loadingWidget);
	
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

	changeScreenState(ui.gameWidget);

	return err;
}

errno_t GameWindow::cleanup()
{
	errno_t err = 0;

	err = server->threadDisconnect();

	if (selectedCharacter != 0)
	{
		delete selectedCharacter;
		selectedCharacter = 0;
	}
	
	changeScreenState(ui.menuWidget);

	return err;
}


void GameWindow::changeScreenState(QWidget* screen)
{
	ui.menuWidget->setVisible(false);
	ui.loadingWidget->setVisible(false);
	ui.characterSelectWidget->setVisible(false);
	ui.gameWidget->setVisible(false);
	screen->setVisible(true);
	qApp->processEvents();
}