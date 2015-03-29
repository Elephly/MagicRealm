#include "gameWindow.h"

#include "availableMovesDialog.h"

#include <QMessageBox>
#include <QScrollBar>

#include <queue>
#include <unordered_set>

#include <Windows.h>

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	gameStarted = false;
	characterImages = new QMap<CharacterType, QPixmap*>();
	loadCharacterImages();
	characterGraphicsItems = new QMap<CharacterType, QGraphicsPixmapItem*>();
	tileImages = new QMap<std::string, QPixmap*>();
	loadTileImages();
	tileGraphicsItems = new QMap<Tile*, TileGraphicsItem*>();
	ui.graphicsView->scale(0.5, 0.5);
	server = new ServerCommThread(this);
	selectedCharacter = NullCharacter;
	game = 0;
	selectedTile = 0;
	destinationClearing = 0;
	selectedAction = NoAction;
	myTurn = 0;
	turnNumber = 1;
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
		//qDeleteAll(*tileGraphicsItems);
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
	characterImages->insert(Amazon, new QPixmap(":/images/counters/characters/amazon.png"));
	characterImages->insert(BlackKnight, new QPixmap(":/images/counters/characters/black_knight.png"));
	characterImages->insert(Captain, new QPixmap(":/images/counters/characters/captain.png"));
	characterImages->insert(Dwarf, new QPixmap(":/images/counters/characters/dwarf.png"));
	characterImages->insert(Elf, new QPixmap(":/images/counters/characters/elf.png"));
	characterImages->insert(Swordsman, new QPixmap(":/images/counters/characters/swordsman.png"));
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
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		cleanup();
		return err;
	}

	return err;
}

void GameWindow::connectedToServer(time_t time)
{
	
	game = new Game(time);

	game->setupGame(false);
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

void GameWindow::requestCharacter(CharacterType character, DwellingType startLoc)
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
	server->writeMessage(&serializedStartLocation);
}

void GameWindow::addCharacterToGame(QString &newCharacter) {
	Character* character = new Character(new string(newCharacter.toUtf8().constData()));
	game->addPlayer(character);
	if (gameStarted)
	{
		updateCharacterInfoPane();
		updateTileInfoPane(selectedTile);
		updateCharacterLocation(character);
	}
}

