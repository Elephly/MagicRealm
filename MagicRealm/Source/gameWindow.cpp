#include "gameWindow.h"

#include "tileGraphicsItem.h"
#include "availableMovesDialog.h"

#include <QMessageBox>

#include <queue>
#include <unordered_set>

#include <Windows.h>

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	gameStarted = false;
	characterImages = new QMap<CharacterTypes, QPixmap*>();
	loadCharacterImages();
	characterGraphicsItems = new QMap<CharacterTypes, QGraphicsItem*>();
	tileImages = new QMap<std::string, QPixmap*>();
	loadTileImages();
	tileGraphicsItems = new QMap<Tile*, QGraphicsItem*>();
	ui.graphicsView->scale(0.5, 0.5);
	server = new ServerCommThread(this);
	selectedCharacter = (CharacterTypes) 0;
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

	if (tileGraphicsItems != 0)
	{
		qDeleteAll(*tileGraphicsItems);
		tileGraphicsItems->clear();
		delete tileGraphicsItems;
		tileGraphicsItems = 0;
	}

	if (tileImages != 0)
	{
		qDeleteAll(*tileImages);
		tileImages->clear();
		delete tileImages;
		tileImages = 0;
	}
}

void GameWindow::loadCharacterImages()
{
	characterImages->insert(Amazon, new QPixmap(":/images/characters/amazon.png"));
	characterImages->insert(BlackKnight, new QPixmap(":/images/characters/black_knight.png"));
	characterImages->insert(Captain, new QPixmap(":/images/characters/captain.png"));
	characterImages->insert(Dwarf, new QPixmap(":/images/characters/dwarf.png"));
	characterImages->insert(Elf, new QPixmap(":/images/characters/elf.png"));
	characterImages->insert(Swordsman, new QPixmap(":/images/characters/swordsman.png"));
}

void GameWindow::loadTileImages()
{
	tileImages->insert("Awful Valley", new QPixmap(":/images/tiles/awfulvalley1.gif"));
	tileImages->insert("Awful Valley Enchanted", new QPixmap(":/images/tiles/awfulvalley-e1.gif"));
	tileImages->insert("Bad Valley", new QPixmap(":/images/tiles/badvalley1.gif"));
	tileImages->insert("Bad Valley Echanted", new QPixmap(":/images/tiles/badvalley-e1.gif"));
	tileImages->insert("Border Land", new QPixmap(":/images/tiles/borderland1.gif"));
	tileImages->insert("Border Land Echanted", new QPixmap(":/images/tiles/borderland-e1.gif"));
	tileImages->insert("Cavern", new QPixmap(":/images/tiles/cavern1.gif"));
	tileImages->insert("Cavern Echanted", new QPixmap(":/images/tiles/cavern-e1.gif"));
	tileImages->insert("Caves", new QPixmap(":/images/tiles/caves1.gif"));
	tileImages->insert("Caves Echanted", new QPixmap(":/images/tiles/caves-e1.gif"));
	tileImages->insert("Cliff", new QPixmap(":/images/tiles/cliff1.gif"));
	tileImages->insert("Cliff Echanted", new QPixmap(":/images/tiles/cliff-e1.gif"));
	tileImages->insert("Crag", new QPixmap(":/images/tiles/crag1.gif"));
	tileImages->insert("Crag Echanted", new QPixmap(":/images/tiles/crag-e1.gif"));
	tileImages->insert("Curst Valley", new QPixmap(":/images/tiles/curstvalley1.gif"));
	tileImages->insert("Curst Valley Echanted", new QPixmap(":/images/tiles/curstvalley-e1.gif"));
	tileImages->insert("Dark Valley", new QPixmap(":/images/tiles/darkvalley1.gif"));
	tileImages->insert("Dark Valley Echanted", new QPixmap(":/images/tiles/darkvalley-e1.gif"));
	tileImages->insert("Deep Woods", new QPixmap(":/images/tiles/deepwoods1.gif"));
	tileImages->insert("Deep Woods Echanted", new QPixmap(":/images/tiles/deepwoods-e1.gif"));
	tileImages->insert("Evil Valley", new QPixmap(":/images/tiles/evilvalley1.gif"));
	tileImages->insert("Evil Valley Echanted", new QPixmap(":/images/tiles/evilvalley-e1.gif"));
	tileImages->insert("High Pass", new QPixmap(":/images/tiles/highpass1.gif"));
	tileImages->insert("High Pass Echanted", new QPixmap(":/images/tiles/highpass-e1.gif"));
	tileImages->insert("Ledges", new QPixmap(":/images/tiles/ledges1.gif"));
	tileImages->insert("Ledges Echanted", new QPixmap(":/images/tiles/ledges-e1.gif"));
	tileImages->insert("Linden Woods", new QPixmap(":/images/tiles/lindenwoods1.gif"));
	tileImages->insert("Linden Woods Echanted", new QPixmap(":/images/tiles/lindenwoods-e1.gif"));
	tileImages->insert("Maple Woods", new QPixmap(":/images/tiles/maplewoods1.gif"));
	tileImages->insert("Maple Woods Echanted", new QPixmap(":/images/tiles/maplewoods-e1.gif"));
	tileImages->insert("Mountain", new QPixmap(":/images/tiles/mountain1.gif"));
	tileImages->insert("Mountain Echanted", new QPixmap(":/images/tiles/mountain-e1.gif"));
	tileImages->insert("Nut Woods", new QPixmap(":/images/tiles/nutwoods1.gif"));
	tileImages->insert("Nut Woods Echanted", new QPixmap(":/images/tiles/nutwoods-e1.gif"));
	tileImages->insert("Oak Woods", new QPixmap(":/images/tiles/oakwoods1.gif"));
	tileImages->insert("Oak Woods Echanted", new QPixmap(":/images/tiles/oakwoods-e1.gif"));
	tileImages->insert("Pine Woods", new QPixmap(":/images/tiles/pinewoods1.gif"));
	tileImages->insert("Pine Woods Echanted", new QPixmap(":/images/tiles/pinewoods-e1.gif"));
	tileImages->insert("Ruins", new QPixmap(":/images/tiles/ruins1.gif"));
	tileImages->insert("Ruins Echanted", new QPixmap(":/images/tiles/ruins-e1.gif"));
}

