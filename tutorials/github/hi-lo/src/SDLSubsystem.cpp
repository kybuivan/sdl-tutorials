#include "SDLSubsystem.hpp"

#include <SDL.h>

#include "Assert.hpp"

namespace HiLo {

auto SDLSubsystem::initialize() noexcept -> void
{
    static SDLSubsystem guard;
}

SDLSubsystem::SDLSubsystem() noexcept
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_assert(false);
    }
}

SDLSubsystem::~SDLSubsystem()
{
    SDL_Quit();
}

} // namespace HiLo
