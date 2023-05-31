#include "ball.h"
#include "court_scene.h"

using namespace pong;

const float Ball::INITIAL_VELOCITY = 8.f;
const float Ball::VELOCITY_INCREASE = 1.f;
const float Ball::MAX_VELOCITY = 15.f;

Ball::Ball(CourtScene &scene, int x, int y, int width, int height)
    : mScene(scene), mRect({x, y, width, height}), mVelocity(INITIAL_VELOCITY),
      mDirection({-0.5f, 0.5f})
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

void Ball::onDraw(SDL_Renderer &renderer)
{
    SDL_RenderFillRect(&renderer, &mRect);
}

void Ball::onUpdate()
{
    // create an array which contains the movement.
    auto movement = std::array<int, 2>();
    movement[0] = static_cast<int>(mDirection[0] * mVelocity);
    movement[1] = static_cast<int>(mDirection[1] * mVelocity);

    // apply the movement for the position of the ball.
    mRect.x += movement[0];
    mRect.y += movement[1];

    // apply the movement for the position of the AABB.
    mAabb.setCenterX(mAabb.getCenterX() + movement[0]);
    mAabb.setCenterY(mAabb.getCenterY() + movement[1]);

    // get references to all possible collision candidates.
    const auto &bottomWallAabb = mScene.getBottomWall().getAabb();
    const auto &topWallAabb = mScene.getTopWall().getAabb();
    const auto &leftPaddleAabb = mScene.getLeftPaddle().getAabb();
    const auto &rightPaddleAabb = mScene.getRightPaddle().getAabb();
    const auto &leftGoalAabb = mScene.getLeftGoal().getAabb();
    const auto &rightGoalAabb = mScene.getRightGoal().getAabb();

    if (mAabb.collides(bottomWallAabb))
    {
        // prevent the ball from moving through the wall.
        mRect.y = bottomWallAabb.getCenterY();
        mRect.y -= bottomWallAabb.getExtentY();
        mRect.y -= mRect.h;

        // ensure that the AABB position gets updated as well.
        mAabb.setCenterX(mRect.x + mAabb.getExtentX());
        mAabb.setCenterY(mRect.y + mAabb.getExtentY());

        // invert the y-axis direction.
        mDirection[1] = -mDirection[1];
    }
    else if (mAabb.collides(topWallAabb))
    {
        // prevent the ball from moving through the wall.
        mRect.y = topWallAabb.getCenterY();
        mRect.y += topWallAabb.getExtentY();

        // ensure that the AABB position gets updated as well.
        mAabb.setCenterX(mRect.x + mAabb.getExtentX());
        mAabb.setCenterY(mRect.y + mAabb.getExtentY());

        // invert the y-axis direction.
        mDirection[1] = -mDirection[1];
    }
    else if (mAabb.collides(leftPaddleAabb))
    {
        // prevent the ball from moving through the paddle.
        mRect.x = leftPaddleAabb.getCenterX();
        mRect.x += leftPaddleAabb.getExtentX();

        // ensure that the AABB position gets updated as well.
        mAabb.setCenterX(mRect.x + mAabb.getExtentX());
        mAabb.setCenterY(mRect.y + mAabb.getExtentY());

        // invert the y-axis direction.
        mDirection[0] = -mDirection[0];

        // increase the velocity if possible.
        mVelocity += VELOCITY_INCREASE;
        mVelocity = std::min(mVelocity, MAX_VELOCITY);
    }
    else if (mAabb.collides(rightPaddleAabb))
    {
        // prevent the ball from moving through the paddle.
        mRect.x = rightPaddleAabb.getCenterX();
        mRect.x -= rightPaddleAabb.getExtentX();
        mRect.x -= mRect.w;

        // ensure that the AABB position gets updated as well.
        mAabb.setCenterX(mRect.x + mAabb.getExtentX());
        mAabb.setCenterY(mRect.y + mAabb.getExtentY());

        // invert the y-axis direction.
        mDirection[0] = -mDirection[0];

        // increase the velocity if possible.
        mVelocity += VELOCITY_INCREASE;
        mVelocity = std::min(mVelocity, MAX_VELOCITY);
    }
    else if (mAabb.collides(rightGoalAabb))
    {
        mScene.addPlayerScore(0);
    }
    else if (mAabb.collides(leftGoalAabb))
    {
        mScene.addPlayerScore(1);
    }
}
