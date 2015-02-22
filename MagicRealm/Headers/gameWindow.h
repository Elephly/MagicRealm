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
	
	void loadCharacterImages();
	void loadTileImages();
	errno_t initializeConnection(QString &hostIP);
	errno_t initializeGame();
	errno_t initializePlayers();
	errno_t drawTiles();
	errno_t drawPlayers();
	errno_t cleanup();

	void changeScreenState(QWidget* screen);
	CharacterTypes getSelectedChar();
	void selectTile(Tile* tile);
	void updateTileInfoPane(Tile* tile);
	void updateCharacterLocation(Character* character);
	void selectAction(ActionType action);
	void move();

	void connectedToServer();
	void updateAvailableCharacters(int removeCharacter);
	void requestCharacter(CharacterTypes character, DwellingType startLoc);
	void characterRequestAcknowledged(bool accepted);
	void addCharacterToGame(QString &newCharacter);
	void doTurn(QString&);

private:
	QMap<CharacterTypes, QPixmap*>* characterImages;
	QMap<CharacterTypes, QGraphicsItem*>* characterGraphicsItems;
	QMap<std::string, QPixmap*>* tileImages;
	QMap<Tile*, QGraphicsItem*>* tileGraphicsItems;
	Ui::MainWindowClass ui;
	QGraphicsScene* gameScene;
	ServerCommThread* server;
	
	CharacterTypes selectedCharacter;
	DwellingType startLocation;
	Game* game;
	Tile* selectedTile;
	ActionType selectedAction;
	RecordedTurn *myTurn;
};

#endif // GAMEWINDOW_H