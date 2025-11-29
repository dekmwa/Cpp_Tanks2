#include "gamescreen.h"
#include <QEventLoop>

GameScreen::GameScreen(QWidget *parent, GameStorage *gs, int widthCount, int heightCount) : QWidget(parent),
    mainLay(new QHBoxLayout(this)), imagesManager(new ImagesManager()),
    gameField(new GameField(this, gs, widthCount, heightCount, *imagesManager)), actionPanel(new ActionPanel(this))
{
    gameController = new GameController(gs, widthCount, heightCount, this);

    mainLay->addWidget(gameField);
    mainLay->addWidget(actionPanel);

    connect(this, &GameScreen::activeActionPanel, actionPanel, &ActionPanel::activeAllButtons);

    connect(this, &GameScreen::highlightCell, gameField, &GameField::highlightCell);
    connect(this, &GameScreen::removeLastHighlightCell, gameField, &GameField::removeLastHighlightCell);
    connect(this, &GameScreen::resizePlusSignal, gameField, &GameField::resizePlus);
    connect(this, &GameScreen::resizeMinusSignal, gameField, &GameField::resizeMinus);

    connect(actionPanel, &ActionPanel::actionClicked, gameController, &GameController::processAction);
    connect(gameController, &GameController::gameStorageChanged, this, &GameScreen::onGameStateChanged);
    connect(gameController, &GameController::highlightCell, this, &GameScreen::onHighlightCell);

    emit highlightCell(gs->getTankByIndex(0)->getCoordinateX(), gs->getTankByIndex(0)->getCoordinateY());

    connect(gameController, &GameController::drawShot, gameField, &GameField::drawBulletCell);
}

void GameScreen::onGameStateChanged()
{
    gameField->updateImages();
}

void GameScreen::onHighlightCell(int x, int y)
{
    emit highlightCell(x, y);
}

void GameScreen::updateWindowSize()
{
    int cellSize = gameField->getCellSize();
    int fieldWidth = gameField->getWidthCellsCount() * cellSize;
    int fieldHeight = gameField->getHeightCellsCount() * cellSize;

    int panelWidth = 150;
    int panelHeight = fieldHeight;

    int menuBarHeight = 25;

    gameField->setFixedSize(fieldWidth, fieldHeight);
    actionPanel->setFixedSize(panelWidth, panelHeight);

    int totalWidth = fieldWidth + panelWidth + mainLay->spacing() + mainLay->contentsMargins().left() + mainLay->contentsMargins().right();
    int totalHeight = fieldHeight + mainLay->contentsMargins().top() + mainLay->contentsMargins().bottom();

    setFixedSize(totalWidth, totalHeight);

    QWidget* mainWindow = window();
    if (mainWindow) {
        mainWindow->setFixedSize(totalWidth, totalHeight + menuBarHeight);
    }
}

GameScreen::~GameScreen()
{
    if (gameField) {
        delete gameField;
        gameField = nullptr;
    }

    if (actionPanel) {
        delete actionPanel;
        actionPanel = nullptr;
    }

    if (imagesManager) {
        delete imagesManager;
        imagesManager = nullptr;
    }

    if (mainLay) {
        delete mainLay;
        mainLay = nullptr;
    }
}

void GameScreen::resizePlus()
{
    emit resizePlusSignal();
    updateWindowSize();
}

void GameScreen::resizeMinus()
{
    emit resizeMinusSignal();
    updateWindowSize();
}
