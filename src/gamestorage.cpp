#include "gamestorage.h"

#include <QDebug>


GameStorage::GameStorage() : widthCellsCount(0), heightCellsCount(0)
{}

void GameStorage::setTanksVector(std::vector<Tank*> newTanks) {
    this->tanks = newTanks;
}

void GameStorage::setWallsVector(std::vector<Wall*> newWalls) {
    this->walls = newWalls;
}

std::vector<Tank*> GameStorage::getTanksVector() {
    return this->tanks;
}

std::vector<Wall*> GameStorage::getWallsVector() {
    return this->walls;
}

void GameStorage::pushTank(Tank *tank) {
    this->tanks.push_back(tank);
}

void GameStorage::pushWall(Wall *wall) {
    this->walls.push_back(wall);
}

Tank* GameStorage::getTankByIndex(int index) {
    return this->tanks[index];
}

Wall* GameStorage::getWallByIndex(int index) {
    return this->walls[index];
}

int GameStorage::getTanksCount()
{
    return this->tanks.size();
}

int GameStorage::getWallsCount()
{
    return this->walls.size();
}

int GameStorage::getWidthCellsCount(){ return widthCellsCount; }
int GameStorage::getHeightCellsCount(){ return heightCellsCount; }
void GameStorage::setWidthCellsCount(int count){ this->widthCellsCount = count; }
void GameStorage::setHeightCellsCount(int count){ this->heightCellsCount = count; }

bool GameStorage::tankOnCoordinatesExist(int x, int y)
{
    for (int i = 0; i < getTanksCount(); i++)
    {
        if (tanks[i]->getCoordinateX() == x && tanks[i]->getCoordinateY() == y)
        {
            return true;
        }
    }
    return false;
}

bool GameStorage::wallOnCoordinatesExist(int x, int y)
{
    for (int i = 0; i < getWallsCount(); i++)
    {
        if (walls[i]->getCoordinateX() == x && walls[i]->getCoordinateY() == y)
        {
            return true;
        }
    }
    return false;
}

bool GameStorage::objectOnCoordinatesExist(int x, int y)
{
    if (tankOnCoordinatesExist(x, y)) {
        return true;
    } else if (wallOnCoordinatesExist(x, y)) {
        return true;
    }
    return false;
}

int GameStorage::getTankIndexByCoordinates(int x, int y)
{
    for (int i = 0; i < getTanksCount(); i++)
    {
        if (tanks[i]->getCoordinateX() == x && tanks[i]->getCoordinateY() == y)
        {
            return i;
        }
    }
    return 0;
}

int GameStorage::getWallIndexByCoordinates(int x, int y)
{
    for (int i = 0; i < getWallsCount(); i++)
    {
        if (walls[i]->getCoordinateX() == x && walls[i]->getCoordinateY() == y)
        {
            return i;
        }
    }
    return 0;
}

void GameStorage::deleteTankByIndex(int index)
{
    tanks.erase(tanks.begin() + index);
}
void GameStorage::deleteWallByIndex(int index)
{
    walls.erase(walls.begin() + index);
}

void GameStorage::printStorageInfo()
{
    qDebug() << "";
    qWarning() << "GameStorage::printStorageInfo Информация об объектах:";

    qDebug() << "Танки: " << getTanksCount();
    for (int i = 0; i < getTanksCount(); i++) {
        qDebug() << "index:" << i << "X:" << tanks[i]->getCoordinateX() + 1 << "Y:" << tanks[i]->getCoordinateY() + 1;
    }

    qDebug() << "Стены: " << getWallsCount();
    for (int i = 0; i < getWallsCount(); i++) {
        qDebug() << "index:" << i << "X:" << walls[i]->getCoordinateX() + 1 << "Y:" << walls[i]->getCoordinateY() + 1;
    }
}

void GameStorage::deleteExistObjectOnCoordinates(int x, int y)
{
    if (tankOnCoordinatesExist(x, y)) {
        deleteTankByIndex(getTankIndexByCoordinates(x, y));
    } else if (wallOnCoordinatesExist(x, y)) {
        deleteWallByIndex(getWallIndexByCoordinates(x, y));
    }
}

GameStorage::~GameStorage()
{
    for (int i = 0; i < tanks.size(); i++) {
        if (tanks[i]) {
            delete tanks[i];
            tanks[i] = nullptr;
        }
    }
    tanks.clear();

    for (int i = 0; i < walls.size(); i++) {
        if (walls[i]) {
            delete walls[i];
            walls[i] = nullptr;
        }
    }
    walls.clear();

    //qDebug() << "=== Destructor called: " << "GameStorage" << "===";
}
