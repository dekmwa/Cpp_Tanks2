#include "game.h"
#include "../Utils/JsonManager/jsonmanager.h"

#include <QDebug>
#include <QMessageBox>


Game::Game(QWidget *parent) : QWidget(parent), mainLay(new QVBoxLayout(this)), stackedWidget(new QStackedWidget(this)),
    menuBar(new QMenuBar(this)), mainMenu(new MainMenu(this)), fieldSizeSelector(new FieldSizeSelector(this)),
    levelSelector(new LevelSelector(this)),
    gameScreen(nullptr), levelMaker(nullptr)
{
    mainLay->setSpacing(0);
    mainLay->setContentsMargins(0, 0, 0, 0);
    mainLay->setAlignment(Qt::AlignTop);

    QAction *resizePlusAction = menuBar->addAction("размер +");
    QAction *resizeMinusAction = menuBar->addAction("размер -");
    QAction *backToMenuAction = menuBar->addAction("Выход в меню");

    // setStyleSheet(
    //     "QWidget {"
    //     "background-color: #ccd5ae;"
    //     "}"
    // );

    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(fieldSizeSelector);
    stackedWidget->addWidget(levelSelector);

    mainLay->addWidget(menuBar);
    mainLay->addWidget(stackedWidget);

    stackedWidget->setCurrentWidget(mainMenu);

    connect(mainMenu, &MainMenu::PlayClicked, this, &Game::showLevelSelector);
    connect(mainMenu, &MainMenu::LevelMakerClicked, this, &Game::showFieldSizeSelector);
    connect(levelSelector, &LevelSelector::filepath, this, &Game::InitializeGameScreen);
    connect(fieldSizeSelector, &FieldSizeSelector::validSizes, this, &Game::initializeLevelMaker);
    connect(resizePlusAction, &QAction::triggered, this, &Game::resizeWindowPlus);
    connect(resizeMinusAction, &QAction::triggered, this, &Game::resizeWindowMinus);
    connect(backToMenuAction, &QAction::triggered, this, &Game::showMainMenu);
}

void Game::InitializeGameScreen(QString filepath)
{
    JsonManager jsonManager;
    ValidationResult result = jsonManager.jsonFileIsValid(filepath);

    if (! result.isValid) {
        QMessageBox::information(this, "Валидация файла карты", result.errorMessage);
        return;
    }

    if (gameScreen == nullptr) {
        stackedWidget->removeWidget(gameScreen);
        delete gameScreen;
        gameScreen = nullptr;
    }

    GameStorage *gs = jsonManager.JsonToGameStorage(filepath);

    gameScreen = new GameScreen(this, gs, gs->getWidthCellsCount(), gs->getHeightCellsCount());
    stackedWidget->addWidget(gameScreen);
    stackedWidget->setCurrentWidget(gameScreen);
    connect(this, &Game::resizePlus, gameScreen, &GameScreen::resizePlus);
    connect(this, &Game::resizeMinus, gameScreen, &GameScreen::resizeMinus);
}

void Game::initializeLevelMaker(int widthCount, int heightCount)
{
    if (levelMaker == nullptr) {
        stackedWidget->removeWidget(levelMaker);
        delete levelMaker;
        levelMaker = nullptr;
    }

    levelMaker = new LevelMaker(this, widthCount, heightCount);
    stackedWidget->addWidget(levelMaker);
    stackedWidget->setCurrentWidget(levelMaker);
    connect(this, &Game::resizePlus, levelMaker, &LevelMaker::resizePlus);
    connect(this, &Game::resizeMinus, levelMaker, &LevelMaker::resizeMinus);
}

void Game::resizeWindowPlus()
{
    emit resizePlus();
}

void Game::resizeWindowMinus()
{
    emit resizeMinus();
}

void Game::showFieldSizeSelector()
{
    stackedWidget->setCurrentWidget(fieldSizeSelector);
}

void Game::showLevelSelector()
{
    stackedWidget->setCurrentWidget(levelSelector);
}

void Game::showMainMenu()
{
    stackedWidget->setCurrentWidget(mainMenu);

    QWidget* mainWindow = window();
    if (mainWindow) {
        mainWindow->setMinimumSize(0, 0);
        mainWindow->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        mainWindow->setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        mainWindow->resize(400, 300);
    }

    if (gameScreen) {
        stackedWidget->removeWidget(gameScreen);
        delete gameScreen;
        gameScreen = nullptr;
    }

    if (levelMaker) {
        stackedWidget->removeWidget(levelMaker);
        delete levelMaker;
        levelMaker = nullptr;
    }
}
