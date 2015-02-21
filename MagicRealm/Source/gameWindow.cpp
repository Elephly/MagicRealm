#include "gameWindow.h"

#include "tileGraphicsItem.h"
#include "availableMovesDialog.h"

#include <QMessageBox>

#include <queue>
#include <unordered_set>

#include <Windows.h>

QMap<std::string, QPixmap> GameWindow::tileImages()
{
	QMap<std::string, QPixmap> map;
	map.insert("Awful Valley", QPixmap(":/images/tiles/awfulvalley1.gif"));
	map.insert("Awful Valley Enchanted", QPixmap(":/images/tiles/awfulvalley-e1.gif"));
	map.insert("Bad Valley", QPixmap(":/images/tiles/badvalley1.gif"));
	map.insert("Bad Valley Echanted", QPixmap(":/images/tiles/badvalley-e1.gif"));
	map.insert("Border Land", QPixmap(":/images/tiles/borderland1.gif"));
	map.insert("Border Land Echanted", QPixmap(":/images/tiles/borderland-e1.gif"));
	map.insert("Cavern", QPixmap(":/images/tiles/cavern1.gif"));
	map.insert("Cavern Echanted", QPixmap(":/images/tiles/cavern-e1.gif"));
	map.insert("Caves", QPixmap(":/images/tiles/caves1.gif"));
	map.insert("Caves Echanted", QPixmap(":/images/tiles/caves-e1.gif"));
	map.insert("Cliff", QPixmap(":/images/tiles/cliff1.gif"));
	map.insert("Cliff Echanted", QPixmap(":/images/tiles/cliff-e1.gif"));
	map.insert("Crag", QPixmap(":/images/tiles/crag1.gif"));
	map.insert("Crag Echanted", QPixmap(":/images/tiles/crag-e1.gif"));
	map.insert("Curst Valley", QPixmap(":/images/tiles/curstvalley1.gif"));
	map.insert("Curst Valley Echanted", QPixmap(":/images/tiles/curstvalley-e1.gif"));
	map.insert("Dark Valley", QPixmap(":/images/tiles/darkvalley1.gif"));
	map.insert("Dark Valley Echanted", QPixmap(":/images/tiles/darkvalley-e1.gif"));
	map.insert("Deep Woods", QPixmap(":/images/tiles/deepwoods1.gif"));
	map.insert("Deep Woods Echanted", QPixmap(":/images/tiles/deepwoods-e1.gif"));
	map.insert("Evil Valley", QPixmap(":/images/tiles/evilvalley1.gif"));
	map.insert("Evil Valley Echanted", QPixmap(":/images/tiles/evilvalley-e1.gif"));
	map.insert("High Pass", QPixmap(":/images/tiles/highpass1.gif"));
	map.insert("High Pass Echanted", QPixmap(":/images/tiles/highpass-e1.gif"));
	map.insert("Ledges", QPixmap(":/images/tiles/ledges1.gif"));
	map.insert("Ledges Echanted", QPixmap(":/images/tiles/ledges-e1.gif"));
	map.insert("Linden Woods", QPixmap(":/images/tiles/lindenwoods1.gif"));
	map.insert("Linden Woods Echanted", QPixmap(":/images/tiles/lindenwoods-e1.gif"));
	map.insert("Maple Woods", QPixmap(":/images/tiles/maplewoods1.gif"));
	map.insert("Maple Woods Echanted", QPixmap(":/images/tiles/maplewoods-e1.gif"));
	map.insert("Mountain", QPixmap(":/images/tiles/mountain1.gif"));
	map.insert("Mountain Echanted", QPixmap(":/images/tiles/mountain-e1.gif"));
	map.insert("Nut Woods", QPixmap(":/images/tiles/nutwoods1.gif"));
	map.insert("Nut Woods Echanted", QPixmap(":/images/tiles/nutwoods-e1.gif"));
	map.insert("Oak Woods", QPixmap(":/images/tiles/oakwoods1.gif"));
	map.insert("Oak Woods Echanted", QPixmap(":/images/tiles/oakwoods-e1.gif"));
	map.insert("Pine Woods", QPixmap(":/images/tiles/pinewoods1.gif"));
	map.insert("Pine Woods Echanted", QPixmap(":/images/tiles/pinewoods-e1.gif"));
	map.insert("Ruins", QPixmap(":/images/tiles/ruins1.gif"));
	map.insert("Ruins Echanted", QPixmap(":/images/tiles/ruins-e1.gif"));
	return map;
}

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	ui.graphicsView->scale(0.75, 0.75);
	server = new ServerCommThread(this);
	selectedCharacter = 0;
	game = 0;
	selectedTile = 0;
	selectedAction = NoAction;
}

