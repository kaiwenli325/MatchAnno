#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>

#include "AnnoTool.h"
#include "MainView.h"

AnnoTool::AnnoTool(QWidget *parent)
    : QWidget(parent)
{
    // ******************************************
    //      Load Images and save results
    // ******************************************

    // *********** load images **********
    btnLoadImg = new QPushButton(QString("Load Img"), this);
    leImgFolderPath = new QLineEdit(this);


    // ************** save **************
    firstRun = true;
    btnSave = new QPushButton(QString("Save"), this);


    // ************** layout ************
    QHBoxLayout *layoutLoadImg = new QHBoxLayout;
    layoutLoadImg->addWidget(btnLoadImg);
    layoutLoadImg->addWidget(leImgFolderPath);
    layoutLoadImg->addWidget(btnSave);




    // ******************************************
    //                Graphics
    // ******************************************
    upPreSelectedPoint = -1;
    downPreSelectedPoint = -1;

    penRect.setColor(QColor(255, 255, 0));
    penRect.setWidth(10);

    brushRect.setStyle(Qt::NoBrush);

    // ************** up **************
    // up main
    upImg = new QGraphicsPixmapItem();
    upImg->setPos(QPointF(0, 0));
    upScene = new MainScene(this);
    upScene->addItem(upImg);
    upView = new MainView(this);
    upView->setScene(upScene);


    // mini up
    miniUpImg = new QGraphicsPixmapItem();
    miniUpImg->setPos(QPointF(0, 0));

    miniUpRect = new QGraphicsRectItem();
    miniUpRect->setPen(penRect);
    miniUpRect->setBrush(brushRect);

    miniUpScene = new MiniScene(this);
    miniUpScene->addItem(miniUpImg);
    miniUpScene->addItem(miniUpRect);

    miniUpView = new MiniView(this);
    miniUpView->setScene(miniUpScene);


    connect(upScene, &MainScene::SendNewPoint, this, &AnnoTool::DrawUpMark);
    connect(upView, &MainView::SendCurSceneVisRect, this, &AnnoTool::MiniUpSceneDrawRect);

    // up point view
    upPointTable = new MyTableWidget("up", this);
    upPointTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    upPointTable->setColumnCount(1);
    upPointTable->setHorizontalHeaderLabels(QStringList() << "Coordinate" );
    upPointTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(upPointTable, &MyTableWidget::DeletePoint, this, &AnnoTool::DeletePointOnTwoViews);
    connect(upPointTable, &MyTableWidget::cellClicked, this, &AnnoTool::SelectPointOnTwoViews);

    // ************** down **************
    // down main
    downImg = new QGraphicsPixmapItem();
    downImg->setPos(QPointF(0, 0));
    downScene = new MainScene(this);
    downScene->addItem(downImg);
    downView = new MainView(this);
    downView->setScene(downScene);

    // mini down
    miniDownImg = new QGraphicsPixmapItem();
    miniDownImg->setPos(QPointF(0, 0));

    miniDownRect = new QGraphicsRectItem();
    miniDownRect->setPen(penRect);
    miniDownRect->setBrush(brushRect);

    miniDownScene = new MiniScene(this);
    miniDownScene->addItem(miniDownImg);
    miniDownScene->addItem(miniDownRect);

    miniDownView = new MiniView(this);
    miniDownView->setScene(miniDownScene);


    connect(downScene, &MainScene::SendNewPoint, this, &AnnoTool::DrawDownMark);
    connect(downView, &MainView::SendCurSceneVisRect, this, &AnnoTool::MiniDownSceneDrawRect);

    // down point view
    downPointTable = new MyTableWidget("down", this);
    downPointTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    downPointTable->setColumnCount(1);
    downPointTable->setHorizontalHeaderLabels(QStringList() << "Coordinate");
    downPointTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(downPointTable, &MyTableWidget::DeletePoint, this, &AnnoTool::DeletePointOnTwoViews);
    connect(downPointTable, &MyTableWidget::cellClicked, this, &AnnoTool::SelectPointOnTwoViews);


    //************** layout **************
    // up layout
    QGridLayout *upLayout = new QGridLayout;
    upLayout->addWidget(upView, 0, 0, 3, 3);
    upLayout->addWidget(miniUpView, 0, 3, 1, 1);
    upLayout->addWidget(upPointTable, 1, 3, 1, 1);
    upLayout->setColumnStretch(0, 1);
    upLayout->setColumnStretch(1, 1);
    upLayout->setColumnStretch(2, 1);
    upLayout->setColumnStretch(3, 1);
    upLayout->setRowStretch(0, 1);
    upLayout->setRowStretch(1, 1);

    // down layout
    QGridLayout *downLayout = new QGridLayout;
    downLayout->addWidget(downView, 0, 0, 3, 3);
    downLayout->addWidget(miniDownView, 0, 3, 1, 1);
    downLayout->addWidget(downPointTable, 1, 3, 1, 1);
    downLayout->setColumnStretch(0, 1);
    downLayout->setColumnStretch(1, 1);
    downLayout->setColumnStretch(2, 1);
    downLayout->setColumnStretch(3, 1);
    downLayout->setRowStretch(0, 1);
    downLayout->setRowStretch(1, 1);

    // ******************************************
    //                Top Layout
    // ******************************************
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layoutLoadImg);
    layout->addLayout(upLayout);
    layout->addLayout(downLayout);

    setLayout(layout);


    // ******************************************
    //             signals and slots
    // ******************************************
    connect(btnLoadImg, &QPushButton::clicked, this, &AnnoTool::UpdateImgPair);
    connect(btnSave, &QPushButton::clicked, this, &AnnoTool::SaveResults);

}

