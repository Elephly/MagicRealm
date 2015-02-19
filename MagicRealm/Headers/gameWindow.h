#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

/*
 * Controller class for client (probably inappropriately titled)
 * Responsible for graphically representing game state
 */

#include "ui_mainwindow.h"
#include "serverCommThread.h"

class GameWindow : public QObject
{
public:
	GameWindow(Ui::MainWindowClass mainWindow);
	~GameWindow();

	errno_t initialize(QString &hostIP);
	errno_t cleanup();

private:
	Ui::MainWindowClass ui;
	ServerCommThread* server;
};

#endif // GAMEWINDOW_H