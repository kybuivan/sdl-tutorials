/*! The court scene for the application.

    This class contains the definitions and the implementation for the court
    scene for the Pong game. Court scene is the scene where the actual gameplay
    takes presence. It contains the definitions for the ball, paddles, goals
    and other entities that are required to play the Pong game.
 */
#ifndef PONG_COURT_SCENE_H
#define PONG_COURT_SCENE_H

#include "ball.h"
#include "center_line.h"
#include "goal.h"
#include "paddle.h"
#include "scene.h"
#include "score_indicator.h"
#include "wall.h"

#include <array>

namespace pong
{
class Game;
class CourtScene : public Scene
{
public:
    /*! The width of the ball boxes used aroung the scene. */
    static const int BOX_WIDTH = 20;
    /*! The height for the top and bottom walls. */
    static const int WALL_HEIGHT = BOX_WIDTH;
    /*! The height for the left and right paddles. */
    static const int PADDLE_HEIGHT = 100;
    /*! A constant edge offset pixels for both paddles. */
    static const int EDGE_OFFSET = 30;

    CourtScene(Game &game);
    virtual ~CourtScene();

    void onDraw(SDL_Renderer &renderer) override;
    void onUpdate() override;
    void onEnter() override;
    void onExit() override;
    void onKeyDown(SDL_KeyboardEvent &event) override;
    void onKeyUp(SDL_KeyboardEvent &event) override;

    void addPlayerScore(int playerIndex);
    void resetEntities();

    const Game &getGame() const
    {
        return mGame;
    }
    Game &getGame()
    {
        return mGame;
    }

    const Wall &getTopWall() const
    {
        return mTopWall;
    }
    Wall &getTopWall()
    {
        return mTopWall;
    }

    const Wall &getBottomWall() const
    {
        return mBottomWall;
    }
    Wall &getBottomWall()
    {
        return mBottomWall;
    }

    const CenterLine &getCenterLine() const
    {
        return mCenterLine;
    }
    CenterLine &getCenterLine()
    {
        return mCenterLine;
    }

    const Paddle &getLeftPaddle() const
    {
        return mLeftPaddle;
    }
    Paddle &getLeftPaddle()
    {
        return mLeftPaddle;
    }

    const Paddle &getRightPaddle() const
    {
        return mRightPaddle;
    }
    Paddle &getRightPaddle()
    {
        return mRightPaddle;
    }

    const Goal &getLeftGoal() const
    {
        return mLeftGoal;
    }
    Goal &getLeftGoal()
    {
        return mLeftGoal;
    }

    const Goal &getRightGoal() const
    {
        return mRightGoal;
    }
    Goal &getRightGoal()
    {
        return mRightGoal;
    }

private:
    Game &mGame;

    Wall mTopWall;
    Wall mBottomWall;
    CenterLine mCenterLine;
    Paddle mLeftPaddle;
    Paddle mRightPaddle;
    Ball mBall;
    Goal mLeftGoal;
    Goal mRightGoal;
    ScoreIndicator mLeftScoreIndicator;
    ScoreIndicator mRightScoreIndicator;
    int mRemainingPauseTicks;
};
} // namespace pong

#endif
