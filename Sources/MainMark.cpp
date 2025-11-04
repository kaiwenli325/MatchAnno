#include "MainMark.h"


MainMark::MainMark()
{
	penLine.setColor(QColor(255, 0, 0));
	penLine.setWidth(1);

	penCir.setColor(QColor(255, 0, 0));
	penCir.setWidth(3);

	semiLineLen = 15;
	radius = 10;

}

QRectF MainMark::boundingRect() const
{
	return QRectF(-semiLineLen, -semiLineLen, 2*semiLineLen, 2*semiLineLen);
}

void MainMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	// crossing
	painter->setPen(penLine);
	QLineF hLine(0 - semiLineLen, 0, 0 + semiLineLen, 0);
	painter->drawLine(hLine); // horizontal line
	QLineF vLine(0, 0 - semiLineLen, 0, 0 + semiLineLen);
	painter->drawLine(vLine); // vertical line

	// circle
	painter->setPen(penCir);
	QRectF cirRect(0 - radius, 0 - radius, radius * 2, radius * 2);
	painter->drawEllipse(cirRect);

}

void MainMark::SetHighlightPen()
{
	penLine.setColor(QColor(0, 0, 255));
	penLine.setWidth(1);

	penCir.setColor(QColor(0, 0, 255));
	penCir.setWidth(3);

	update();
}

void MainMark::ResetPen() 
{
	penLine.setColor(QColor(255, 0, 0));
	penLine.setWidth(1);

	penCir.setColor(QColor(255, 0, 0));
	penCir.setWidth(3);

	update();
}


