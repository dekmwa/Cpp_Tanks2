#include "./levelmakercontroller.h"

LevelMakerController::LevelMakerController(GameStorage* storage, QObject* parent)
    : QObject(parent), gameStorage(storage)
{
}

void LevelMakerController::placeTank(int col, int row)
{
    gameStorage->deleteExistObjectOnCoordinates(row, col);
    gameStorage->pushTank(new Tank(row, col, Direction::UP));
    makeNewFrame();
}

void LevelMakerController::placeWall(int col, int row)
{
    gameStorage->deleteExistObjectOnCoordinates(row, col);
    gameStorage->pushWall(new Wall(row, col));
    makeNewFrame();
}

void LevelMakerController::deleteObject(int col, int row)
{
    gameStorage->deleteExistObjectOnCoordinates(row, col);
    makeNewFrame();
}

void LevelMakerController::rotateTank(int col, int row)
{
    if (gameStorage->tankOnCoordinatesExist(row, col))
    {
        int index = gameStorage->getTankIndexByCoordinates(row, col);
        Tank *tank = gameStorage->getTankByIndex(index);
        tank->turnRight();
        makeNewFrame();
    }
}

void LevelMakerController::makeNewFrame()
{
    NewFrameObjects newFrame;

    const auto& tankPointers = gameStorage->getTanksVector();
    newFrame.tanks.reserve(tankPointers.size());
    for (const Tank* tankPtr : tankPointers) {
        if (tankPtr) {
            newFrame.tanks.push_back(*tankPtr);
        }
    }

    const auto& wallPointers = gameStorage->getWallsVector();
    newFrame.walls.reserve(wallPointers.size());
    for (const Wall* wallPtr : wallPointers) {
        if (wallPtr) {
            newFrame.walls.push_back(*wallPtr);
        }
    }

    emit gameStorageChanged(newFrame);
}
