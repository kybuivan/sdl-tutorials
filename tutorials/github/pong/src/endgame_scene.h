/*! The end game scene for the application.

    This class contains the implementation for the "end game" scene for the
    game. It shows the overall results of the game to the players and is being
    shown after a match in the court scene has been ended.
 */
#ifndef PONG_ENDGAME_SCENE_H
#define PONG_ENDGAME_SCENE_H

#include "game.h"
#include "scene.h"


namespace pong
{
class EndgameScene final : public Scene
{
public:
    EndgameScene(Game &game);
    ~EndgameScene();

    void onDraw(SDL_Renderer &renderer) override;
    void onUpdate() override;
    void onEnter() override;
    void onExit() override;
    void onKeyDown(SDL_KeyboardEvent &event) override;
    void onKeyUp(SDL_KeyboardEvent &event) override;

private:
    Game &mGame;
    SDL_Texture *mTopicTexture;
    SDL_Texture *mEndgameTexture;
    SDL_Texture *mWinnerTexture;
    SDL_Texture *mEndResultTexture;
    SDL_Texture *mResultScoreTexture;
    SDL_Texture *mInstructionsTexture;
};
} // namespace pong

#endif