errno_t GameWindow::initializeGame()
{
	errno_t err = 0;

	gameScene = new QGraphicsScene();

	turnNumber = 1;
	
	tileLocations = new QMap<Tile*, QPointF>();

	drawTiles();
	
	for (int i = 0; i <= Swordsman; i++)
	{
		QPixmap pxmap = *(*characterImages)[(CharacterType)i];
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pxmap);
		item->setTransformOriginPoint(pxmap.width() / 2, pxmap.height() / 2);
		characterGraphicsItems->insert((CharacterType)i, item);
		item->setZValue(0.2);
		item->setVisible(false);
		Character* character = game->getPlayer((CharacterType)i);
		if (character != 0)
		{
			updateCharacterLocation(character);
		}
		gameScene->addItem(item);
	}
	
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
		TileGraphicsItem* item = new TileGraphicsItem(pixmap, currTile, this);
		item->setPos(0, 0);
		item->setRotation((360 / 6) * ((int)currTile->getOrientation()));
		item->setTransformOriginPoint(pixmap.width() / 2, pixmap.height() / 2);
		
		gameScene->addItem(item);

		unordered_set<Tile*> visitedTiles;
		visitedTiles.insert(currTile);

		tileLocations->insert(currTile, QPointF(0, 0));

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
					TileGraphicsItem* item = new TileGraphicsItem(pixmap, newTile, this);

					int side = ((int)(currTile->getOrientation()) + i) % 6;
					QPointF pos;
					switch (side)
					{
					case 0:
						pos = QPointF((*tileLocations)[currTile].x(), (*tileLocations)[currTile].y() + yTileOffset);
						break;
					case 1:
						pos = QPointF((*tileLocations)[currTile].x() - (xTileOffset * 0.75), (*tileLocations)[currTile].y() + (yTileOffset / 2));
						break;
					case 2:
						pos = QPointF((*tileLocations)[currTile].x() - (xTileOffset * 0.75), (*tileLocations)[currTile].y() - (yTileOffset / 2));
						break;
					case 3:
						pos = QPointF((*tileLocations)[currTile].x(), (*tileLocations)[currTile].y() - yTileOffset);
						break;
					case 4:
						pos = QPointF((*tileLocations)[currTile].x() + (xTileOffset * 0.75), (*tileLocations)[currTile].y() - (yTileOffset / 2));
						break;
					case 5:
						pos = QPointF((*tileLocations)[currTile].x() + (xTileOffset * 0.75), (*tileLocations)[currTile].y() + (yTileOffset / 2));
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
					tileLocations->insert(newTile, pos);
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

	/*
	if (tileGraphicsItems != 0)
	{
		tileGraphicsItems->clear();
		delete tileGraphicsItems;
		tileGraphicsItems = 0;
	}
	*/

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

void GameWindow::enableActions()
{
	ui.gameMoveActionButton->setEnabled(true);
	ui.gameSearchActionButton->setEnabled(true);
	ui.gameTradeActionButton->setEnabled(true);
	ui.gameHideActionButton->setEnabled(true);
}

void GameWindow::disableActions()
{
	ui.gameMoveActionButton->setDisabled(true);
	ui.gameSearchActionButton->setDisabled(true);
	ui.gameTradeActionButton->setDisabled(true);
	ui.gameHideActionButton->setDisabled(true);
}

CharacterType GameWindow::getSelectedChar()
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
	Clearing* loc = character->getCurrentLocation();
	characterInfo.sprintf("\nLocation: %s Clearing %d: %s", loc->getTile()->getName().c_str(), loc->getClearingNum(), Clearing::getTypeString(loc->getClearingType()));
	ui.gameCharacterInformationBrowser->append(characterInfo);
	
	characterInfo.sprintf("\nGold: %d", character->getGold());
	ui.gameCharacterInformationBrowser->append(characterInfo);

	ui.gameCharacterInformationBrowser->append("\nEquipment:");
	vector<Equipment*>* equipment = character->getEquipment();
	for (vector<Equipment*>::iterator it = equipment->begin(); it != equipment->end(); ++it)
	{
		characterInfo.sprintf("  - %s", (*it)->getName().c_str());
		ui.gameCharacterInformationBrowser->append(characterInfo);
	}
	ui.gameCharacterInformationBrowser->verticalScrollBar()->setValue(0);
}

