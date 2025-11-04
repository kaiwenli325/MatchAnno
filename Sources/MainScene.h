#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MainScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MainScene(QObject *parent = nullptr);


private:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
	QPen penLine;
	QPen penCir;
	qreal semiLineLen; 
	qreal radius;

signals:
	void SendNewPoint(QPointF pos);
};