AnnoTool::~AnnoTool()
{}


void AnnoTool::UpdateImgPair()
{

    //************ auto save *************
    if(firstRun)
    {

    }

    // ************ clear old content *************
    // up
    upScene->clear();
    upMainMarkVec.clear();

    miniUpScene->clear();
    upMiniMarkVec.clear();

    upPointTable->setRowCount(0);
    upMarkCoordiVec.clear();

    // down
    downScene->clear();
    downMainMarkVec.clear();

    miniDownScene->clear();
    downMiniMarkVec.clear();

    downPointTable->setRowCount(0);
    downMarkCoordiVec.clear();

    //************** open new images **************
    imgFolderPath = QFileDialog::getExistingDirectory(this, tr("Select a folder"));
    leImgFolderPath->setText(imgFolderPath);

    QDir dir(imgFolderPath);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();

    QString imgPath1;
    QString imgPath2;
    bool hasResFlag = false;
    if (fileList.size() == 3)  
    {
        for (int i = 0; i < fileList.size(); i++)
        {
            QFileInfo fileInfo = fileList.at(i);
            if(fileInfo.suffix() == "json")
            {
                QFile file(fileList.at(i).filePath());
                if (!file.open(QFile::ReadOnly | QFile::Text)) {
                    qDebug() << "can't open json error!";
                    return;
                }

                QTextStream stream(&file);
                QString jsonAsStr = stream.readAll();
                file.close();

                QJsonParseError jsonError;
                QJsonDocument doc = QJsonDocument::fromJson(jsonAsStr.toUtf8(), &jsonError);
                if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
                    qDebug() << "Json∏Ò Ω¥ÌŒÛ£°" << jsonError.error;
                    return;
                }

                QJsonObject rootObj = doc.object();
                // up
                QJsonObject upObj = rootObj.value("up").toObject();
                imgName1 = upObj.value("Name").toString();
                imgPath1 = dir.absoluteFilePath(imgName1);
                QJsonArray upCoordiArray = upObj.value("Coordi").toArray();
                for (int i = 0; i < upCoordiArray.count(); i++) {
                    QJsonArray onePoint = upCoordiArray.at(i).toArray();
                    upMarkCoordiVec.push_back(QPointF(onePoint.at(0).toDouble(), onePoint.at(1).toDouble()));
                }

                // down
                QJsonObject downObj = rootObj.value("down").toObject();
                imgName2 = downObj.value("Name").toString();
                imgPath2 = dir.absoluteFilePath(imgName2);
                QJsonArray downCoordiArray = downObj.value("Coordi").toArray();
                for (int i = 0; i < downCoordiArray.count(); i++) {
                    QJsonArray onePoint = downCoordiArray.at(i).toArray();
                    downMarkCoordiVec.push_back(QPointF(onePoint.at(0).toDouble(), onePoint.at(1).toDouble()));
                }

                hasResFlag = true;
            }
        }


    }
    else
    {
        imgPath1 = fileList.at(0).filePath();
        imgPath2 = fileList.at(1).filePath();
        imgName1 = fileList.at(0).fileName();
        imgName2 = fileList.at(1).fileName();
    }

    qDebug() << imgPath1;
    qDebug() << imgPath2;

    // up
    QPixmap Image1(imgPath1);
    upImg = new QGraphicsPixmapItem();
    upImg->setPos(QPointF(0, 0));
    upImg->setPixmap(Image1);
    upScene->addItem(upImg);
    upView->fitInView(upScene->sceneRect(), Qt::KeepAspectRatio);

    miniUpImg = new QGraphicsPixmapItem();
    miniUpImg->setPos(QPointF(0, 0));
    miniUpImg->setPixmap(Image1);
    miniUpScene->addItem(miniUpImg);

    miniUpRect = new QGraphicsRectItem();
    miniUpRect->setPen(penRect);
    miniUpRect->setBrush(brushRect);
    miniUpScene->addItem(miniUpRect);
    miniUpView->fitInView(miniUpScene->sceneRect(), Qt::KeepAspectRatio);


    // down
    QPixmap Image2(imgPath2);
    downImg = new QGraphicsPixmapItem();
    downImg->setPos(QPointF(0, 0));
    downImg->setPixmap(Image2);
    downScene->addItem(downImg);
    downView->fitInView(downScene->sceneRect(), Qt::KeepAspectRatio);

    miniDownImg = new QGraphicsPixmapItem();
    miniDownImg->setPos(QPointF(0, 0));
    miniDownImg->setPixmap(Image2);
    miniDownScene->addItem(miniDownImg);

    miniDownRect = new QGraphicsRectItem();
    miniDownRect->setPen(penRect);
    miniDownRect->setBrush(brushRect);
    miniDownScene->addItem(miniDownRect);
    miniDownView->fitInView(miniDownScene->sceneRect(), Qt::KeepAspectRatio);


    if (hasResFlag == true)
    {
        RestorePoints();
    }


    firstRun = false;
}


