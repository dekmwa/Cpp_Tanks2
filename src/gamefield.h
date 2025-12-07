#pragma once
#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "imagesmanager.h"
#include "NewFrameObjects.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>


struct LastHighlightCell {
    int x;
    int y;
};

class GameField : public QWidget
{
    Q_OBJECT

public:
    GameField(QWidget *parent, int widthCellsCnt, int heightCellsCnt, ImagesManager &imgManager);
    ~GameField();

    int getWidthCellsCount();
    int getHeightCellsCount();
    int getCellSize();

private:
    ImagesManager *imagesManager;
    int widthCellsCount;
    int heightCellsCount;
    std::vector<std::vector<QPushButton*>> fieldCells;
    QGridLayout *gridLayout;
    int cellSize;
    LastHighlightCell *lastHighlightCell;
    NewFrameObjects lastFrame;

public slots:
    void resizePlus();
    void resizeMinus();
    void updateImages(NewFrameObjects newFrame);

    void highlightCell(int x, int y);
    void removeLastHighlightCell();
    void drawBulletCell(int x, int y, Direction direction);

signals:
    void cellClicked(int i, int j);
};

#endif // GAMEFIELD_H
