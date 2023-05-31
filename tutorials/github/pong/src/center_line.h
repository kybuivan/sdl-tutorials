/*! The center line entity that contains the center line boxes.

    Note that this entity is not collideable and should not be used in any kind
    of game logic related stuff. It is only used to make the court to look like
    a playfield similar to tennis or other ball games.
 */
#ifndef PONG_CENTER_LINE_H
#define PONG_CENTER_LINE_H

#include <SDL.h>

namespace pong
{
class CenterLine
{
public:
    CenterLine(int x, int y, int height, int widt);

    void onDraw(SDL_Renderer &renderer);

private:
    SDL_Rect mRect;
};
} // namespace pong

#endif
