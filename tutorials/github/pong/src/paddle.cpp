#include "paddle.h"
#include "court_scene.h"

#include <iostream>

using namespace pong;

const int Paddle::VELOCITY = 8;

Paddle::Paddle(CourtScene &scene, int x, int y, int width, int height)
    : mScene(scene), mRect({x, y, width, height}), mMovement(Movement::NONE)
{
    // calculate half width and height.
    auto halfWidth = (width / 2);
    auto halfHeight = (height / 2);

    // construct an AABB for the object.
    mAabb.setCenterX(x + halfWidth);
    mAabb.setCenterY(y + halfHeight);
    mAabb.setExtentX(halfWidth);
    mAabb.setExtentY(halfHeight);
}

void Paddle::onDraw(SDL_Renderer &renderer)
{
    SDL_RenderFillRect(&renderer, &mRect);
}

void Paddle::onUpdate()
{
    // update paddle position only if the paddle is moving.
    if (mMovement != Movement::NONE)
    {
        auto movement = (int)mMovement * VELOCITY;
        mRect.y += movement;
        mAabb.setCenterY(mAabb.getCenterY() + movement);
        if (mMovement == Movement::UP)
        {
            const auto &wallAabb = mScene.getTopWall().getAabb();
            if (mAabb.collides(wallAabb))
            {
                // prevent the paddle from moving through the wall.
                mRect.y = wallAabb.getCenterY();
                mRect.y += wallAabb.getExtentY();

                // ensure that the AABB position gets updated as well.
                mAabb.setCenterY(mRect.y + mAabb.getExtentY());

                // stop the movement.
                mMovement = Movement::NONE;
            }
        }
        else
        {
            const auto &wallAabb = mScene.getBottomWall().getAabb();
            if (mAabb.collides(wallAabb))
            {
                // prevent the paddle from moving through the wall.
                mRect.y = wallAabb.getCenterY();
                mRect.y -= wallAabb.getExtentY();
                mRect.y -= mRect.h;

                // ensure that the AABB position gets updated as well.
                mAabb.setCenterY(mRect.y + mAabb.getExtentY());

                // stop the movement.
                mMovement = Movement::NONE;
            }
        }
    }
}