void AnnoTool::resizeEvent(QResizeEvent *event)
{
    // up
    upView->fitInView(upScene->sceneRect(), Qt::KeepAspectRatio);
    miniUpView->fitInView(miniUpScene->sceneRect(), Qt::KeepAspectRatio);

    // down
    downView->fitInView(downScene->sceneRect(), Qt::KeepAspectRatio);
    miniDownView->fitInView(miniDownScene->sceneRect(), Qt::KeepAspectRatio);
}


void AnnoTool::MiniUpSceneDrawRect(QRectF visSceneRect)
{
    QRectF miniSceneRect = miniUpScene->sceneRect();
    if (miniSceneRect.contains(visSceneRect))
    {
        miniUpRect->setRect(visSceneRect);
        miniUpRect->setVisible(true);
    }
    else
    {
        miniUpRect->setVisible(false);
    }
}


void AnnoTool::DrawUpMark(QPointF pos)
{
    // up
    MainMark *mark = new MainMark();
    mark->setPos(pos);
    upScene->addItem(mark);
    upMainMarkVec.push_back(mark);

    // up mini
    MiniMark *miniMark = new MiniMark();
    miniMark->setPos(pos);
    miniUpScene->addItem(miniMark);
    upMiniMarkVec.push_back(miniMark);

    // ccordi
    upMarkCoordiVec.push_back(pos);
    QString s = '(' + QString::number(pos.x()) + " , " + QString::number(pos.y()) + ')';

    upPointTable->insertRow(upPointTable->rowCount());
    upPointTable->setItem(upPointTable->rowCount()-1, 0, new QTableWidgetItem(s));
}


void AnnoTool::MiniDownSceneDrawRect(QRectF visSceneRect)
{
    QRectF miniSceneRect = miniDownScene->sceneRect();
    if (miniSceneRect.contains(visSceneRect))
    {
        miniDownRect->setRect(visSceneRect);
        miniDownRect->setVisible(true);
    }
    else
    {
        miniDownRect->setVisible(false);
    }
}


void AnnoTool::DrawDownMark(QPointF pos)
{
    // down
    MainMark *mark = new MainMark();
    mark->setPos(pos);
    downScene->addItem(mark);
    downMainMarkVec.push_back(mark);

    // down mini
    MiniMark *miniMark = new MiniMark();
    miniMark->setPos(pos);
    miniDownScene->addItem(miniMark);
    downMiniMarkVec.push_back(miniMark);

    // ccordi
    downMarkCoordiVec.push_back(pos);
    QString s = '(' + QString::number(pos.x()) + " , " + QString::number(pos.y()) + ')';
    //qDebug() << s;
    downPointTable->insertRow(downPointTable->rowCount());
    downPointTable->setItem(downPointTable->rowCount() - 1, 0, new QTableWidgetItem(s));
}