void GameWindow::updateTileInfoPane(Tile* tile)
{
	QFont font = QFont("MS Serif", 26);
	font.setBold(true);
	font.setUnderline(true);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->setText(QString(tile->getName().c_str()));
	
	// CHITS INFO
	font.setPointSize(18);
	font.setUnderline(false);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->append("\nChits");
	Chit* siteOrSoundChit = tile->getSiteOrSoundChit();
	if (siteOrSoundChit != 0 && (!siteOrSoundChit->isHidden() ||
		(game->getPlayer(selectedCharacter)->getCurrentLocation() != 0 &&
		tile == game->getPlayer(selectedCharacter)->getCurrentLocation()->getTile())))
	{
		font.setPointSize(16);
		font.setBold(false);
		ui.gameTileInformationBrowser->setCurrentFont(font);
		QString chitInfo;
		ChitType chitType = siteOrSoundChit->getType();
		bool lost = false;
		switch (chitType)
		{
		case CHIT_SOUND:
			chitInfo.append("Sound: ");
			break;
		case CHIT_SITE:
			chitInfo.append("Site: ");
			break;
		case CHIT_LOST:
			lost = true;
		case CHIT_WARNING:
		default:
				break;
		}
		chitInfo.append(siteOrSoundChit->getName().c_str());
		ui.gameTileInformationBrowser->append(chitInfo);
		if (lost)
		{
			font.setPointSize(14);
			ui.gameTileInformationBrowser->setCurrentFont(font);
			vector<Chit*>* treasureChits = siteOrSoundChit->getContents();
			for (vector<Chit*>::iterator it = treasureChits->begin(); it != treasureChits->end(); ++it)
			{
				chitInfo.sprintf(" - %s", (*it)->getName().c_str());
				ui.gameTileInformationBrowser->append(chitInfo);
			}
		}
	}
	else
	{
		if (tile->getType() == TILE_CAVES || tile->getType() == TILE_MOUNTAIN)
		{
			ui.gameTileInformationBrowser->append("???");
		}
	}
	Chit* warningChit = tile->getWarningChit();
	if (warningChit != 0 && (!warningChit->isHidden() ||
		(game->getPlayer(selectedCharacter)->getCurrentLocation() != 0 &&
		tile == game->getPlayer(selectedCharacter)->getCurrentLocation()->getTile())))
	{
		font.setPointSize(16);
		font.setBold(false);
		ui.gameTileInformationBrowser->setCurrentFont(font);
		QString chitInfo;
		chitInfo.sprintf("Warning: %s", warningChit->getName().c_str());
		ui.gameTileInformationBrowser->append(chitInfo);
	}
	else
	{
		ui.gameTileInformationBrowser->append("???");
	}

	// CLEARINGS INFO
	font.setPointSize(18);
	font.setBold(true);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->append("\nClearings");
	for (int i = 1; i < CONNECTED_LENGTH+1; i++)
	{
		Clearing* c = tile->getClearing(i);
		if (c != 0)
		{
			QString clearingInfo;
			Dwelling* d = c->getDwelling();
			if (d != 0)
			{
				clearingInfo.sprintf("Clearing %d: %s\n%s", c->getClearingNum(), 
					Clearing::getTypeString(c->getClearingType()), c->getDwelling()->getName().c_str());
			}
			else
			{
				clearingInfo.sprintf("Clearing %d: %s", c->getClearingNum(), 
					Clearing::getTypeString(c->getClearingType()));
			}
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
				if ((*chr)->isHidden())
				{
					charString.append(" (hidden)");
				}
				ui.gameTileInformationBrowser->append(charString);
			}
			ui.gameTileInformationBrowser->append("");
		}
	}
	ui.gameTileInformationBrowser->verticalScrollBar()->setValue(0);
}

void GameWindow::updateCharacterLocation(Character* character)
{
	Clearing* currClearing = character->getCurrentLocation();
	if (currClearing != 0)
	{
		Tile* currTile = currClearing->getTile();
		if (currTile != 0)
		{
			QGraphicsPixmapItem* charItem = ((*characterGraphicsItems)[character->getType()]);
			TileGraphicsItem* tileItem = ((*tileGraphicsItems)[currTile]);
			charItem->setX((*tileLocations)[currTile].x() + (tileItem->width() / 2) - (charItem->pixmap().width() / 2));
			charItem->setY((*tileLocations)[currTile].y() + (tileItem->height() / 2) - (charItem->pixmap().height() / 2));
			charItem->setVisible(true);
		}
	}
}

