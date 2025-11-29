#ifndef TANK_H
#define TANK_H

#include <string>
#include <QDebug>


enum class Direction {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class Tank
{
public:
    Tank(int coordinateX, int coordinateY,
         Direction direction);

    void shot();
    void forward();
    void backward();
    void turnRight();
    void turnLeft();

    std::string getName() const;
    int getCoordinateX() const;
    int getCoordinateY() const;
    Direction getDirection() const;
    int getHealth() const;
    int getAmmo() const;
    bool isShot() const;

    void setName(const std::string& name);
    void setCoordinateX(int coordinateX);
    void setCoordinateY(int coordinateY);
    void setDirection(Direction direction);
    void setHealth(int health);
    void setAmmo(int ammo);
    void setShot(bool shot);

private:
    std::string name;
    int coordinateX;
    int coordinateY;
    Direction direction;
    int health;
    int ammo;
    bool shotCondition = false;
};

#endif // TANK_H