void AnnoTool::SelectPointOnTwoViews(int row, int column)
{
    QObject* obj = sender();
    if (obj == qobject_cast<QObject *>(upPointTable))
    {
        QPointF upChosenPoint = upMarkCoordiVec[row];
        upView->CenterOnPos(upChosenPoint);

        if (upPreSelectedPoint != -1)
        {
            upMainMarkVec[upPreSelectedPoint]->ResetPen();
            upMiniMarkVec[upPreSelectedPoint]->ResetPenBrush();

        }
        upMainMarkVec[row]->SetHighlightPen();
        upMiniMarkVec[row]->SetHighlightPenBrush();
        upPreSelectedPoint = row;


        // down
        if (downPreSelectedPoint != -1)
        {
            downMainMarkVec[downPreSelectedPoint]->ResetPen();
            downMiniMarkVec[downPreSelectedPoint]->ResetPenBrush();
        }
        if (downPointTable->rowCount() >= row + 1)
        {
            downPointTable->setCurrentCell(row, 0);

            QPointF downChosenPoint = downMarkCoordiVec[row];
            downView->CenterOnPos(downChosenPoint);

            downMainMarkVec[row]->SetHighlightPen();
            downMiniMarkVec[row]->SetHighlightPenBrush();
            downPreSelectedPoint = row;
        }

    }
    else
    {
        QPointF downChosenPoint = downMarkCoordiVec[row];
        downView->CenterOnPos(downChosenPoint);

        if (downPreSelectedPoint != -1)
        {
            downMainMarkVec[downPreSelectedPoint]->ResetPen();
            downMiniMarkVec[downPreSelectedPoint]->ResetPenBrush();
        }
        downMainMarkVec[row]->SetHighlightPen();
        downMiniMarkVec[row]->SetHighlightPenBrush();
        downPreSelectedPoint = row;

        //up
        if (upPreSelectedPoint != -1)
        {
            upMainMarkVec[upPreSelectedPoint]->ResetPen();
            upMiniMarkVec[upPreSelectedPoint]->ResetPenBrush();
        }
        if (upPointTable->rowCount() >= row + 1)
        {
            upPointTable->setCurrentCell(row, 0);

            QPointF upChosenPoint = upMarkCoordiVec[row];
            upView->CenterOnPos(upChosenPoint);

            upMainMarkVec[row]->SetHighlightPen();
            upMiniMarkVec[row]->SetHighlightPenBrush();
            upPreSelectedPoint = row;
        }

    }
}


void AnnoTool::DeletePointOnTwoViews(QString senderTableName)
{

    qDebug() << senderTableName;

    if (senderTableName == "up")
    {
        QItemSelectionModel *selectionModel = upPointTable->selectionModel();
        QModelIndexList selectedRows = selectionModel->selectedRows();
        if (selectedRows.size() > 0)
        {
            int rowIdx = upPointTable->currentRow();
            upPointTable->removeRow(rowIdx);

            upScene->removeItem(upMainMarkVec[rowIdx]);
            upMainMarkVec.erase(upMainMarkVec.begin() + rowIdx);

            miniUpScene->removeItem(upMiniMarkVec[rowIdx]);
            upMiniMarkVec.erase(upMiniMarkVec.begin() + rowIdx);

            upMarkCoordiVec.erase(upMarkCoordiVec.begin() + rowIdx);

            if (upPreSelectedPoint == rowIdx)
            {
                upPreSelectedPoint = -1;
            }
            //down
            QItemSelectionModel *selectionModel2 = downPointTable->selectionModel();
            QModelIndexList selectedRows2 = selectionModel2->selectedRows();

            if (selectedRows2.size() > 0 || downPointTable->rowCount() >= rowIdx + 1)
            {
                downPointTable->removeRow(rowIdx);

                downScene->removeItem(downMainMarkVec[rowIdx]);
                downMainMarkVec.erase(downMainMarkVec.begin() + rowIdx);

                miniDownScene->removeItem(downMiniMarkVec[rowIdx]);
                downMiniMarkVec.erase(downMiniMarkVec.begin() + rowIdx);

                downMarkCoordiVec.erase(downMarkCoordiVec.begin() + rowIdx);

                if (downPreSelectedPoint == rowIdx)
                {
                    downPreSelectedPoint = -1;
                }

            }
        }
    }
    else
    {
        QItemSelectionModel *selectionModel = downPointTable->selectionModel();
        QModelIndexList selectedRows = selectionModel->selectedRows();
        if (selectedRows.size() > 0)
        {
            int rowIdx = downPointTable->currentRow();
            downPointTable->removeRow(rowIdx);

            downScene->removeItem(downMainMarkVec[rowIdx]);
            downMainMarkVec.erase(downMainMarkVec.begin() + rowIdx);

            miniDownScene->removeItem(downMiniMarkVec[rowIdx]);
            downMiniMarkVec.erase(downMiniMarkVec.begin() + rowIdx);

            downMarkCoordiVec.erase(downMarkCoordiVec.begin() + rowIdx);

            if (downPreSelectedPoint == rowIdx)
            {
                downPreSelectedPoint = -1;
            }


            //up
            QItemSelectionModel *selectionModel2 = upPointTable->selectionModel();
            QModelIndexList selectedRows2 = selectionModel2->selectedRows();

            if (selectedRows2.size() > 0 || upPointTable->rowCount() >= rowIdx + 1)
            {
                upPointTable->removeRow(rowIdx);

                upScene->removeItem(upMainMarkVec[rowIdx]);
                upMainMarkVec.erase(upMainMarkVec.begin() + rowIdx);

                miniUpScene->removeItem(upMiniMarkVec[rowIdx]);
                upMiniMarkVec.erase(upMiniMarkVec.begin() + rowIdx);

                upMarkCoordiVec.erase(upMarkCoordiVec.begin() + rowIdx);

                if (upPreSelectedPoint == rowIdx)
                {
                    upPreSelectedPoint = -1;
                }

            }
        }
    }

}


