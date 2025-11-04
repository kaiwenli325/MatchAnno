#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItem> 
#include <QRectF> 
#include <iostream>


class MiniScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MiniScene(QObject *parent = nullptr);

private:

};