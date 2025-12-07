#ifndef NEWFRAMEOBJECTS_H
#define NEWFRAMEOBJECTS_H

#include "tank.h"
#include "wall.h"


struct NewFrameObjects {
    std::vector<Tank> tanks;
    std::vector<Wall> walls;
};

#endif // NEWFRAMEOBJECTS_H
