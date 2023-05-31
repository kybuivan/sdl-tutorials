#include "TextRendering.hpp"

#include <SDL_ttf.h>

#include "Assert.hpp"
#include "Font.hpp"
#include "Renderer.hpp"

namespace HiLo {

auto getTextTexture(std::string const& text, Color color) noexcept -> Texture
{
    auto rawSurface = TTF_RenderText_Blended(Font::instance().getRawPointer(),
        text.c_str(), *reinterpret_cast<SDL_Color*>(&color));
    SDL_assert(rawSurface);
    auto rawTexture = SDL_CreateTextureFromSurface(
        Renderer::instance().getRawPointer(), rawSurface);
    SDL_assert(rawTexture);
    SDL_FreeSurface(rawSurface);
    Texture texture;
    texture.setRawPointer(rawTexture);
    return texture;
}

} // namespace HiLo
