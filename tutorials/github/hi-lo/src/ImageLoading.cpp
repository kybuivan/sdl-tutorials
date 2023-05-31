#include "ImageLoading.hpp"

#include <SDL_image.h>

#include "Assert.hpp"
#include "Renderer.hpp"

namespace HiLo
{

auto loadTexture(std::string const &path) noexcept -> Texture
{
    auto rawTexture =
        IMG_LoadTexture(Renderer::instance().getRawPointer(), path.c_str());
    SDL_assert(rawTexture);
    Texture texture;
    texture.setRawPointer(rawTexture);
    return texture;
}

} // namespace HiLo
