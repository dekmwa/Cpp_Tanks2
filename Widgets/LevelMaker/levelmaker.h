#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#include "../../Utils/GameStorage/gamestorage.h"
#include "./levelmakercontroller.h"
#include "../GameField/gamefield.h"
#include "../ObjectPanel/objectpanel.h"
#include "../../Utils/ImagesManager/imagesmanager.h"
#include "../../Utils/JsonManager/jsonmanager.h"

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
    void onGameStateChanged();

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
