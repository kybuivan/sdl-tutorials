#pragma once

namespace HiLo
{

class Point
{
public:
    Point() noexcept = default;

    constexpr Point(int x, int y) noexcept;

    constexpr auto x() const noexcept -> int;

    constexpr auto setX(int x) noexcept -> void;

    constexpr auto y() const noexcept -> int;

    constexpr auto setY(int y) noexcept -> void;

private:
    int mX;
    int mY;
};

constexpr Point::Point(int x, int y) noexcept : mX{x}, mY{y}
{
}

constexpr auto Point::x() const noexcept -> int
{
    return mX;
}

constexpr auto Point::setX(int x) noexcept -> void
{
    mX = x;
}

constexpr auto Point::y() const noexcept -> int
{
    return mY;
}

constexpr auto Point::setY(int y) noexcept -> void
{
    mY = y;
}

} // namespace HiLo