void GameWindow::selectAction(ActionType action)
{
	selectedAction = action;
	bool actionCompleted = false;
	QString eventString;
	
	if (action == NoAction)
	{

	}
	else if (action == MoveAction)
	{
		actionCompleted = moveAction();
		if (actionCompleted)
		{
			eventString.sprintf(" - Move to %s clearing %d", destinationClearing->getTile()->getName().c_str(),
				destinationClearing->getClearingNum());
			ui.gameEventFeedBrowser->append(eventString);
		}
	}
	else if (action == SearchAction)
	{
		actionCompleted = true;
		if (actionCompleted)
		{
			eventString.sprintf(" - Search %s clearing %d", destinationClearing->getTile()->getName().c_str(),
				destinationClearing->getClearingNum());
			ui.gameEventFeedBrowser->append(eventString);
		}
	}
	else if (action == TradeAction)
	{
		actionCompleted = true;
		if (actionCompleted)
		{
			eventString.sprintf(" - Trade");
			ui.gameEventFeedBrowser->append(eventString);
		}
	}
	else if (action == HideAction)
	{
		actionCompleted = true;
		if (actionCompleted)
		{
			eventString.sprintf(" - Hide at %s clearing %d", destinationClearing->getTile()->getName().c_str(),
				destinationClearing->getClearingNum());
			ui.gameEventFeedBrowser->append(eventString);
		}
	}

	if (actionCompleted)
	{
		myTurn->addAction(new Action(action, destinationClearing), currentPhase);
		ui.gamePhaseComboBox->removeItem(ui.gamePhaseComboBox->currentIndex());
		caveCheck();
		int movablePhases = 0;
		for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
		{
			if (ui.gamePhaseComboBox->itemText(i) == "Basic")
			{
				movablePhases++;
			}
		}
		if (movablePhases <= 0)
		{
			for (int i = 0; i < sunlightPhases; i++)
			{
				ui.gamePhaseComboBox->addItem("Adding sunlight phase");
				for (int i = ui.gamePhaseComboBox->count() - 1; i > 0 ; i--)
				{
					ui.gamePhaseComboBox->setItemText(i, ui.gamePhaseComboBox->itemText(i-1));
					ui.gamePhaseComboBox->setItemIcon(i, ui.gamePhaseComboBox->itemIcon(i-1));
				}
				ui.gamePhaseComboBox->setItemText(0, "Sunlight");
				ui.gamePhaseComboBox->setItemIcon(0, QIcon(":/images/phases/sunshine.gif"));
			}
			if (sunlightPhases > 0)
			{
				enableActions();
			}
			sunlightPhases = 0;
		}
	}

	selectedAction = NoAction;
}

bool GameWindow::moveAction()
{
	vector<Path*> availablePaths = *(destinationClearing->getPaths());
	QList<Clearing*> adjacentClearings;
	for (vector<Path*>::iterator it = availablePaths.begin(); it != availablePaths.end(); ++it)
	{
		Path* p = *it;
		Clearing* end = p->getEnd(destinationClearing);
		Character* character = game->getPlayer(selectedCharacter);
		if (end != NULL && ((p->getType() == NORMAL) || character->isDiscovered(p)))
		{
			adjacentClearings.append(end);
		}
	}

	int movingPhases = countMovingPhases();

	AvailableMovesDialog* dlg = new AvailableMovesDialog(ui.centralWidget);
	for (Clearing* c : adjacentClearings)
	{
		bool noMountainClimb = true;
		bool noSunlightIntoCaves = true;

		QString option;
		option.sprintf("%s: Clearing %d", c->getTile()->getName().c_str(), c->getClearingNum());
		if ((destinationClearing->getClearingType() == MOUNTAIN && c->getClearingType() != MOUNTAIN) ||
			(destinationClearing->getClearingType() != MOUNTAIN && c->getClearingType() == MOUNTAIN))
		{
			option.append(" (Cost: 2 phases to climb/descend)");
			noMountainClimb = false;
		}
		if (c->getClearingType() == CAVES && ui.gamePhaseComboBox->currentText() == "Sunlight")
		{
			option.append(" (May not move into a cave using sunlight phase)");
			noSunlightIntoCaves = false;
		}

		dlg->addOption(option, ((noMountainClimb || (movingPhases > 1)) && noSunlightIntoCaves));
	}
	int destIndex = dlg->exec();

	bool moveConfirmed = false;

	if (destIndex != -1)
	{
		moveConfirmed = true;
		Clearing* newDest = adjacentClearings.at(destIndex);
		if ((destinationClearing->getClearingType() == MOUNTAIN && newDest->getClearingType() != MOUNTAIN) ||
			(destinationClearing->getClearingType() != MOUNTAIN && newDest->getClearingType() == MOUNTAIN))
		{
			payForMountainClimb();
		}
		destinationClearing = newDest;
	}
	delete dlg;

	return moveConfirmed;
}

