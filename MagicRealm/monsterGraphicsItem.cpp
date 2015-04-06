#include "monsterGraphicsItem.h"


MonsterGraphicsItem::MonsterGraphicsItem(QPixmap pixmap, Monster* monster, GameWindow* container)
	: QGraphicsPixmapItem(pixmap)
{
	setPixmap(pixmap);
	setAcceptHoverEvents(true);

	myWidth = pixmap.width();
	myHeight = pixmap.height();

	myMonster = monster;
	myContainer = container;
}


MonsterGraphicsItem::~MonsterGraphicsItem()
{
}

void MonsterGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		//setScale(scale() / 1.05);
		myContainer->selectMonster(myMonster);
	}
	QGraphicsPixmapItem::mousePressEvent(event);
}

void MonsterGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		//setScale(scale() * 1.05);
	}
	QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void MonsterGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	//setScale(scale() * 1.05);
	QGraphicsPixmapItem::hoverEnterEvent(event);
}

void MonsterGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	//setScale(scale() / 1.05);
	QGraphicsPixmapItem::hoverLeaveEvent(event);
}

int MonsterGraphicsItem::width()
{
	return myWidth;
}

int MonsterGraphicsItem::height()
{
	return myHeight;
}