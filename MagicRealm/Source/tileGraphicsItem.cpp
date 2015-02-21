#include "tileGraphicsItem.h"

TileGraphicsItem::TileGraphicsItem(QPixmap pixmap, Tile* tile, GameWindow* container)
{
	setPixmap(pixmap);
	setZValue(0);
	setAcceptHoverEvents(true);

	myTile = tile;
	myContainer = container;
}

TileGraphicsItem::~TileGraphicsItem()
{

}

void TileGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		setZValue(0);
		setScale(1);
		myContainer->selectTile(myTile);
	}
}

void TileGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		setZValue(0.1);
		setScale(1.05);
	}
}

void TileGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	setZValue(0.1);
	setScale(1.05);
}

void TileGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	setZValue(0);
	setScale(1);
}