void GameWindow::moveTo(CharacterType character, QString& clearingString)
{
	if (!gameStarted && (selectedCharacter != NullCharacter))
	{
		gameStarted = true;
		initializeGame();
	}
	string second(clearingString.toUtf8().constData());

	int pos = second.find(VARDELIM);
	int id = atoi(second.substr(pos + 1).c_str());
	second = second.substr(0, pos);

	Clearing* clearing = game->getBoard()->getTile(second)->getClearing(id);
	
	game->move(game->getPlayer(character), clearing);
	if (gameStarted)
	{
		if (selectedCharacter == character)
		{
			destinationClearing = clearing;
		}
		updateCharacterInfoPane();
		updateTileInfoPane(selectedTile);
		updateCharacterLocation(game->getPlayer((CharacterType)character));
		
		QString eventString;
		eventString.sprintf("%s moved to %s clearing %d", Character::getTypeString((CharacterType)character),
			clearing->getTile()->getName().c_str(), clearing->getClearingNum());
		ui.gameEventFeedBrowser->append(eventString);
	}
}

void GameWindow::setCharacterHidden(CharacterType character, bool hidden)
{
	Character* c = game->getPlayer(character);
	QString eventString;
	if (hidden)
	{
		if (!c->isHidden())
		{
			c->toggleHide();
		}
		eventString.sprintf("%s hid.", Character::getTypeString(character));
	}
	else
	{
		if (c->isHidden())
		{
			c->toggleHide();
		}
		else
		{
			eventString.sprintf("%s failed to hide.", Character::getTypeString(character));
		}
	}
	ui.gameEventFeedBrowser->append(eventString);
}

void GameWindow::searchTypeRequest(QString& searchTypes)
{
	int pos = searchTypes.indexOf(CLASSDELIM);
	searchTypes = searchTypes.remove(0, pos + 2);
	pos = searchTypes.indexOf(VARDELIM);
	searchTypes = searchTypes.right(searchTypes.size() - (pos + 1));
	pos = searchTypes.indexOf(VARDELIM);
	int searchType;
	if (pos != -1) {
		searchType = QMessageBox::question(ui.centralWidget, "Search Type", "How would you like to search?", "Peer", "Locate", "Loot");
	} else {
		searchType = QMessageBox::question(ui.centralWidget, "Search Type", "How would you like to search?", "Peer", "Locate");
	}
	
	QString serializedSearchType;
	serializedSearchType.sprintf("SearchTypeResp%s%d", CLASSDELIM, searchType);
	server->writeMessage(&serializedSearchType);
}

void GameWindow::search(CharacterType character, SearchType searchType)
{
	Character* c = game->getPlayer(character);
	switch (searchType)
	{
	case PEER:
		game->searchPeerRequest();
		break;
	case LOCATE:
		game->searchLocateRequest();
		break;
	case LOOT:
		game->searchLootRequest(c);
		break;
	default:
		break;
	}
}

void GameWindow::treasureFound(CharacterType character, int treasureWorth)
{
	Character* c = game->getPlayer(character);
	c->addGold(treasureWorth);
	QString eventString;
	eventString.sprintf("%s found %d gold!", Character::getTypeString(character), treasureWorth);
	ui.gameEventFeedBrowser->append(eventString);
}