GameWindow::~GameWindow()
{
	if (server != 0)
	{
		delete server;
		server = 0;
	}
}

errno_t GameWindow::initializeConnection(QString &hostIP)
{
	errno_t err = 0;

	changeScreenState(ui.loadingWidget);
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		cleanup();
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

	changeScreenState(ui.characterSelectWidget);

	return err;
}

errno_t GameWindow::initializeGame(int character, bool cheatMode)
{
	errno_t err = 0;

	changeScreenState(ui.loadingWidget);

	selectedCharacter = new Character((CharacterTypes)character);

	QString serializedCharacter;
	serializedCharacter = QString("CharacterType%1%2").arg(CLASSDELIM, character);
	server->writeMessage(&serializedCharacter);
	
	gameScene = new QGraphicsScene();
	ui.graphicsView->setScene(gameScene);
	
	game = new Game();
	game->setupGame(cheatMode, selectedCharacter);
	Board* gameBoard = game->getBoard();

	Tile* currTile = gameBoard->getTile("Border Land");
	if (currTile)
	{
		selectTile(currTile);

		QPixmap pixmap = tileImages()[currTile->getName()];
		QGraphicsItem* item = new TileGraphicsItem(pixmap, currTile, this);
		item->setPos(0, 0);
		item->setRotation((360 / 6) * ((int)currTile->getOrientation()));
		item->setTransformOriginPoint(pixmap.width() / 2, pixmap.height() / 2);
	
		gameScene->addItem(item);

		unordered_set<Tile*> visitedTiles;
		visitedTiles.insert(currTile);

		QMap<Tile*, QPointF> locations;
		locations.insert(currTile, QPointF(0, 0));

		queue<Tile*> incompleteTiles;
		incompleteTiles.push(currTile);

		qreal xOffset = 1;
		qreal yOffset = 3;
		qreal xTileOffset = pixmap.width() - xOffset;
		qreal yTileOffset = pixmap.height() - yOffset;

		while (!incompleteTiles.empty())
		{
			currTile = incompleteTiles.front();
			incompleteTiles.pop();
			for (int i = 0; i < CONNECTED_LENGTH; i++)
			{
				Tile* newTile = currTile->getConnected((Direction)i);
				if ((newTile != 0) && (visitedTiles.find(newTile) == visitedTiles.end()))
				{
					QPixmap pixmap = tileImages()[newTile->getName()];
					QGraphicsItem* item = new TileGraphicsItem(pixmap, newTile, this);

					int side = ((int)(currTile->getOrientation()) + i) % 6;
					QPointF pos;
					switch (side)
					{
					case 0:
						pos = QPointF(locations[currTile].x(), locations[currTile].y() + yTileOffset);
						break;
					case 1:
						pos = QPointF(locations[currTile].x() - (xTileOffset * 0.75), locations[currTile].y() + (yTileOffset / 2));
						break;
					case 2:
						pos = QPointF(locations[currTile].x() - (xTileOffset * 0.75), locations[currTile].y() - (yTileOffset / 2));
						break;
					case 3:
						pos = QPointF(locations[currTile].x(), locations[currTile].y() - yTileOffset);
						break;
					case 4:
						pos = QPointF(locations[currTile].x() + (xTileOffset * 0.75), locations[currTile].y() - (yTileOffset / 2));
						break;
					case 5:
						pos = QPointF(locations[currTile].x() + (xTileOffset * 0.75), locations[currTile].y() + (yTileOffset / 2));
						break;
					default:
						pos = QPointF(0, 0);
						break;
					}
					item->setPos(pos);
					
					item->setRotation((360 / 6) * ((int)newTile->getOrientation()));
					item->setTransformOriginPoint(pixmap.width() / 2, pixmap.height() / 2);

					gameScene->addItem(item);

					incompleteTiles.push(newTile);
					visitedTiles.insert(newTile);
					locations.insert(newTile, pos);
				}
			}		
		}
	}

	changeScreenState(ui.gameWidget);

	return err;
}