errno_t GameWindow::initializeConnection(QString &hostIP)
{
	errno_t err = 0;

	ui.loadingMessageLabel->setText("--Connecting to server--");
	changeScreenState(ui.loadingWidget);
	
	game = new Game();
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		cleanup();
		return err;
	}

	return err;
}

void GameWindow::connectedToServer()
{
	qDebug() << "client is connected to server, signal";
	for (int i = 0; i < ui.characterListView->count(); i++)
	{
		if (ui.characterListView->item(i)->flags() & Qt::ItemIsUserCheckable)
		{
			ui.characterListView->setCurrentRow(i);
			break;
		}
	}
	changeScreenState(ui.characterSelectWidget);
}

void GameWindow::updateAvailableCharacters(int removeCharacter)
{
	Qt::ItemFlags flags = ui.characterListView->item(removeCharacter)->flags();
	ui.characterListView->item(removeCharacter)->setFlags((flags & ~Qt::ItemIsSelectable & ~Qt::ItemIsUserCheckable & ~Qt::ItemIsEnabled));
}

void GameWindow::requestCharacter(CharacterTypes character, DwellingType startLoc)
{
	if (character >= Amazon && character <= Swordsman)
	{
		ui.loadingMessageLabel->setText("--Waiting for character acknowledgement--");
		changeScreenState(ui.loadingWidget);

		selectedCharacter = character;
		startLocation = startLoc;
	
		QString serializedCharacter;
		serializedCharacter.sprintf("CharacterType%s%d", CLASSDELIM, character);
		qDebug() << serializedCharacter;
		server->writeMessage(&serializedCharacter);
	}
}

void GameWindow::characterRequestAcknowledged(bool accepted)
{
	if (!accepted)
	{
		changeScreenState(ui.characterSelectWidget);
		QMessageBox::about(ui.centralWidget, "Error", "Character taken.");
		return;
	}

	ui.loadingMessageLabel->setText("--Waiting for game to begin--");
	changeScreenState(ui.loadingWidget);

	QString serializedStartLocation;
	serializedStartLocation.sprintf("SpawnLocation%s%d", CLASSDELIM, startLocation);
	qDebug() << serializedStartLocation;
	server->writeMessage(&serializedStartLocation);
}

void GameWindow::addCharacterToGame(QString &newCharacter) {
	game->addPlayer(new Character(new string(newCharacter.toUtf8().constData())));
}

errno_t GameWindow::initializeGame()
{
	errno_t err = 0;

	gameScene = new QGraphicsScene();

	game->setupGame(false);

	drawTiles();
	
	for (int i = 0; i <= Swordsman; i++)
	{
		QPixmap pxmap = *(*characterImages)[(CharacterTypes)i];
		QGraphicsItem* item = new QGraphicsPixmapItem(pxmap);
		item->setTransformOriginPoint(pxmap.width() / 2, pxmap.height() / 2);
		characterGraphicsItems->insert((CharacterTypes)i, item);
		updateCharacterLocation(game->getPlayer((CharacterTypes)i));
		gameScene->addItem(item);
	}
	
	updateCharacterInfoPane();
	
	ui.graphicsView->setScene(gameScene);
	changeScreenState(ui.gameWidget);

	return err;
}

