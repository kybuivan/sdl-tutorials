/*! A score indicator for the application.

    Score indicators are used to show the current score state for the users.
    Typically a Pong gameplay scene contains two score indicators at the each
    side of the center line. One score indicator is assigned for each player.
 */
#ifndef PONG_SCORE_INDICATOR_H
#define PONG_SCORE_INDICATOR_H

#include <SDL.h>
#include <array>

namespace pong
{
class ScoreIndicator final
{
public:
    ScoreIndicator(int x, int y, int width, int height);

    void onDraw(SDL_Renderer &renderer);

    void setValue(int value)
    {
        mValue = value;
    }

private:
    int mValue;
    std::array<SDL_Rect, 3> mHLines;
    std::array<SDL_Rect, 5> mVLines;
};
} // namespace pong

#endif
