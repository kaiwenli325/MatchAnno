#include "MyTableWidget.h"


MyTableWidget::MyTableWidget(QString tableName, QWidget *parent)
	: QTableWidget(parent)
{
	this->tableName = tableName;
}


void MyTableWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Backspace)
	{
		emit DeletePoint(tableName);
	}
	else
	{
		QTableWidget::keyPressEvent(event);
	}
}