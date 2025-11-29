#include "levelmaker.h"

#include <QDebug>
#include <QMessageBox>


LevelMaker::LevelMaker(QWidget *parent, int widthCellsCnt, int heightCellsCnt)
    : QWidget(parent), widthCellsCount(widthCellsCnt), heightCellsCount(heightCellsCnt),
    gameStorage(new GameStorage()),
    imagesManager(new ImagesManager()),
    jsonManager(new JsonManager()),
    gameField(new GameField(this, gameStorage, widthCellsCnt, heightCellsCnt, *imagesManager)),
    objectPanel(new ObjectPanel(this, *imagesManager)),
    tankSelectedFlag(false), wallSelectedFlag(false), deleteSelectedFlag(false), rotateSelectedFlag(false)
{
    levelMakerController = new LevelMakerController(gameStorage, this);

    mainLay = new QHBoxLayout(this);
    mainLay->addWidget(gameField);
    mainLay->addWidget(objectPanel);

    connect(this, &LevelMaker::resizePlusSignal, gameField, &GameField::resizePlus);
    connect(this, &LevelMaker::resizeMinusSignal, gameField, &GameField::resizeMinus);

    connect(objectPanel, &ObjectPanel::onTankObjectClicked, this, &LevelMaker::selectTank);
    connect(objectPanel, &ObjectPanel::onWallObjectClicked, this, &LevelMaker::selectWall);
    connect(objectPanel, &ObjectPanel::onClearCellClicked, this, &LevelMaker::selectDelete);
    connect(objectPanel, &ObjectPanel::onRotateClicked, this, &LevelMaker::selectRotate);
    connect(objectPanel, &ObjectPanel::onSavePresetClicked, this, &LevelMaker::savePreset);

    connect(gameField, &GameField::cellClicked, this, &LevelMaker::onCellClicked);
    connect(levelMakerController, &LevelMakerController::gameStorageChanged, this, &LevelMaker::onGameStateChanged);
}

void LevelMaker::onCellClicked(int row, int col)
{
    if (tankSelectedFlag) {
        levelMakerController->placeTank(row, col);
    } else if (wallSelectedFlag) {
        levelMakerController->placeWall(row, col);
    } else if (deleteSelectedFlag) {
        levelMakerController->deleteObject(row, col);
    } else if (rotateSelectedFlag) {
        levelMakerController->rotateTank(row, col);
    }
}

void LevelMaker::onGameStateChanged()
{
    gameField->updateImages();
}

void LevelMaker::savePreset()
{
    if (jsonManager->GameStorageToJson(levelMakerController->getGameStorage(), widthCellsCount, heightCellsCount)) {
        QMessageBox::information(this, "Сохранение карты", "Карта была упешно сохранена");
    }
    emit mapSaved();
}

void LevelMaker::resizePlus()
{
    emit resizePlusSignal();
    updateWindowSize();
}

void LevelMaker::resizeMinus()
{
    emit resizeMinusSignal();
    updateWindowSize();
}

void LevelMaker::selectTank()
{
    disableAllSelectedFlags();
    tankSelectedFlag = true;
}

void LevelMaker::selectWall()
{
    disableAllSelectedFlags();
    wallSelectedFlag = true;
}

void LevelMaker::selectDelete()
{
    disableAllSelectedFlags();
    deleteSelectedFlag = true;
}

void LevelMaker::selectRotate()
{
    disableAllSelectedFlags();
    rotateSelectedFlag = true;
}

void LevelMaker::updateWindowSize()
{
    int cellSize = gameField->getCellSize();
    int fieldWidth = gameField->getWidthCellsCount() * cellSize;
    int fieldHeight = gameField->getHeightCellsCount() * cellSize;

    int panelWidth = 150;
    int panelHeight = fieldHeight;

    int menuBarHeight = 25;

    gameField->setFixedSize(fieldWidth, fieldHeight);
    objectPanel->setFixedSize(panelWidth, panelHeight);

    int totalWidth = fieldWidth + panelWidth + mainLay->spacing() + mainLay->contentsMargins().left() + mainLay->contentsMargins().right();
    int totalHeight = fieldHeight + mainLay->contentsMargins().top() + mainLay->contentsMargins().bottom();

    setFixedSize(totalWidth, totalHeight);

    QWidget* mainWindow = window();
    if (mainWindow) {
        mainWindow->setFixedSize(totalWidth, totalHeight + menuBarHeight);
    }
}

LevelMaker::~LevelMaker()
{
    if (gameField) {
        mainLay->removeWidget(gameField);
        delete gameField;
        gameField = nullptr;
    }

    if (objectPanel) {
        mainLay->removeWidget(objectPanel);
        delete objectPanel;
        objectPanel = nullptr;
    }

    if (gameStorage) {
        delete gameStorage;
        gameStorage = nullptr;
    }

    if (imagesManager) {
        delete imagesManager;
        imagesManager = nullptr;
    }

    if (jsonManager) {
        delete jsonManager;
        jsonManager = nullptr;
    }

    if (mainLay) {
        QLayoutItem* item;
        while ((item = mainLay->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
        delete mainLay;
        mainLay = nullptr;
    }
}

void LevelMaker::disableAllSelectedFlags()
{
    tankSelectedFlag = false;
    wallSelectedFlag = false;
    deleteSelectedFlag = false;
    rotateSelectedFlag = false;
}
