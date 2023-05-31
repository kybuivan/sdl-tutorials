#include "welcome_scene.h"
#include "court_scene.h"
#include "game.h"

#include <SDL.h>

using namespace pong;

WelcomeScene::WelcomeScene(Game &game)
    : mGame(game), mTopicTexture(nullptr), mLeftPlayerInstructions(nullptr),
      mRightPlayerInstructions(nullptr), mContinueInstructions(nullptr)
{
    mTopicTexture = mGame.createText("SDL2 PONG");
    mLeftPlayerInstructions =
        mGame.createText("Controls for the left player: W and S");
    mRightPlayerInstructions = mGame.createText(
        "Controls for the right player: UP-ARROW and DOWN-ARROW");
    mContinueInstructions =
        mGame.createText("Press [ENTER] to start the match");
}

WelcomeScene::~WelcomeScene()
{
    SDL_DestroyTexture(mTopicTexture);
    SDL_DestroyTexture(mLeftPlayerInstructions);
    SDL_DestroyTexture(mRightPlayerInstructions);
    SDL_DestroyTexture(mContinueInstructions);
}

void WelcomeScene::onDraw(SDL_Renderer &renderer)
{
    // draw the topic of the game.
    SDL_Rect rect{0, 100, 0, 0};
    SDL_QueryTexture(mTopicTexture, nullptr, nullptr, &rect.w, &rect.h);
    rect.x = (400 - (rect.w / 2));
    SDL_RenderCopy(&renderer, mTopicTexture, nullptr, &rect);

    // draw the left player control instructions.
    SDL_QueryTexture(mLeftPlayerInstructions,
                     nullptr,
                     nullptr,
                     &rect.w,
                     &rect.h);
    rect.x = (400 - (rect.w / 2));
    rect.y = 200;
    SDL_RenderCopy(&renderer, mLeftPlayerInstructions, nullptr, &rect);

    // draw the right player control instructions.
    SDL_QueryTexture(mRightPlayerInstructions,
                     nullptr,
                     nullptr,
                     &rect.w,
                     &rect.h);
    rect.x = (400 - (rect.w / 2));
    rect.y = 250;
    SDL_RenderCopy(&renderer, mRightPlayerInstructions, nullptr, &rect);

    // draw the instructions how to continue to court scene.
    SDL_QueryTexture(mContinueInstructions, nullptr, nullptr, &rect.w, &rect.h);
    rect.x = (400 - (rect.w / 2));
    rect.y = 400;
    SDL_RenderCopy(&renderer, mContinueInstructions, nullptr, &rect);
}

void WelcomeScene::onUpdate()
{
    // ...
}

void WelcomeScene::onEnter()
{
    // ...
}

void WelcomeScene::onExit()
{
    // ...
}

void WelcomeScene::onKeyDown(SDL_KeyboardEvent &event)
{
    // ...
}

void WelcomeScene::onKeyUp(SDL_KeyboardEvent &event)
{
    // move player into the court scene to start the match.
    switch (event.keysym.sym)
    {
    case SDLK_RETURN:
        mGame.setScene(std::make_shared<CourtScene>(mGame));
        break;
    }
}
