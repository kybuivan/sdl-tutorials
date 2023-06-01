#include "size.hpp"

Size::Size(int width, int height) noexcept : mWidth(width), mHeight(height)
{
}

auto Size::width() const noexcept -> int
{
    return mWidth;
}

auto Size::setWidth(int width) noexcept -> void
{
    mWidth = width;
}

auto Size::height() const noexcept -> int
{
    return mHeight;
}

auto Size::setHeight(int height) noexcept -> void
{
    mHeight = height;
}
