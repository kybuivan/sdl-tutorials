#include "Texture.hpp"

#include "Assert.hpp"

namespace HiLo
{

Texture::Texture() noexcept : mTexture{nullptr, SDL_DestroyTexture}
{
}

auto Texture::getRawPointer() const noexcept -> SDL_Texture *
{
    return mTexture.get();
}

auto Texture::setRawPointer(SDL_Texture *rawPointer) noexcept -> void
{
    mTexture.reset(rawPointer);
}

auto Texture::size() const noexcept -> Size
{
    int width;
    int height;
    if (SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &width, &height) < 0)
    {
        SDL_assert(false);
    }
    return {width, height};
}

auto Texture::setColorMod(Uint8 red, Uint8 green, Uint8 blue) noexcept -> void
{
    if (SDL_SetTextureColorMod(mTexture.get(), red, green, blue) < 0)
    {
        SDL_assert(false);
    }
}

} // namespace HiLo