void AnnoTool::SaveResults()
{
    // up image
    QJsonArray upPointsCoordiArray;
    for (int i = 0; i < upMarkCoordiVec.size(); i++)
    {
        QJsonArray tempPointArray;
        tempPointArray.append(upMarkCoordiVec[i].x());
        tempPointArray.append(upMarkCoordiVec[i].y());
        upPointsCoordiArray.append(tempPointArray);
    }
    QJsonObject upObj;
    upObj.insert("Name", imgName1);
    upObj.insert("Coordi", upPointsCoordiArray);

    // down image
    QJsonArray downPointsCoordiArray;
    for (int i = 0; i < downMarkCoordiVec.size(); i++)
    {
        QJsonArray tempPointArray;
        tempPointArray.append(downMarkCoordiVec[i].x());
        tempPointArray.append(downMarkCoordiVec[i].y());
        downPointsCoordiArray.append(tempPointArray);
    }
    QJsonObject downObj;
    downObj.insert("Name", imgName2);
    downObj.insert("Coordi", downPointsCoordiArray);


    // save
    QJsonObject rootObject; // root
    rootObject.insert("up", upObj);
    rootObject.insert("down", downObj);

    QJsonDocument doc;
    doc.setObject(rootObject);

    QFile file(imgFolderPath + "/MatchingPointsCoordinates.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) 
    {
        qDebug() << "can't open json error!";
        return;
    }

    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();
}


void AnnoTool::RestorePoints()
{
    // *************** up *****************
    for (int i = 0; i < upMarkCoordiVec.size(); i++)
    {
        QPointF pos = upMarkCoordiVec[i];
        // up
        MainMark *mark = new MainMark();
        mark->setPos(pos);
        upScene->addItem(mark);
        upMainMarkVec.push_back(mark);

        // up mini
        MiniMark *miniMark = new MiniMark();
        miniMark->setPos(pos);
        miniUpScene->addItem(miniMark);
        upMiniMarkVec.push_back(miniMark);

        // ccordi
        QString s = '(' + QString::number(pos.x()) + " , " + QString::number(pos.y()) + ')';
        qDebug() << s;
        upPointTable->insertRow(upPointTable->rowCount());
        upPointTable->setItem(upPointTable->rowCount() - 1, 0, new QTableWidgetItem(s));
    }

    // *************** down *****************
    for (int i = 0; i < downMarkCoordiVec.size(); i++)
    {
        QPointF pos = downMarkCoordiVec[i];
        // down
        MainMark *mark = new MainMark();
        mark->setPos(pos);
        downScene->addItem(mark);
        downMainMarkVec.push_back(mark);

        // down mini
        MiniMark *miniMark = new MiniMark();
        miniMark->setPos(pos);
        miniDownScene->addItem(miniMark);
        downMiniMarkVec.push_back(miniMark);

        // ccordi
        QString s = '(' + QString::number(pos.x()) + " , " + QString::number(pos.y()) + ')';
        qDebug() << s;
        downPointTable->insertRow(downPointTable->rowCount());
        downPointTable->setItem(downPointTable->rowCount() - 1, 0, new QTableWidgetItem(s));
    }

}
