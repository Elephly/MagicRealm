#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

/*
 * Controller class for client (probably inappropriately titled)
 * Responsible for graphically representing game state
 */

#include <QMap>

#include "ui_mainwindow.h"
#include "serverCommThread.h"
#include "game.h"
#include "character.h"

//Forward decl
class ServerCommThread;

class GameWindow : public QObject
{
public:
	GameWindow(QObject* parent, Ui::MainWindowClass mainWindow);
	~GameWindow();

	errno_t initializeConnection(QString &hostIP);
	errno_t initializeGame(bool charcterRequestAccepted);
	errno_t cleanup();

	void changeScreenState(QWidget* screen);
	Character* getSelectedChar();
	void selectTile(Tile* tile);
	void updateTileInfoPane(Tile* tile);
	void selectAction(ActionType action);
	void move();

	static QMap<std::string, QPixmap> tileImages();
	void connectedToServer();
	void requestCharacter(CharacterTypes character);

private:
	Ui::MainWindowClass ui;
	QGraphicsScene* gameScene;
	ServerCommThread* server;
	
	Character* selectedCharacter;
	Game* game;
	Tile* selectedTile;
	ActionType selectedAction;
};

#endif // GAMEWINDOW_H