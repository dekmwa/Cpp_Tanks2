#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#include "gamestorage.h"
#include "levelmakercontroller.h"
#include "gamefield.h"
#include "objectpanel.h"
#include "imagesmanager.h"
#include "jsonmanager.h"

#include <QWidget>
#include <QHBoxLayout>

class LevelMaker : public QWidget
{
    Q_OBJECT

public:
    LevelMaker(QWidget *parent, int widthCellsCnt, int heightCellsCnt);
    ~LevelMaker();

private:
    LevelMakerController* levelMakerController;
    ImagesManager *imagesManager;
    GameStorage *gameStorage;
    JsonManager *jsonManager;
    GameField *gameField;
    ObjectPanel *objectPanel;
    QHBoxLayout *mainLay;

    int widthCellsCount;
    int heightCellsCount;

    bool tankSelectedFlag;
    bool wallSelectedFlag;
    bool deleteSelectedFlag;
    bool rotateSelectedFlag;

    void updateWindowSize();
    void disableAllSelectedFlags();
    void savePreset();

private slots:
    void onCellClicked(int row, int col);
    void onGameStateChanged(NewFrameObjects newFrame);

public slots:
    void resizePlus();
    void resizeMinus();
    void selectTank();
    void selectWall();
    void selectDelete();
    void selectRotate();

signals:
    void resizePlusSignal();
    void resizeMinusSignal();
    void mapSaved();
};

#endif // LEVELMAKER_H
