#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

/*
 * Controller class for client (probably inappropriately titled)
 * Responsible for graphically representing game state
 */

#include "ui_mainwindow.h"

class GameWindow
{
public:
	GameWindow(Ui::MainWindowClass mainWindow);
	~GameWindow();

	errno_t initialize();
	errno_t cleanup();

private:
	Ui::MainWindowClass ui;
};

#endif // GAMEWINDOW_H