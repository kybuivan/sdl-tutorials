#include "TTFSubsystem.hpp"

#include <SDL_ttf.h>

#include "Assert.hpp"

namespace HiLo
{

auto TTFSubsystem::initialize() noexcept -> void
{
    static TTFSubsystem guard;
}

TTFSubsystem::TTFSubsystem() noexcept
{
    if (TTF_Init() < 0)
    {
        SDL_assert(false);
    }
}

TTFSubsystem::~TTFSubsystem()
{
    TTF_Quit();
}

} // namespace HiLo
