#include "gamefield.h"


GameField::GameField(QWidget *parent, GameStorage *gs, int widthCellsCnt, int heightCellsCnt, ImagesManager &imgManager)
    : QWidget(parent), gameStorage(gs), widthCellsCount(widthCellsCnt), heightCellsCount(heightCellsCnt), cellSize(50), imagesManager(&imgManager)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    fieldCells.resize(heightCellsCount);

    for (int i = 0; i < heightCellsCount; i++)
    {
        fieldCells[i].resize(widthCellsCount);

        for (int j = 0; j < widthCellsCount; j++)
        {
            fieldCells[i][j] = new QPushButton(this);
            fieldCells[i][j]->setFixedSize(cellSize, cellSize);
            fieldCells[i][j]->setFlat(true);
            fieldCells[i][j]->setStyleSheet(
                "border: 1px;"
                "margin: 0px;"
                "padding: 0px;"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                "stop:0 #E6D2B5, stop:1 #C19A6B);"
            );

            connect(fieldCells[i][j], &QPushButton::clicked, [this, i, j]()
                {
                    emit cellClicked(i, j);
                });
            gridLayout->addWidget(fieldCells[i][j], i, j);
        }
    }

    updateImages();
    lastHighlightCell = new LastHighlightCell();
}

void GameField::updateImages()
{
    for (int i = 0; i < heightCellsCount; i++) {
        for (int j = 0; j < widthCellsCount; j++) {
            fieldCells[i][j]->setIcon(QIcon());
            fieldCells[i][j]->setStyleSheet(
                "border: 1px;"
                "margin: 0px;"
                "padding: 0px;"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                "stop:0 #E6D2B5, stop:1 #C19A6B);"
                );
        }
    }

    for (int i = 0; i < gameStorage->getTanksCount(); i++) {
        Tank *currentTank = gameStorage->getTankByIndex(i);
        int row = currentTank->getCoordinateY();
        int coll = currentTank->getCoordinateX();
        QPixmap tankImg = imagesManager->getTankScaledImage(cellSize);
        QTransform transform;
        int angle = 0;

        switch(currentTank->getDirection()) {
        case Direction::UP: angle = 0; break;
        case Direction::RIGHT: angle = 90; break;
        case Direction::DOWN: angle = 180; break;
        case Direction::LEFT: angle = 270; break;
        }

        transform.rotate(angle);
        tankImg = tankImg.transformed(transform, Qt::SmoothTransformation);
        fieldCells[row][coll]->setIcon(QIcon(tankImg));
        fieldCells[row][coll]->setIconSize(QSize(cellSize, cellSize));
    }

    for (int i = 0; i < gameStorage->getWallsCount(); i++) {
        int row = gameStorage->getWallByIndex(i)->getCoordinateY();
        int coll = gameStorage->getWallByIndex(i)->getCoordinateX();
        QPixmap wallImg = imagesManager->getWallScaledImage(cellSize);

        fieldCells[row][coll]->setIcon(QIcon(wallImg));
        fieldCells[row][coll]->setIconSize(QSize(cellSize, cellSize));
    }

    //gameStorage->printStorageInfo();
}

void GameField::resizePlus()
{
    //qDebug() << "GameField  размер клеток: " << cellSize + 10;
    cellSize += 5;
    for (int i = 0; i < heightCellsCount; i++) {
        for (int j = 0; j < widthCellsCount; j++) {
            fieldCells[i][j]->setFixedSize(cellSize, cellSize);
        }
    }
    updateImages();
}

void GameField::resizeMinus()
{
    //qDebug() << "GameField  размер клеток: " << cellSize + 10;
    cellSize -= 5;
    for (int i = 0; i < heightCellsCount; i++) {
        for (int j = 0; j < widthCellsCount; j++) {
            fieldCells[i][j]->setFixedSize(cellSize, cellSize);
        }
    }
    updateImages();
}

void GameField::highlightCell(int x, int y)
{
    fieldCells[y][x]->setStyleSheet(
        "border: 1px;"
        "margin: 0px;"
        "padding: 0px;"
        "background-color: #90EE90;"
    );

    lastHighlightCell->x = x;
    lastHighlightCell->y = y;
}

void GameField::removeLastHighlightCell()
{
    fieldCells[lastHighlightCell->y][lastHighlightCell->x]->setStyleSheet(
        "border: 1px;"
        "margin: 0px;"
        "padding: 0px;"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #E6D2B5, stop:1 #C19A6B);"
    );

    qDebug() << "удалено выделение клетки " << "x" << lastHighlightCell->x << " y" << lastHighlightCell->y;
}

void GameField::drawBulletCell(int x, int y, Direction direction)
{
    QPixmap bulletScaled = imagesManager->getBulletScaledImage(cellSize);
    QTransform transform;
    int angle = 0;

    switch(direction) {
    case Direction::UP: angle = 0; break;
    case Direction::RIGHT: angle = 90; break;
    case Direction::DOWN: angle = 180; break;
    case Direction::LEFT: angle = 270; break;
    }

    transform.rotate(angle);
    bulletScaled = bulletScaled.transformed(transform, Qt::SmoothTransformation);
    fieldCells[y][x]->setIcon(QIcon(bulletScaled));
    fieldCells[y][x]->setIconSize(QSize(cellSize, cellSize));
}

GameField::~GameField() {
    for (int i = 0; i < heightCellsCount; i++) {
        for (int j = 0; j < widthCellsCount; j++) {
            if (fieldCells[i][j]) {
                fieldCells[i][j]->disconnect();
                disconnect(fieldCells[i][j], nullptr, nullptr, nullptr);
            }
        }
    }

    if (lastHighlightCell) {
        delete lastHighlightCell;
        lastHighlightCell = nullptr;
    }

    for (int i = 0; i < heightCellsCount; i++) {
        for (int j = 0; j < widthCellsCount; j++) {
            if (fieldCells[i][j]) {
                gridLayout->removeWidget(fieldCells[i][j]);
                delete fieldCells[i][j];
                fieldCells[i][j] = nullptr;
            }
        }
        fieldCells[i].clear();
    }
    fieldCells.clear();

    if (gridLayout) {
        QLayoutItem* item;
        while ((item = gridLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
        delete gridLayout;
        gridLayout = nullptr;
    }

    imagesManager = nullptr;
    gameStorage = nullptr;

    //qDebug() << "=== Destructor called: " << this->metaObject()->className() << "===";
}

int GameField::getWidthCellsCount()
{
    return this->widthCellsCount;
}

int GameField::getHeightCellsCount()
{
    return this->heightCellsCount;
}

int GameField::getCellSize()
{
    return this->cellSize;
}
