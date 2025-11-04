#pragma once

#include <QTableWidget>
#include <QKeyEvent>
#include <iostream>

class MyTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	MyTableWidget(QString tableName, QWidget *parent = nullptr);

protected:
	virtual void keyPressEvent(QKeyEvent *event) override;
	QString tableName;

signals:
	void DeletePoint(QString tableName);
};

