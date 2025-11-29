#include "wall.h"

Wall::Wall(int coordinateX, int coordinateY)
    : coordinateX(coordinateX), coordinateY(coordinateY)
{
}

std::string Wall::getName() const {
    return name;
}

int Wall::getCoordinateX() const {
    return coordinateX;
}

int Wall::getCoordinateY() const {
    return coordinateY;
}

void Wall::setName(const std::string& name) {
    this->name = name;
}

void Wall::setCoordinateX(int coordinateX) {
    this->coordinateX = coordinateX;
}

void Wall::setCoordinateY(int coordinateY) {
    this->coordinateY = coordinateY;
}
