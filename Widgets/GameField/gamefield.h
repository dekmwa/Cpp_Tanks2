#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "../../Utils/GameStorage/gamestorage.h"
#include "../../Utils/ImagesManager/imagesmanager.h"

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
    GameField(QWidget *parent, GameStorage *gs, int widthCellsCnt, int heightCellsCnt, ImagesManager &imgManager);
    ~GameField();

    int getWidthCellsCount();
    int getHeightCellsCount();
    int getCellSize();

private:
    GameStorage *gameStorage;
    ImagesManager *imagesManager;
    int widthCellsCount;
    int heightCellsCount;
    std::vector<std::vector<QPushButton*>> fieldCells;
    QGridLayout *gridLayout;
    int cellSize;
    LastHighlightCell *lastHighlightCell;

public slots:
    void resizePlus();
    void resizeMinus();
    void updateImages();

    void highlightCell(int x, int y);
    void removeLastHighlightCell();
    void drawBulletCell(int x, int y, Direction direction);

signals:
    void cellClicked(int i, int j);
};

#endif // GAMEFIELD_H
