#pragma once

#include "Rectangle.hpp"
#include <size.hpp>

namespace HiLo
{

class Grid
{
public:
    Grid() noexcept = default;

    Grid(Size const &size, Size const &fieldSize, int innerPadding) noexcept;

    auto fieldBounds(int x, int y) const noexcept -> Rectangle;

    auto fieldSize() const noexcept -> Size;

private:
    Size mSize;
    Size mFieldSize;
    int mInnerPadding;
};

} // namespace HiLo
