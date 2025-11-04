#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsPixmapItem>
#include <QTableWidget>
#include <QHeaderView>
#include <vector>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QGraphicsColorizeEffect>

#include "MainView.h"
#include "MiniView.h"
#include "MainScene.h"
#include "MiniScene.h"
#include "MainMark.h"
#include "MiniMark.h"
#include "MyTableWidget.h"

class AnnoTool : public QWidget
{
    Q_OBJECT

public:
    AnnoTool(QWidget *parent = nullptr);
    ~AnnoTool();

private:
    // ******* Load Images and save results ********
    QPushButton *btnLoadImg;
    QLineEdit *leImgFolderPath;
    QString imgFolderPath;
    QString imgName1;
    QString imgName2;

    bool firstRun;
    QPushButton *btnSave;


    // **************** Graphics up ****************
    QPen penRect;
    QBrush brushRect;

    int upPreSelectedPoint;
    int downPreSelectedPoint;

    // Up View
    MainView *upView;
    MainScene *upScene;
    QGraphicsPixmapItem *upImg;
    std::vector<MainMark*> upMainMarkVec;

    // Mini Up View
    MiniView *miniUpView;
    MiniScene *miniUpScene;
    QGraphicsPixmapItem *miniUpImg;
    std::vector<MiniMark*> upMiniMarkVec;

    QGraphicsRectItem *miniUpRect;

    // up point list
    MyTableWidget *upPointTable;
    std::vector<QPointF> upMarkCoordiVec;

    // **************** Graphics down ****************

    // Down View
    MainView *downView;
    MainScene *downScene;
    QGraphicsPixmapItem *downImg;
    std::vector<MainMark*> downMainMarkVec;

    // Mini Up View
    MiniView *miniDownView;
    MiniScene *miniDownScene;
    QGraphicsPixmapItem *miniDownImg;
    std::vector<MiniMark*> downMiniMarkVec;

    QGraphicsRectItem *miniDownRect;

    // up point list
    MyTableWidget *downPointTable;
    std::vector<QPointF> downMarkCoordiVec;


private slots:
    void UpdateImgPair();
    void MiniUpSceneDrawRect(QRectF visSceneRect);
    void DrawUpMark(QPointF pos);
    void MiniDownSceneDrawRect(QRectF visSceneRect);
    void DrawDownMark(QPointF pos);
    void SelectPointOnTwoViews(int row, int column);
    void DeletePointOnTwoViews(QString senderTableName);
    void SaveResults();

private:
    virtual void resizeEvent(QResizeEvent *event) override;
    void RestorePoints();


};