void GameWindow::siteFound(CharacterType character, QString& siteName)
{
	Character* c = game->getPlayer(character);
	Chit* chit = c->getCurrentLocation()->getTile()->getSiteOrSoundChit();
	if (chit->getType() == CHIT_LOST)
	{
		vector<Chit*>* lostChits = chit->getContents();
		for (vector<Chit*>::iterator it = lostChits->begin(); it != lostChits->end(); ++it)
		{
			QString chitName;
			chitName.append((*it)->getName().c_str());
			if (siteName == chitName)
			{
				chit = *it;
				break;
			}
		}
	}
	c->discover(chit);
	QString eventString;
	eventString.sprintf("%s found %s!", Character::getTypeString(character), chit->getName().c_str());
	ui.gameEventFeedBrowser->append(eventString);
}

void GameWindow::doTurn(QString &turnString)
{
	string *s = new string(turnString.toUtf8().constData());
	if (myTurn != 0)
	{
		delete myTurn;
		myTurn = 0;
	}
	myTurn = new RecordedTurn(s);
	delete s;

	ui.gamePhaseComboBox->clear();
	ui.gamePhaseComboBox->setEnabled(true);

	sunlightPhases = 0;

	map<PhaseType, int>* availablePhases = myTurn->getAvailablePhases();
	for (map<PhaseType, int>::iterator it = availablePhases->begin(); it != availablePhases->end(); ++it)
	{
		for (int i = 0; i < it->second; i++)
		{
			switch (it->first)
			{
			case MovePhase:
				ui.gamePhaseComboBox->addItem("Move");
				ui.gamePhaseComboBox->setItemIcon(ui.gamePhaseComboBox->count()-1, QIcon(":/images/actions/move.gif"));
				break;
			case BasicPhase:
				ui.gamePhaseComboBox->addItem("Basic");
				ui.gamePhaseComboBox->setItemIcon(ui.gamePhaseComboBox->count()-1, QIcon(":/images/phases/basic.gif"));
				break;
			case SunlightPhase:
				sunlightPhases++;
				break;
			case HidePhase:
				ui.gamePhaseComboBox->addItem("Hide");
				ui.gamePhaseComboBox->setItemIcon(ui.gamePhaseComboBox->count()-1, QIcon(":/images/actions/hide.gif"));
				break;
			default:
				break;
			}
		}
	}
	QString eventString;
	eventString.sprintf("Plot turn %d:", turnNumber);
	ui.gameEventFeedBrowser->append(eventString);
	caveCheck();
	ui.gameSubmitTurnButton->setEnabled(true);
}

void GameWindow::submitTurn()
{
	server->writeMessage(myTurn->serialize());
	disableActions();
	ui.gamePhaseComboBox->setDisabled(true);
	ui.gameSubmitTurnButton->setDisabled(true);
	QString eventString;
	eventString.sprintf("Turn %d submitted.", turnNumber);
	ui.gameEventFeedBrowser->append(eventString);
	turnNumber++;
}

void GameWindow::setCurrentPhaseType(const QString& phaseString)
{
	disableActions();
	if (phaseString == "Basic")
	{
		currentPhase = BasicPhase;
		enableActions();
	}
	else if (phaseString == "Sunlight")
	{
		currentPhase = SunlightPhase;
		enableActions();
	}
	else if (phaseString == "Move")
	{
		currentPhase = MovePhase;
		ui.gameMoveActionButton->setEnabled(true);
	}
	else if (phaseString == "Hide")
	{
		currentPhase = HidePhase;
		ui.gameHideActionButton->setEnabled(true);
	}
	else
	{
		qDebug() << "phase check failed";
	}
}

