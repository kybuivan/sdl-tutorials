#include "IMGSubsystem.hpp"

#include <SDL_image.h>

#include "Assert.hpp"

namespace HiLo
{

auto IMGSubsystem::initialize() noexcept -> void
{
    static IMGSubsystem guard;
}

IMGSubsystem::IMGSubsystem() noexcept
{
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_assert(false);
    }
}

IMGSubsystem::~IMGSubsystem()
{
    IMG_Quit();
}

} // namespace HiLo
