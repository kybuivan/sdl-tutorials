#include "Display.hpp"

#include <SDL.h>

#include "Assert.hpp"

namespace HiLo
{

auto getDisplaySize() noexcept -> Size
{
    SDL_Rect rect;
    if (SDL_GetDisplayUsableBounds(0, &rect) < 0)
    {
        SDL_assert(false);
    }
    return {rect.w, rect.h};
}

} // namespace HiLo
