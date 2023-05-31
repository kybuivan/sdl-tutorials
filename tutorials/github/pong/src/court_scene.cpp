#include "court_scene.h"
#include "endgame_scene.h"
#include "game.h"
#include "wall.h"

#include <SDL.h>
#include <stdlib.h>
#include <time.h>

using namespace pong;

// The amount of pause ticks to wait at start or after a goal.
#define PAUSE_TICKS 30

CourtScene::CourtScene(Game &game)
    : mGame(game), mTopWall(0, 0, game.getResolution()[0], BOX_WIDTH),
      mBottomWall(0,
                  (game.getResolution()[1] - BOX_WIDTH),
                  game.getResolution()[0],
                  BOX_WIDTH),
      mCenterLine((game.getResolution()[0] / 2) - BOX_WIDTH / 2,
                  BOX_WIDTH,
                  BOX_WIDTH,
                  game.getResolution()[1]),
      mLeftPaddle(*this,
                  EDGE_OFFSET,
                  (game.getResolution()[1] / 2) - (PADDLE_HEIGHT / 2),
                  BOX_WIDTH,
                  PADDLE_HEIGHT),
      mRightPaddle(*this,
                   game.getResolution()[0] - EDGE_OFFSET - BOX_WIDTH,
                   (game.getResolution()[1] / 2) - (PADDLE_HEIGHT / 2),
                   BOX_WIDTH,
                   PADDLE_HEIGHT),
      mBall(*this,
            game.getResolution()[0] / 2 - (BOX_WIDTH / 2),
            game.getResolution()[1] / 2 - (BOX_WIDTH / 2),
            BOX_WIDTH,
            BOX_WIDTH),
      mLeftGoal(-1000, 0, 1000 - BOX_WIDTH, game.getResolution()[1]),
      mRightGoal(game.getResolution()[0] + BOX_WIDTH,
                 0,
                 1000,
                 game.getResolution()[1]),
      mLeftScoreIndicator(game.getHalfResolution()[0] -
                              (70 + (game.getResolution()[0] / 10)),
                          game.getResolution()[1] / 10,
                          game.getResolution()[0] / 10,
                          game.getResolution()[1] / 6),
      mRightScoreIndicator(game.getHalfResolution()[0] + 70,
                           game.getResolution()[1] / 10,
                           game.getResolution()[0] / 10,
                           game.getResolution()[1] / 6),
      mRemainingPauseTicks(PAUSE_TICKS)
{
    // ...
}

CourtScene::~CourtScene()
{
    // ...
}

void CourtScene::onDraw(SDL_Renderer &renderer)
{
    mTopWall.onDraw(renderer);
    mBottomWall.onDraw(renderer);
    mCenterLine.onDraw(renderer);
    mLeftPaddle.onDraw(renderer);
    mRightPaddle.onDraw(renderer);
    mBall.onDraw(renderer);
    mLeftScoreIndicator.onDraw(renderer);
    mRightScoreIndicator.onDraw(renderer);
}

void CourtScene::onUpdate()
{
    if (mRemainingPauseTicks <= 0)
    {
        mLeftPaddle.onUpdate();
        mRightPaddle.onUpdate();
        mBall.onUpdate();
    }
    else
    {
        mRemainingPauseTicks--;
    }
}

void CourtScene::onEnter()
{
    // seed the random with the time.
    srand(static_cast<unsigned int>(time(nullptr)));

    // clear the player scores.
    mGame.getPlayerScores()[0] = 0;
    mGame.getPlayerScores()[1] = 0;
}

void CourtScene::onExit()
{
    // TODO ...
}

void CourtScene::onKeyDown(SDL_KeyboardEvent &event)
{
    switch (event.keysym.sym)
    {
    case SDLK_w:
        mLeftPaddle.setMovement(Paddle::Movement::UP);
        break;
    case SDLK_s:
        mLeftPaddle.setMovement(Paddle::Movement::DOWN);
        break;
    case SDLK_UP:
        mRightPaddle.setMovement(Paddle::Movement::UP);
        break;
    case SDLK_DOWN:
        mRightPaddle.setMovement(Paddle::Movement::DOWN);
        break;
    }
}

void CourtScene::onKeyUp(SDL_KeyboardEvent &event)
{
    switch (event.keysym.sym)
    {
    case SDLK_w:
        if (mLeftPaddle.isMoving(Paddle::Movement::UP))
        {
            mLeftPaddle.setMovement(Paddle::Movement::NONE);
        }
        break;
    case SDLK_s:
        if (mLeftPaddle.isMoving(Paddle::Movement::DOWN))
        {
            mLeftPaddle.setMovement(Paddle::Movement::NONE);
        }
        break;
    case SDLK_UP:
        if (mRightPaddle.isMoving(Paddle::Movement::UP))
        {
            mRightPaddle.setMovement(Paddle::Movement::NONE);
        }
        break;
    case SDLK_DOWN:
        if (mRightPaddle.isMoving(Paddle::Movement::DOWN))
        {
            mRightPaddle.setMovement(Paddle::Movement::NONE);
        }
        break;
    }
}

void CourtScene::addPlayerScore(int playerIndex)
{
    resetEntities();
    auto &scores = mGame.getPlayerScores();
    scores[playerIndex]++;
    if (playerIndex == 0)
    {
        mLeftScoreIndicator.setValue(scores[playerIndex]);
    }
    else
    {
        mRightScoreIndicator.setValue(scores[playerIndex]);
    }
    mRemainingPauseTicks = PAUSE_TICKS;
    if (scores[playerIndex] > 9)
    {
        mGame.setScene(std::make_shared<EndgameScene>(mGame));
    }
}

void CourtScene::resetEntities()
{
    // get a reference to screen half-resolution values.
    const auto &halfResolution = mGame.getHalfResolution();

    // place the ball back into the middle of the screen.
    const auto &ballAabb = mBall.getAabb();
    mBall.setX(halfResolution[0] - ballAabb.getExtentX());
    mBall.setY(halfResolution[1] - ballAabb.getExtentY());

    // randomize the ball direction.
    int random = rand() % 4;
    switch (random)
    {
    case 0:
        mBall.setDirection({0.5f, 0.5f});
        break;
    case 1:
        mBall.setDirection({0.5f, -0.5f});
        break;
    case 2:
        mBall.setDirection({-0.5f, 0.5f});
        break;
    case 3:
        mBall.setDirection({-0.5f, -0.5f});
        break;
    }

    // reset the ball velocity back to initial velocity.
    mBall.setVelocity(Ball::INITIAL_VELOCITY);

    // place the paddles back into the initial positions.
    const auto &paddleAabb = mLeftPaddle.getAabb();
    mLeftPaddle.setY(halfResolution[1] - paddleAabb.getExtentY());
    mRightPaddle.setY(halfResolution[1] - paddleAabb.getExtentY());
}
