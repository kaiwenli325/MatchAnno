#include "MainScene.h"

MainScene::MainScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (event->button() == Qt::RightButton)
	{
		QPointF pos = event->scenePos();
		emit SendNewPoint(pos);
	}
}