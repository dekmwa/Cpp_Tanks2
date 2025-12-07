#ifndef LEVELMAKERCONTROLLER_H
#define LEVELMAKERCONTROLLER_H

#include "../../Utils/GameStorage/gamestorage.h"
#include "../../src/NewFrameObjects.h"

#include <QObject>

class LevelMakerController : public QObject
{
    Q_OBJECT

public:
    LevelMakerController(GameStorage* storage, QObject* parent = nullptr);

    void placeTank(int row, int col);
    void placeWall(int row, int col);
    void deleteObject(int row, int col);
    void rotateTank(int row, int col);

    GameStorage* getGameStorage() const { return gameStorage; }

    void makeNewFrame();

private:
    GameStorage* gameStorage;

signals:
    void gameStorageChanged(NewFrameObjects newFrame);
};

#endif // LEVELMAKERCONTROLLER_H
