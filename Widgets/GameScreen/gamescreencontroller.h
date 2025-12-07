#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../../Utils/GameStorage/gamestorage.h"
#include "../ActionPanel/actionpanel.h"
#include "../../src/NewFrameObjects.h"

#include <QObject>


class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(GameStorage *gs, int widthCount, int heightCount, QObject* parent = nullptr);
    ~GameController();

    void processAction(Action action);
    void makeNewFrame();

    int getCurrentTankIndex() const { return m_currentTankIndex; }
    GameStorage* getGameStorage() const { return gameStorage; }

private:
    GameStorage *gameStorage;
    int m_currentTankIndex;
    int fieldWidth;
    int fieldHeight;

    void shot();
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void changeIndexes();

signals:
    void gameStorageChanged(NewFrameObjects newFrame);
    void highlightCell(int x, int y);
    void drawShot(int x, int y, Direction direction);
};

#endif // GAMECONTROLLER_H
