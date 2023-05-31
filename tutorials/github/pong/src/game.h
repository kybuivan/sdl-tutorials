/*! The game instance for the whole application.

  This is the main instance for the whole Pong game application. This class
  encapsulates the required functionality to tie the application as a whole
  by combining and providing a way to manage the game state and scenes as
  well as the management of performing logical game updates (i.e. ticks).
 */
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "scene.h"

#include <array>
#include <string>

// SDL forward declarations.
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

namespace pong
{
class Game
{
public:
    Game();
    Game(const Game &) = delete;
    Game(Game &&) = delete;

    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;

    ~Game();

    void start();

    void setScene(ScenePtr scene);

    SDL_Texture *createText(const std::string &text);

    /* Get the resolution (in a 2d-array) of the game canvas. */
    const std::array<int, 2> &getResolution() const
    {
        return mResolution;
    }

    /* Get the half-resolution (in a 2d-array) of the game canvas. */
    const std::array<int, 2> &getHalfResolution() const
    {
        return mHalfResolution;
    }

    /* Get a reference to the player scores via a 2d-array. */
    std::array<int, 2> &getPlayerScores()
    {
        return mPlayerScores;
    }

private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    _TTF_Font *mFont;
    ScenePtr mScene;
    std::array<int, 2> mResolution;
    std::array<int, 2> mHalfResolution;
    std::array<int, 2> mPlayerScores;
};
} // namespace pong

#endif
