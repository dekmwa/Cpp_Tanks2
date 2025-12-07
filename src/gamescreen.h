#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "gamestorage.h"
#include "imagesmanager.h"
#include "gamescreencontroller.h"
#include "gamefield.h"
#include "actionpanel.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QCloseEvent>

class GameScreen : public QWidget
{
    Q_OBJECT

public:
    GameScreen(QWidget *parent, GameStorage *gs, int widthCount, int heightCount);
    ~GameScreen();

public slots:
    void resizePlus();
    void resizeMinus();

private:
    GameController *gameController;
    ImagesManager *imagesManager;
    QHBoxLayout *mainLay;
    GameField *gameField;
    ActionPanel *actionPanel;

private:
    void updateWindowSize();

private slots:
    void onGameStateChanged(NewFrameObjects newFrame);
    void onHighlightCell(int x, int y);

signals:
    void resizePlusSignal();
    void resizeMinusSignal();
    void inactiveActionPanel();
    void activeActionPanel();
    void highlightCell(int x, int y);
    void removeLastHighlightCell();
};

#endif // GAMESCREEN_H
