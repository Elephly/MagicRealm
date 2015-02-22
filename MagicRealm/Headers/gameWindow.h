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
	errno_t cleanup();

	void changeScreenState(QWidget* screen);
	CharacterType getSelectedChar();
	void selectTile(Tile* tile);
	void updateCharacterInfoPane();
	void updateTileInfoPane(Tile* tile);
	void updateCharacterLocation(Character* character);
	void selectAction(ActionType action);
	void moveAction();
	void moveTo(CharacterType character, QString& clearingString);

	void connectedToServer();
	void updateAvailableCharacters(int removeCharacter);
	void requestCharacter(CharacterType character, DwellingType startLoc);
	void characterRequestAcknowledged(bool accepted);
	void addCharacterToGame(QString &newCharacter);
	void doTurn(QString&);

private:
	bool gameStarted;
	QMap<CharacterType, QPixmap*>* characterImages;
	QMap<CharacterType, QGraphicsItem*>* characterGraphicsItems;
	QMap<std::string, QPixmap*>* tileImages;
	QMap<Tile*, QGraphicsItem*>* tileGraphicsItems;
	Ui::MainWindowClass ui;
	QGraphicsScene* gameScene;
	ServerCommThread* server;
	
	CharacterType selectedCharacter;
	DwellingType startLocation;
	Game* game;
	Tile* selectedTile;
	ActionType selectedAction;
	RecordedTurn *myTurn;
};

#endif // GAMEWINDOW_H