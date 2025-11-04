#pragma once

#include <QGraphicsView>
#include <QWheelEvent>


class MainView : public QGraphicsView
{
	Q_OBJECT

public:
	MainView(QWidget *parent = nullptr);
	void CenterOnPos(QPointF centerPos);

protected:
	virtual void wheelEvent(QWheelEvent *) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
	double upScale;
	double downScale;
	bool isTranslate;
	QPoint lastMousePos;
	QRectF visSceneRect;

	void GetCurSceneVisRect();

signals:
	void SendCurSceneVisRect(QRectF visSceneRect);
};