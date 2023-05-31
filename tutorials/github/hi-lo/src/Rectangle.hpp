#pragma once

#include "Point.hpp"
#include "Size.hpp"

namespace HiLo
{

class Rectangle : private Point, private Size
{
public:
    using Point::setX;
    using Point::setY;
    using Point::x;
    using Point::y;
    using Size::height;
    using Size::setHeight;
    using Size::setWidth;
    using Size::width;

    Rectangle() noexcept = default;

    Rectangle(Point const &position, Size const &) noexcept;

    Rectangle(Point const &position, int width, int height) noexcept;

    Rectangle(int x, int y, Size const &) noexcept;

    Rectangle(int x, int y, int width, int height);

    auto position() const noexcept -> Point;

    auto setPosition(Point const &position) noexcept -> void;

    auto size() const noexcept -> Size;

    auto setSize(Size const &) noexcept -> void;
};

} // namespace HiLo
