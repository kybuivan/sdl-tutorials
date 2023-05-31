#include "Size.hpp"

#include "Assert.hpp"

namespace HiLo {

Size::Size(int const width, int const height) noexcept
    : mWidth{width}
    , mHeight{height}
{
    SDL_assert(0 <= width);
    SDL_assert(0 <= height);
}

auto Size::width() const noexcept -> int
{
    return mWidth;
}

auto Size::setWidth(int const width) noexcept -> void
{
    SDL_assert(0 <= width);
    mWidth = width;
}

auto Size::height() const noexcept -> int
{
    return mHeight;
}

auto Size::setHeight(int const height) noexcept -> void
{
    SDL_assert(0 <= height);
    mHeight = height;
}

} // namespace HiLo
