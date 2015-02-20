#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

/*
 * Controller class for client (probably inappropriately titled)
 * Responsible for graphically representing game state
 */

#include <QMap>

#include "ui_mainwindow.h"
#include "serverCommThread.h"
#include "character.h"

//Forward decl
class ServerCommThread;

class GameWindow : public QObject
{
public:
	GameWindow(QObject* parent, Ui::MainWindowClass mainWindow);
	~GameWindow();

	errno_t initialize(QString &hostIP, int character);
	errno_t cleanup();

	void changeScreenState(QWidget* screen);
	Character* getSelectedChar();
	void selectTile(Tile* tile);
	void updateTileInfoPane(Tile* tile);
	void selectAction(ActionType action);

	static QMap<std::string, QPixmap> tileImages();

private:
	Ui::MainWindowClass ui;
	QGraphicsScene* gameScene;
	ServerCommThread* server;
	Character* selectedCharacter;
	Tile* selectedTile;
	ActionType selectedAction;
};

#endif // GAMEWINDOW_H