errno_t GameWindow::cleanup()
{
	errno_t err = 0;

	err = server->threadDisconnect();

	if (game != 0)
	{
		delete game;
		game = 0;
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

Character* GameWindow::getSelectedChar()
{
	return selectedCharacter;
}

void GameWindow::selectTile(Tile* tile)
{
	selectedTile = tile;

	switch (selectedAction)
	{
	case NoAction:
		{
			break;
		}
	case MoveAction:
		{
			/*
			Clearing* currentClearing = selectedCharacter->getCurrentLocation();
			if (currentClearing->getTile() == selectedTile)
			{

			}
			else
			{
				Clearing* destination = selectedTile->getConnectedClearing(currentClearing->getTile());
				if (!game->moveRequest(selectedCharacter, destination))
				{
					QMessageBox::about(ui.centralWidget, "Woops", "That destination is out of reach.");
				}
			}
			*/
			break;
		}
	case SearchAction:
		{
			break;
		}
	case TradeAction:
		{
			break;
		}
	case HideAction:
		{
			break;
		}
	case PeerAction:
		{
			break;
		}
	default:
		{
			break;
		}
	}

	updateTileInfoPane(selectedTile);

	selectAction(NoAction);
}

void GameWindow::updateTileInfoPane(Tile* tile)
{
	QFont font = QFont("MS Serif", 26);
	font.setBold(true);
	font.setUnderline(true);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->setText(QString(tile->getName().c_str()));

	font.setPointSize(18);
	font.setUnderline(false);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->append("\nClearings");
	for (int i = 1; i < CONNECTED_LENGTH+1; i++)
	{
		Clearing* c = tile->getClearing(i);
		if (c != 0)
		{
			char* type;
			switch (c->getClearingType())
			{
			case WOODS:
				type = "Woods";
				break;
			case CAVES:
				type = "Caves";
				break;
			case MOUNTAIN:
				type = "Mountain";
				break;
			default:
				break;
			}
			QString clearingInfo;
			clearingInfo.sprintf("Clearing %d: %s", c->getClearingNum(), type);
			font.setPointSize(16);
			font.setBold(false);
			ui.gameTileInformationBrowser->setCurrentFont(font);
			ui.gameTileInformationBrowser->append(clearingInfo);

			vector<Character*> chrs = *c->getCharacters();
			ui.gameTileInformationBrowser->append("Players:");
			font.setPointSize(12);
			font.setBold(true);
			ui.gameTileInformationBrowser->setCurrentFont(font);
			for (vector<Character*>::iterator chr  = chrs.begin(); chr != chrs.end(); ++chr)
			{
				QString charString;
				charString.sprintf("  - %s", Character::getTypeString((*chr)->getType()));
				ui.gameTileInformationBrowser->append(charString);
			}
			ui.gameTileInformationBrowser->append("");
		}
	}
}

void GameWindow::selectAction(ActionType action)
{
	selectedAction = action;
	
	ui.gameMoveActionButton->setStyleSheet("");
	ui.gameSearchActionButton->setStyleSheet("");
	ui.gameTradeActionButton->setStyleSheet("");
	ui.gameHideActionButton->setStyleSheet("");
	ui.gamePeerActionButton->setStyleSheet("");
}

void GameWindow::move()
{
	Clearing* currentClearing = selectedCharacter->getCurrentLocation();
	vector<Path*> availablePaths = *currentClearing->getPaths();
	QList<Clearing*> adjacentClearings;
	for (vector<Path*>::iterator it = availablePaths.begin(); it != availablePaths.end(); ++it)
	{
		Path* p = *it;
		Clearing* end = p->getEnd(currentClearing);
		if (end != NULL && (!p->isHidden() /*|| player knows about hidden path */))
		{
			adjacentClearings.append(end);
		}
	}

	AvailableMovesDialog* dlg = new AvailableMovesDialog(ui.centralWidget);
	for (Clearing* c : adjacentClearings)
	{
		QString option;
		dlg->addOption(option.sprintf("%s: Clearing %d", c->getTile()->getName().c_str(), c->getClearingNum()));
	}
	int destIndex = dlg->exec();
	if (destIndex != -1)
	{
		Clearing* dest = adjacentClearings.at(destIndex);
		game->moveRequest(selectedCharacter, dest);
		updateTileInfoPane(dest->getTile());
	}
	delete dlg;

	selectAction(NoAction);
}