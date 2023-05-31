#include "score_indicator.h"

using namespace pong;

// horizontal line draw instruction indices.
#define HLINE_TOP 0
#define HLINE_MIDDLE 1
#define HLINE_BOTTOM 2

// vertical line draw instruction indices.
#define VLINE_LEFT_TOP 0
#define VLINE_LEFT_BOTTOM 1
#define VLINE_RIGHT_TOP 2
#define VLINE_RIGHT_BOTTOM 3
#define VLINE_CENTER 4

inline void drawLine(SDL_Renderer &renderer, const SDL_Rect &instructions)
{
    SDL_RenderFillRect(&renderer, &instructions);
}

ScoreIndicator::ScoreIndicator(int x, int y, int width, int height) : mValue(0)
{
    // calculate the line thickness based on the indicator height.
    auto thickness = (height / 5);

    // construct horizontal line draw instructions.
    mHLines[HLINE_TOP] = {x, y, width, thickness};
    mHLines[HLINE_MIDDLE] = {x,
                             y + (height / 2) - thickness / 2,
                             width,
                             thickness};
    mHLines[HLINE_BOTTOM] = {x, y + (height - thickness), width, thickness};

    // construct vertical line draw instructions.
    mVLines[VLINE_LEFT_TOP] = {x, y, thickness, height / 2};
    mVLines[VLINE_LEFT_BOTTOM] = {x, y + height / 2, thickness, height / 2};
    mVLines[VLINE_RIGHT_TOP] = {x + width - thickness,
                                y,
                                thickness,
                                height / 2};
    mVLines[VLINE_RIGHT_BOTTOM] = {x + width - thickness,
                                   y + height / 2,
                                   thickness,
                                   height / 2};
    mVLines[VLINE_CENTER] = {x + width / 2 - thickness, y, thickness, height};
}

void ScoreIndicator::onDraw(SDL_Renderer &renderer)
{
    switch (mValue)
    {
    case 0:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    case 1:
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_CENTER]);
        break;
    case 2:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
        break;
    case 3:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    case 4:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    case 5:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    case 6:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    case 7:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    case 8:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    case 9:
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
        SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
        SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
        break;
    }
}
