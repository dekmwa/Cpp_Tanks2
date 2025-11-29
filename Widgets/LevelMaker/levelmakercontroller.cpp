#include "./levelmakercontroller.h"

LevelMakerController::LevelMakerController(GameStorage* storage, QObject* parent)
    : QObject(parent), gameStorage(storage)
{
}

void LevelMakerController::placeTank(int col, int row)
{
    gameStorage->deleteExistObjectOnCoordinates(row, col);
    gameStorage->pushTank(new Tank(row, col, Direction::UP));
    emit gameStorageChanged();
}

void LevelMakerController::placeWall(int col, int row)
{
    gameStorage->deleteExistObjectOnCoordinates(row, col);
    gameStorage->pushWall(new Wall(row, col));
    emit gameStorageChanged();
}

void LevelMakerController::deleteObject(int col, int row)
{
    gameStorage->deleteExistObjectOnCoordinates(row, col);
    emit gameStorageChanged();
}

void LevelMakerController::rotateTank(int col, int row)
{
    if (gameStorage->tankOnCoordinatesExist(row, col))
    {
        int index = gameStorage->getTankIndexByCoordinates(row, col);
        Tank *tank = gameStorage->getTankByIndex(index);
        tank->turnRight();
        emit gameStorageChanged();
    }
}
