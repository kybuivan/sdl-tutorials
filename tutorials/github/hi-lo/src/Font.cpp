#include "Font.hpp"

#include "Assert.hpp"

namespace HiLo
{

auto Font::instance() noexcept -> Font &
{
    static Font font;
    return font;
}

auto Font::getRawPointer() const noexcept -> TTF_Font *
{
    return mFont.get();
}

auto Font::setOutline(int outline) noexcept -> void
{
    TTF_SetFontOutline(mFont.get(), outline);
}

auto Font::setStyle(Style style) noexcept -> void
{
    TTF_SetFontStyle(mFont.get(), static_cast<int>(style));
}

Font::Font() noexcept
    : mFont{TTF_OpenFont("Assets/Spectral-Regular.ttf", 128), TTF_CloseFont}
{
    SDL_assert(mFont);
}

} // namespace HiLo
