#ifndef GAME_H
#define GAME_H

#include "../Widgets/MainMenu/mainmenu.h"
#include "../Widgets/FieldSizeSelector/fieldsizeselector.h"
#include "../Widgets/LevelSelector/levelselector.h"
#include "../Widgets/LevelMaker/levelmaker.h"
#include "../Widgets/GameScreen/gamescreen.h"

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
