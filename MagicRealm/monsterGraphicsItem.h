#ifndef MONSTERGRAPHICSITEM_H
#define MONSTERGRAPHICSITEM_H

#include <QGraphicsItem>
#include "gameWindow.h"
#include "monster.h"

class GameWindow;

class MonsterGraphicsItem : public QGraphicsPixmapItem
{
public:
	MonsterGraphicsItem(QPixmap pixmap, Monster* monster, GameWindow* container);
	~MonsterGraphicsItem();
	int width();
	int height();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *evernt);

private:
	Monster* myMonster;
	GameWindow* myContainer;
	int myWidth;
	int myHeight;
};

#endif