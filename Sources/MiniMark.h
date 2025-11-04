#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QLineF>

class MiniMark : public QGraphicsItem
{
public:
	MiniMark();

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

	void SetHighlightPenBrush();
	void ResetPenBrush();

private:
	QPen penCir;
	qreal radius;
	QBrush brushCir;
};