#include "gamescreencontroller.h"
#include <QDebug>

GameController::GameController(GameStorage *gs, int widthCount, int heightCount, QObject* parent)
    : QObject(), gameStorage(gs), m_currentTankIndex(0), fieldWidth(widthCount), fieldHeight(heightCount)
{
}

GameController::~GameController()
{
}

void GameController::processAction(Action action)
{
    switch (action) {
    case Action::FORWARD: moveForward(); break;
    case Action::BACKWARD: moveBackward(); break;
    case Action::TURNLEFT: turnLeft(); break;
    case Action::TURNRIGHT: turnRight(); break;
    case Action::SHOT: break;
    }

    makeNewFrame();

    if (action == Action::SHOT)
        shot();

    changeIndexes();
    emit highlightCell(gameStorage->getTankByIndex(m_currentTankIndex)->getCoordinateX(), gameStorage->getTankByIndex(m_currentTankIndex)->getCoordinateY());
}

void GameController::makeNewFrame()
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

void GameController::shot()
{
    Tank *currentTank = gameStorage->getTankByIndex(m_currentTankIndex);

    switch(currentTank->getDirection()) {
    case Direction::UP: {
        int currentCheckY = currentTank->getCoordinateY() - 1;
        for (int i = 0; i < currentTank->getCoordinateY(); i++) {
            if (gameStorage->objectOnCoordinatesExist(currentTank->getCoordinateX(), currentCheckY)) {
                gameStorage->deleteExistObjectOnCoordinates(currentTank->getCoordinateX(), currentCheckY);
                return;
            }
            emit drawShot(currentTank->getCoordinateX(), currentCheckY, Direction::UP);
            currentCheckY--;
        }
        break;
    }
    case Direction::DOWN: {
        int currentCheckY = currentTank->getCoordinateY() + 1;
        for (int i = 1; i < fieldHeight - currentTank->getCoordinateY(); i++) {
            if (gameStorage->objectOnCoordinatesExist(currentTank->getCoordinateX(), currentCheckY)) {
                gameStorage->deleteExistObjectOnCoordinates(currentTank->getCoordinateX(), currentCheckY);
                return;
            }
            emit drawShot(currentTank->getCoordinateX(), currentCheckY, Direction::DOWN);
            currentCheckY++;
        }
        break;
    }
    case Direction::RIGHT: {
        int currentCheckX = currentTank->getCoordinateX() + 1;
        for (int i = 1; i < fieldWidth - currentTank->getCoordinateX(); i++) {
            if (gameStorage->objectOnCoordinatesExist(currentCheckX, currentTank->getCoordinateY())) {
                gameStorage->deleteExistObjectOnCoordinates(currentCheckX, currentTank->getCoordinateY());
                return;
            }
            emit drawShot(currentCheckX, currentTank->getCoordinateY(), Direction::RIGHT);
            currentCheckX++;
        }
        break;
    }
    case Direction::LEFT: {
        int currentCheckX = currentTank->getCoordinateX() - 1;
        for (int i = 0; i < currentTank->getCoordinateX(); i++) {
            if (gameStorage->objectOnCoordinatesExist(currentCheckX, currentTank->getCoordinateY())) {
                gameStorage->deleteExistObjectOnCoordinates(currentCheckX, currentTank->getCoordinateY());
                return;
            }
            emit drawShot(currentCheckX, currentTank->getCoordinateY(), Direction::LEFT);
            currentCheckX--;
        }
        break;
    }
    }
}

void GameController::moveForward()
{
    Tank *currentTank = gameStorage->getTankByIndex(m_currentTankIndex);
    Tank tankCopy(*currentTank);

    tankCopy.forward();

    if (tankCopy.getCoordinateX() < 0 || tankCopy.getCoordinateX() >= fieldWidth
        || tankCopy.getCoordinateY() < 0 || tankCopy.getCoordinateY() >= fieldHeight) {
        return;
    }
    if (gameStorage->objectOnCoordinatesExist(tankCopy.getCoordinateX(), tankCopy.getCoordinateY())) {
        return;
    }

    currentTank->forward();
}

void GameController::moveBackward()
{
    Tank *currentTank = gameStorage->getTankByIndex(m_currentTankIndex);
    Tank tankCopy(*currentTank);

    tankCopy.backward();

    if (tankCopy.getCoordinateX() < 0 || tankCopy.getCoordinateX() >= fieldWidth
        || tankCopy.getCoordinateY() < 0 || tankCopy.getCoordinateY() >= fieldHeight) {
        return;
    }
    if (gameStorage->objectOnCoordinatesExist(tankCopy.getCoordinateX(), tankCopy.getCoordinateY())) {
        return;
    }

    currentTank->backward();
}

void GameController::turnLeft()
{
    Tank *currentTank = gameStorage->getTankByIndex(m_currentTankIndex);
    currentTank->turnLeft();
}

void GameController::turnRight()
{
    Tank *currentTank = gameStorage->getTankByIndex(m_currentTankIndex);
    currentTank->turnRight();
}

void GameController::changeIndexes()
{
    if (m_currentTankIndex + 1 >= gameStorage->getTanksCount())
    {
        m_currentTankIndex = 0;
    } else
    {
        m_currentTankIndex++;
    }
}
