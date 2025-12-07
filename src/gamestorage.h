#ifndef GAMESTORAGE_H
#define GAMESTORAGE_H

#include "tank.h"
#include "wall.h"
#include <vector>

class GameStorage
{
public:
    GameStorage();
    ~GameStorage();

    void setTanksVector(std::vector<Tank*> newTanks);
    void setWallsVector(std::vector<Wall*> newWalls);
    std::vector<Tank*> getTanksVector();
    std::vector<Wall*> getWallsVector();

    void pushTank(Tank *tank);
    void pushWall(Wall *wall);

    Tank* getTankByIndex(int index);
    Wall* getWallByIndex(int index);

    int getTanksCount();
    int getWallsCount();

    int getWidthCellsCount();
    int getHeightCellsCount();
    void setWidthCellsCount(int count);
    void setHeightCellsCount(int count);

    bool tankOnCoordinatesExist(int x, int y);
    bool wallOnCoordinatesExist(int x, int y);
    bool objectOnCoordinatesExist(int x, int y);

    int getTankIndexByCoordinates(int x, int y);
    int getWallIndexByCoordinates(int x, int y);

    void deleteTankByIndex(int index);
    void deleteWallByIndex(int index);
    void deleteExistObjectOnCoordinates(int x, int y);

    void printStorageInfo();

private:
    std::vector<Tank*> tanks;
    std::vector<Wall*> walls;
    int widthCellsCount;
    int heightCellsCount;
};

#endif // GAMESTORAGE_H
