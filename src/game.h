#ifndef GAME_H
#define GAME_H

#include "mainmenu.h"
#include "fieldsizeselector.h"
#include "levelselector.h"
#include "levelmaker.h"
#include "gamescreen.h"

#include <QWidget>
#include <QStackedWidget>
#include <QMenuBar>


class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);

private:
    MainMenu *mainMenu;
    FieldSizeSelector *fieldSizeSelector;
    LevelSelector *levelSelector;
    LevelMaker *levelMaker;
    GameScreen *gameScreen;

    //JsonManager *jsonManager;

    QStackedWidget *stackedWidget;
    QMenuBar *menuBar;
    QVBoxLayout *mainLay;

private:
    void InitializeGameScreen(QString filepath);

private slots:
    void showMainMenu();
    void showFieldSizeSelector();
    void showLevelSelector();
    void initializeLevelMaker(int widthCount, int heightCount);

    void resizeWindowPlus();
    void resizeWindowMinus();

signals:
    void resizePlus();
    void resizeMinus();

    void jsonInvalid();
};

#endif // GAME_H