errno_t GameWindow::drawTiles()
{
	Board* gameBoard = game->getBoard();

	Tile* currTile = gameBoard->getTile("Border Land");
	if (currTile != 0)
	{
		selectTile(currTile);

		QPixmap pixmap = *(*tileImages)[currTile->getName()];
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
			tileGraphicsItems->insert(currTile, item);
			currTile = incompleteTiles.front();
			incompleteTiles.pop();
			for (int i = 0; i < CONNECTED_LENGTH; i++)
			{
				Tile* newTile = currTile->getConnected((Direction)i);
				if ((newTile != 0) && (visitedTiles.find(newTile) == visitedTiles.end()))
				{
					QPixmap pixmap = *(*tileImages)[newTile->getName()];
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
		return 0;
	}
	return 1;
}

errno_t GameWindow::cleanup()
{
	errno_t err = 0;

	err = server->threadDisconnect();

	if (tileGraphicsItems != 0)
	{
		tileGraphicsItems->clear();
		delete tileGraphicsItems;
		tileGraphicsItems = 0;
	}

	if (game != 0)
	{
		delete game;
		game = 0;
	}

	gameStarted = false;
	
	changeScreenState(ui.menuWidget);

	return err;
}

void GameWindow::changeScreenState(QWidget* screen)
{
	ui.menuWidget->setEnabled(false);
	ui.loadingWidget->setEnabled(false);
	ui.characterSelectWidget->setEnabled(false);
	ui.gameWidget->setEnabled(false);
	ui.menuWidget->setVisible(false);
	ui.loadingWidget->setVisible(false);
	ui.characterSelectWidget->setVisible(false);
	ui.gameWidget->setVisible(false);
	screen->setEnabled(true);
	screen->setVisible(true);
	qApp->processEvents();
}

CharacterTypes GameWindow::getSelectedChar()
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

void GameWindow::updateCharacterInfoPane()
{
	Character* character = game->getPlayer(selectedCharacter);
	QFont font = QFont("MS Serif", 26);
	font.setBold(true);
	font.setUnderline(true);
	ui.gameCharacterInformationBrowser->setCurrentFont(font);
	ui.gameCharacterInformationBrowser->setText(Character::getTypeString(character->getType()));
	
	font.setPointSize(14);
	font.setUnderline(false);
	ui.gameCharacterInformationBrowser->setCurrentFont(font);

	QString characterInfo;
	//Clearing* loc = character->getCurrentLocation();
	//characterInfo.sprintf("\Location: %s Clearing %d: %s", loc->getTile()->getName().c_str(), loc->getClearingNum(),
	//	Clearing::getTypeString(loc->getClearingType()));
	//ui.gameCharacterInformationBrowser->append(characterInfo);
	
	characterInfo.sprintf("\nGold: %d", character->getGold());
	ui.gameCharacterInformationBrowser->append(characterInfo);

	//character->getEquipment();
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
			QString clearingInfo;
			clearingInfo.sprintf("Clearing %d: %s", c->getClearingNum(), 
				Clearing::getTypeString(c->getClearingType()));
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

void GameWindow::updateCharacterLocation(Character* character)
{
	/*
	Clearing* currClearing = character->getCurrentLocation();
	Tile* currTile = currClearing->getTile();
	QGraphicsItem* charItem = (*characterGraphicsItems)[character->getType()];
	charItem->setX((*tileGraphicsItems)[currTile]->x());
	*/
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

void GameWindow::moveAction()
{
	Clearing* currentClearing = game->getPlayer(selectedCharacter)->getCurrentLocation();
	vector<Path*> availablePaths = *currentClearing->getPaths();
	QList<Clearing*> adjacentClearings;
	for (vector<Path*>::iterator it = availablePaths.begin(); it != availablePaths.end(); ++it)
	{
		Path* p = *it;
		Clearing* end = p->getEnd(currentClearing);
		Character* character = game->getPlayer(selectedCharacter);
		if (end != NULL && (!p->isHidden() || character->isDiscovered(p)))
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
		myTurn->addAction(new Action(MoveAction, dest), BasicPhase);
	}
	delete dlg;

	selectAction(NoAction);
}

void GameWindow::moveTo(CharacterTypes character, QString& clearingString)
{
	if (!gameStarted)
	{
		gameStarted = true;
		initializeGame();
	}
	string second(clearingString.toUtf8().constData());

	int pos = second.find(VARDELIM);
	int id = atoi(second.substr(0, pos).c_str());
	second = second.substr(pos + 1);

	Clearing* clearing = game->getBoard()->getTile(second)->getClearing(id);
	//parse clearingString;
	game->move(game->getPlayer(character), clearing);
}

void GameWindow::doTurn(QString &turnString)
{
	string *s = new string(turnString.toUtf8().constData());
	if (myTurn != 0)
	{
		delete myTurn;
		myTurn = 0;
	}
	myTurn = new RecordedTurn(s, game->getBoard());
	delete s;
}