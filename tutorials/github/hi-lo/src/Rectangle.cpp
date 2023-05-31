#include "Rectangle.hpp"

namespace HiLo {

Rectangle::Rectangle(Point const& position, Size const& size) noexcept
    : Point{position}
    , Size{size}
{
}

Rectangle::Rectangle(Point const& position, int width, int height) noexcept
    : Point{position}
    , Size{width, height}
{
}

Rectangle::Rectangle(int x, int y, Size const& size) noexcept
    : Point{x, y}
    , Size{size}
{
}

Rectangle::Rectangle(int x, int y, int width, int height)
    : Point{x, y}
    , Size{width, height}
{
}

auto Rectangle::position() const noexcept -> Point
{
    return *this;
}

auto Rectangle::setPosition(Point const& position) noexcept -> void
{
    Point::operator=(position);
}

auto Rectangle::size() const noexcept -> Size
{
    return *this;
}

auto Rectangle::setSize(Size const& size) noexcept -> void
{
    Size::operator=(size);
}

} // namespace HiLo
