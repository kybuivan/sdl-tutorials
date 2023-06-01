#pragma once

#include <memory>

#include <SDL.h>

#include <size.hpp>

namespace HiLo
{

class Texture
{
public:
    Texture() noexcept;

    auto getRawPointer() const noexcept -> SDL_Texture *;

    auto setRawPointer(SDL_Texture *) noexcept -> void;

    auto size() const noexcept -> Size;

    auto setColorMod(Uint8 red, Uint8 green, Uint8 blue) noexcept -> void;

private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> mTexture;
};

} // namespace HiLo
