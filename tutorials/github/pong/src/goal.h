/*! A goal entity that contains definitions for the game goals.

    This class contains an implementation for a single pong game goal. Goal is
    not a visible component but is used to detect when players gain scores.
 */
#ifndef PONG_GOAL_H
#define PONG_GOAL_H

#include <SDL.h>

#include "aabb.h"

namespace pong
{
class Goal final
{
public:
    Goal(int x, int y, int width, int height);

    void setX(int x)
    {
        mRect.x = x;
        mAabb.setCenterX(x + mAabb.getExtentX());
    }
    void setY(int y)
    {
        mRect.y = y;
        mAabb.setCenterY(y + mAabb.getExtentY());
    }

    const AABB &getAabb() const
    {
        return mAabb;
    }
    AABB &getAabb()
    {
        return mAabb;
    }

private:
    SDL_Rect mRect;
    AABB mAabb;
};
} // namespace pong

#endif