void GameWindow::caveCheck()
{
	int phasesToRemove = 0;

	if (destinationClearing->getClearingType() == CAVES)
	{
		sunlightPhases = 0;

		for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
		{
			if (ui.gamePhaseComboBox->itemText(i) == "Sunlight")
			{
				phasesToRemove++;
			}
		}
		ui.gameEventFeedBrowser->append(" - Sunlight phases lost in cave clearing.");
	}
	
	for (int i = 0; i < phasesToRemove; i++)
	{
		for (int j = 0; j < ui.gamePhaseComboBox->count(); j++)
		{
			if (ui.gamePhaseComboBox->itemText(j) == "Sunlight")
			{
				ui.gamePhaseComboBox->removeItem(j);
			}
		}
	}
}

int GameWindow::countMovingPhases()
{
	int movingPhases = 0;

	for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
	{
		if (isMovingPhase(i))
		{
			movingPhases++;
		}
	}

	return movingPhases;
}

bool GameWindow::isMovingPhase(int phaseIndex)
{
	return (ui.gamePhaseComboBox->itemText(phaseIndex) == "Basic" ||
			ui.gamePhaseComboBox->itemText(phaseIndex) == "Sunlight" ||
			ui.gamePhaseComboBox->itemText(phaseIndex) == "Move");
}

void GameWindow::payForMountainClimb()
{
	QString currentSelectedPhase = ui.gamePhaseComboBox->currentText();
	for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
	{
		if (ui.gamePhaseComboBox->currentIndex() != i && isMovingPhase(i))
		{
			QString eventString;
			eventString.sprintf(" - Extra %s phase used to pay for mountain climb.", 
				ui.gamePhaseComboBox->itemText(i));
			ui.gameEventFeedBrowser->append(eventString);
			ui.gamePhaseComboBox->removeItem(i);
			break;
		}
	}

	for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
	{
		if (ui.gamePhaseComboBox->itemText(i) == currentSelectedPhase)
		{
			ui.gamePhaseComboBox->setCurrentIndex(i);
			break;
		}
	}
}

void GameWindow::setupChit(QString& chitString) {
	//Strip the Chit identifier from the string
	int pos = chitString.indexOf(CLASSDELIM);
	chitString = chitString.right(chitString.size() - (pos + 2));

	//find the end of the chit name
	pos = chitString.indexOf("Tile");
	string name = string(chitString.left(pos).toUtf8().constData());
	qDebug() << "Chit Name: " << QString(name.c_str());

	//strip the Tile identifier from the string
	pos = chitString.indexOf(CLASSDELIM);
	chitString = chitString.right(chitString.size() - (pos + 2));
	string tName;

	Chit* chit = game->getBoard()->getChitByName(name);
	
	pos = chitString.indexOf(LISTDELIM);
	if (pos != -1)
	{
		tName = string(chitString.left(pos).toUtf8().constData());
		chitString = chitString.right(chitString.size() - (pos + 1));
		qDebug() << "contained chits: " << chitString;

		//add contents to lost chits
		string innerChit;
		while ((pos = chitString.indexOf(LISTDELIM)) != -1)
		{
			innerChit = string(chitString.left(pos).toUtf8().constData());
			chitString = chitString.right(chitString.size() - (pos + 1));
			innerChit = innerChit.substr(innerChit.find(CLASSDELIM) + 2);
			qDebug() << "innerChit: " << QString(innerChit.c_str());
			qDebug() << "chitString remainder: " << chitString;
			//TODO add to contents of chit
		}
		innerChit = string(chitString.toUtf8().constData());
		innerChit = innerChit.substr(innerChit.find(CLASSDELIM) + 2);
		qDebug() << "innerChit: " << QString(innerChit.c_str());
		//TODO add to contents of chit
	}
	else 
	{
		tName = string(chitString.toUtf8().constData());
	}

	//add chits to the correct tiles
	if (chit->getType() == CHIT_WARNING) {
		game->getBoard()->getTile(tName)->addWarningChit((Warning*)chit);
	} else {
		game->getBoard()->getTile(tName)->addSiteOrSoundChit(chit);
	}

	qDebug() << "Tile Name: " << QString(tName.c_str());
}