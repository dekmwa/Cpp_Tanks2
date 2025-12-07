#ifndef WALL_H
#define WALL_H

#include <string>
#include <qDebug>


class Wall
{
public:
    Wall(int coordinateX, int coordinateY);

    std::string getName() const;
    int getCoordinateX() const;
    int getCoordinateY() const;

    void setName(const std::string& name);
    void setCoordinateX(int coordinateX);
    void setCoordinateY(int coordinateY);

private:
    std::string name;
    int coordinateX;
    int coordinateY;
};

#endif // WALL_H
