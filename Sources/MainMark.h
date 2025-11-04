#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QLineF>

class MainMark : public QGraphicsItem
{
public:
	MainMark();

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

	void SetHighlightPen();
	void ResetPen();

private:
	QPen penLine;
	QPen penCir;
	qreal semiLineLen;
	qreal radius;
};

