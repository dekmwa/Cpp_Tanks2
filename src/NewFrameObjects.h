#ifndef NEWFRAMEOBJECTS_H
#define NEWFRAMEOBJECTS_H

#include "../Objects/Tank/tank.h"
#include "../Objects/Wall/wall.h"


struct NewFrameObjects {
    std::vector<Tank> tanks;
    std::vector<Wall> walls;
};

#endif // NEWFRAMEOBJECTS_H
