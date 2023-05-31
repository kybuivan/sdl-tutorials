#include "wall.h"

using namespace pong;

Wall::Wall(int x, int y, int width, int height) : mRect({x, y, width, height})
{
    // construct an AABB for the wall.
    mAabb.setCenterX(x + width / 2);
    mAabb.setCenterY(y + height / 2);
    mAabb.setExtentX(width / 2);
    mAabb.setExtentY(height / 2);
}

void Wall::onDraw(SDL_Renderer &renderer)
{
    SDL_RenderFillRect(&renderer, &mRect);
}
