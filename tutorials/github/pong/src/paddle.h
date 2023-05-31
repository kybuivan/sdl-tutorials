/*! A paddle definition and implementation for a Pong game.

    This class contains the necessary definitions and logics for a single game
    paddle instance that is used in the court scene. Paddles act as a player
    avatars that can be controlled in a response for player inputs.
 */
#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include <SDL.h>

#include "aabb.h"

namespace pong
{
class CourtScene;
class Paddle
{
public:
    /*! The movement velocity for the paddle. */
    static const int VELOCITY;

    /*! Enumeration for possible paddle movement directions. */
    enum class Movement : int
    {
        UP = -1,
        NONE = 0,
        DOWN = 1
    };

    Paddle(CourtScene &scene, int x, int y, int width, int height);

    void onDraw(SDL_Renderer &renderer);
    void onUpdate();

    void setMovement(Movement movement)
    {
        mMovement = movement;
    }

    bool isMoving(Movement movement) const
    {
        return mMovement == movement;
    }

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
    CourtScene &mScene;
    SDL_Rect mRect;
    Movement mMovement;
    AABB mAabb;
};
} // namespace pong

#endif
