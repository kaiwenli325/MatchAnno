#include "MiniMark.h"


MiniMark::MiniMark()
{
	// draw point
	penCir.setColor(QColor(255, 0, 0));
	radius = 20;

	brushCir.setColor(QColor(255, 0, 0));
	brushCir.setStyle(Qt::SolidPattern);
}

QRectF MiniMark::boundingRect() const
{
	return QRectF(-radius/2, -radius/2, radius, radius);
}

void MiniMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

	// draw circle
	painter->setPen(penCir);
	painter->setBrush(brushCir);
	QRectF cirRect(0 - radius, 0 - radius, radius * 2, radius * 2);
	painter->drawEllipse(cirRect);

}

void  MiniMark::SetHighlightPenBrush()
{
	penCir.setColor(QColor(0, 0, 255));
	brushCir.setColor(QColor(0, 0, 255));
	update();
}

void  MiniMark::ResetPenBrush()
{
	penCir.setColor(QColor(255, 0, 0));
	brushCir.setColor(QColor(255, 0, 0));
	update();
}
