#include "goal.h"

using namespace pong;

Goal::Goal(int x, int y, int width, int height) : mRect({x, y, width, height})
{
    // calculate the half width and height.
    auto extentX = (width / 2);
    auto extentY = (height / 2);

    // define the dimensions for the AABB.
    mAabb.setCenterX(x + extentX);
    mAabb.setCenterY(y + extentY);
    mAabb.setExtentX(extentX);
    mAabb.setExtentY(extentY);
}
