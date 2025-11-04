#include "MainView.h"
#include <iostream>
#include<QScrollBar>

MainView::MainView(QWidget *parent)
	: QGraphicsView(parent)
{
	upScale = 1.1;
	downScale = 1/1.1;
	isTranslate = false;
}

void MainView::wheelEvent(QWheelEvent *e)
{
	QPoint sroll = e->angleDelta();
	if (sroll.y() > 0)
	{
		scale(upScale, upScale);
		GetCurSceneVisRect();
		emit SendCurSceneVisRect(visSceneRect);
	}
	else
	{
		//avoid that the size is too small
		qreal factor = transform().scale(downScale, downScale).mapRect(QRectF(0, 0, 1, 1)).width();
		if (factor < 0.07)
			return;

		scale(downScale, downScale);
		GetCurSceneVisRect();
		emit SendCurSceneVisRect(visSceneRect);
	}
	e->accept();
}


void MainView::mouseMoveEvent(QMouseEvent *event)
{
	if (isTranslate)
	{
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->position().rx() - lastMousePos.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->position().ry() - lastMousePos.y()));
	}
	lastMousePos = event->pos();
	GetCurSceneVisRect();
	emit SendCurSceneVisRect(visSceneRect);
	QGraphicsView::mouseMoveEvent(event);
}

void MainView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		isTranslate = true;
		lastMousePos = event->pos();
	}

	QGraphicsView::mousePressEvent(event);
}

void MainView::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		isTranslate = false;

	QGraphicsView::mouseReleaseEvent(event);
}

void MainView::GetCurSceneVisRect()
{
	QRect viewRect(0, 0, this->viewport()->width(), this->viewport()->height());
	visSceneRect = this->mapToScene(viewRect).boundingRect();
}

void MainView::CenterOnPos(QPointF centerPos)
{
	centerOn(centerPos);
	GetCurSceneVisRect();
	emit SendCurSceneVisRect(visSceneRect);
}
