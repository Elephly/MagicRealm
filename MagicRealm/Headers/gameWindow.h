#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

/*
 * Controller class for client (probably inappropriately titled)
 * Responsible for graphically representing game state
 */

#include <QEvent>
#include <QWheelEvent>
#include <QMap>

#include "ui_mainwindow.h"
#include "serverCommThread.h"
#include "game.h"
#include "character.h"
#include "tileGraphicsItem.h"

//Forward decl
class ServerCommThread;
class TileGraphicsItem;

class GameWindow : public QObject
{
public:
	GameWindow(QObject* parent, Ui::MainWindowClass mainWindow);
	~GameWindow();
	
	void loadCharacterImages();
	void loadTileImages();
	void loadDwellingImages();
	errno_t initializeConnection(QString &hostIP);
	errno_t initializeGame();
	errno_t initializeDestinationCounter();
	errno_t drawTiles();
	errno_t cleanup();

	int getXRelationalOffsetWithRotation(int x, int y, int rotation);
	int getYRelationalOffsetWithRotation(int x, int y, int rotation);

	void changeScreenState(QWidget* screen);
	void enableActions();
	void disableActions();
	CharacterType getSelectedChar();
	void selectTile(Tile* tile);
	void updateCharacterInfoPane();
	void updateTileInfoPane(Tile* tile);
	void updateCharacterLocation(Character* character);
	void placeCharacter(Character* character, Tile* tile, Clearing* clearing);
	void placeDestinationCounter();
	void placeDwelling(Dwelling* dwelling);
	void selectAction(ActionType action);
	bool moveAction();
	void moveTo(CharacterType character, QString& clearingString);
	void setCharacterHidden(CharacterType character, bool hidden);
	void searchTypeRequest(QString& searchTypes);
	void search(CharacterType character, SearchType searchType);
	void treasureFound(CharacterType character, int treasureWorth);
	void siteFound(CharacterType character, QString& siteName);

	void connectedToServer(time_t);
	void updateAvailableCharacters(int removeCharacter);
	void requestCharacter(CharacterType character, DwellingType startLoc);
	void characterRequestAcknowledged(bool accepted);
	void addCharacterToGame(QString &newCharacter);
	void doTurn(QString&);
	void submitTurn();
	void setCurrentPhaseType(const QString& phaseString);
	void caveCheck();
	int countMovingPhases();
	bool isMovingPhase(int phaseIndex);
	void payForMountainClimb();
	void setupChit(QString& chitString);

protected:
	bool eventFilter(QObject *, QEvent *);

private:
	bool gameStarted;
	QPixmap* destinationCounterImage;
	QGraphicsPixmapItem* destinationCounter;
	double counterDepth;
	double characterImageScale;
	QMap<CharacterType, QPixmap*>* characterImages;
	QMap<CharacterType, QGraphicsPixmapItem*>* characterGraphicsItems;
	QMap<std::string, QPixmap*>* tileImages;
	QMap<std::string, QList<QPoint*>*>* tileClearingOffsets;
	QMap<Tile*, TileGraphicsItem*>* tileGraphicsItems;
	QMap<Tile*, QPointF>* tileLocations;
	double dwellingImageScale;
	QMap<DwellingType, QPixmap*>* dwellingImages;
	QMap<DwellingType, QGraphicsPixmapItem*>* dwellingGraphicsItems;
	QMainWindow* window;
	Ui::MainWindowClass ui;
	QGraphicsScene* gameScene;
	ServerCommThread* server;
	
	CharacterType selectedCharacter;
	DwellingType startLocation;
	Game* game;
	Tile* selectedTile;
	Clearing* destinationClearing;
	ActionType selectedAction;
	RecordedTurn *myTurn;
	int turnNumber;
	PhaseType currentPhase;
	int sunlightPhases;
};

#endif // GAMEWINDOW_H