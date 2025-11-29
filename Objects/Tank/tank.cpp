#include "tank.h"

Tank::Tank(int coordinateX, int coordinateY,
           Direction direction)
    : coordinateX(coordinateX), coordinateY(coordinateY),
    direction(direction)
{
}

void Tank::shot() {
    if (ammo > 0) {
        shotCondition = true;
        ammo--;
    }
}

void Tank::forward() {
    switch (direction) {
    case Direction::UP: coordinateY--; break;
    case Direction::DOWN: coordinateY++; break;
    case Direction::LEFT: coordinateX--; break;
    case Direction::RIGHT: coordinateX++; break;
    }
}

void Tank::backward() {
    switch (direction) {
    case Direction::UP: coordinateY++; break;
    case Direction::DOWN: coordinateY--; break;
    case Direction::LEFT: coordinateX++; break;
    case Direction::RIGHT: coordinateX--; break;
    }
}

void Tank::turnRight() {
    switch (direction) {
    case Direction::UP: direction = Direction::RIGHT; break;
    case Direction::DOWN: direction = Direction::LEFT; break;
    case Direction::LEFT: direction = Direction::UP; break;
    case Direction::RIGHT: direction = Direction::DOWN; break;
    }
}

void Tank::turnLeft() {
    switch (direction) {
    case Direction::UP: direction = Direction::LEFT; break;
    case Direction::DOWN: direction = Direction::RIGHT; break;
    case Direction::LEFT: direction = Direction::DOWN; break;
    case Direction::RIGHT: direction = Direction::UP; break;
    }
}

std::string Tank::getName() const {
    return name;
}

int Tank::getCoordinateX() const {
    return coordinateX;
}

int Tank::getCoordinateY() const {
    return coordinateY;
}

Direction Tank::getDirection() const {
    return direction;
}

int Tank::getHealth() const {
    return health;
}

int Tank::getAmmo() const {
    return ammo;
}

bool Tank::isShot() const {
    return shotCondition;
}

void Tank::setName(const std::string& name) {
    this->name = name;
}

void Tank::setCoordinateX(int coordinateX) {
    this->coordinateX = coordinateX;
}

void Tank::setCoordinateY(int coordinateY) {
    this->coordinateY = coordinateY;
}

void Tank::setDirection(Direction direction) {
    this->direction = direction;
}

void Tank::setHealth(int health) {
    this->health = health;
}

void Tank::setAmmo(int ammo) {
    this->ammo = ammo;
}

void Tank::setShot(bool shot) {
    this->shotCondition = shot;
}
