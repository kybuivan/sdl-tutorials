#include "game.h"
#include "welcome_scene.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#define ERROR -1
#define OK 0

using namespace pong;

Game::Game()
    : mWindow(nullptr), mRenderer(nullptr), mFont(nullptr),
      mResolution({800, 600}),
      mHalfResolution({mResolution[0] / 2, mResolution[1] / 2}),
      mPlayerScores({0, 0})
{
    // ...
}

Game::~Game()
{
    TTF_CloseFont(mFont);
    SDL_DestroyWindow(mWindow);
    TTF_Quit();
    SDL_Quit();
}

void Game::start()
{
    // initialize the SDL2 framework along with systems.
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError()
                  << std::endl;
        return;
    }

    // initialize the TTF framework for the text rendering.
    if (TTF_Init() == -1)
    {
        std::cerr << "Unable to initialize TTF: " << TTF_GetError()
                  << std::endl;
        return;
    }

    // try to create a new window for the application.
    mWindow = SDL_CreateWindow("SDL2 - Pong",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               mResolution[0],
                               mResolution[1],
                               SDL_WINDOW_SHOWN);
    if (mWindow == nullptr)
    {
        std::cerr << "Unable to create SDL window: " << SDL_GetError()
                  << std::endl;
        return;
    }

    // try to create a new renderer for the application window.
    mRenderer = SDL_CreateRenderer(mWindow,
                                   -1,
                                   SDL_RENDERER_ACCELERATED |
                                       SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr)
    {
        std::cerr << "Unable to create SDL renderer: " << SDL_GetError()
                  << std::endl;
        return;
    }

    // initialize the font we want to use within our application.
    mFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 28);
    if (mFont == nullptr)
    {
        std::cerr << "Unable to load a font for the application: "
                  << TTF_GetError() << std::endl;
    }

    // set the initial scene for the game.
    setScene(std::make_shared<WelcomeScene>(*this));

    auto isRunning = true;
    SDL_Event event;
    while (isRunning)
    {
        // poll and handle events from the SDL framework.
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                mScene->onKeyDown(event.key);
                break;
            case SDL_KEYUP:
                mScene->onKeyUp(event.key);
                break;
            }
        }

        // update game logics on the current scene.
        mScene->onUpdate();

        // clear the rendering context with the black color.
        SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(mRenderer);

        // turn the renderer draw color to white.
        SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);

        // render scene stuff into the buffer.
        mScene->onDraw(*mRenderer);

        // present the rendered buffer.
        SDL_RenderPresent(mRenderer);
    }
}

void Game::setScene(ScenePtr scene)
{
    // skip the null scene assignment.
    if (scene == nullptr)
    {
        std::cerr << "Unable to set null as the active scene!" << std::endl;
        return;
    }

    // tell old scene (if any) that we are going to exit from it.
    if (mScene)
    {
        mScene->onExit();
    }

    // assign and enter the new scene.
    mScene = scene;
    mScene->onEnter();
}

SDL_Texture *Game::createText(const std::string &text)
{
    // create a surface which contains the desired text.
    SDL_Color color{0xff, 0xff, 0xff, 0xff};
    auto surface = TTF_RenderText_Blended(mFont, text.c_str(), color);
    if (surface == nullptr)
    {
        std::cerr << "Unable to create a surface with a text: "
                  << TTF_GetError() << std::endl;
        return nullptr;
    }

    // create a texture from the text surface.
    auto texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        std::cerr << "Unable to create texture from a text surface: "
                  << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}
