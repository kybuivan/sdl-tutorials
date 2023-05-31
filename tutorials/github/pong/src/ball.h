/*! The ball entity that contains definitions for the game ball.

    This class presents the ball entity used in the court scene. Ball is an
    entity that goes around the scene by bouncing from the other entities.
 */
#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "aabb.h"

#include <SDL.h>
#include <array>

namespace pong
{
class CourtScene;
class Ball
{
public:
    /** The initial velocity for the ball. */
    static const float INITIAL_VELOCITY;
    /** The amount of velocity to be added on each paddle hit. */
    static const float VELOCITY_INCREASE;
    /** The maximum velocity for the ball. */
    static const float MAX_VELOCITY;

    Ball(CourtScene &scene, int x, int y, int width, int height);

    void onDraw(SDL_Renderer &renderer);
    void onUpdate();

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

    void setDirection(const std::array<float, 2> &direction)
    {
        mDirection = direction;
    }

    void setVelocity(float velocity)
    {
        mVelocity = velocity;
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
    CourtScene &mScene;
    SDL_Rect mRect;
    AABB mAabb;
    float mVelocity;
    std::array<float, 2> mDirection;
};
} // namespace pong

#endif
