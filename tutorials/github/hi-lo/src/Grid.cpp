#include "Grid.hpp"

namespace HiLo
{

Grid::Grid(Size const &size, Size const &fieldSize, int innerPadding) noexcept
    : mSize{size}, mFieldSize{fieldSize}, mInnerPadding{innerPadding}
{
}

auto Grid::fieldBounds(int x, int y) const noexcept -> Rectangle
{
    // TODO: Assert to ensure valid arguments are passed in.
    return {x * (mFieldSize.width() + mInnerPadding),
            y * (mFieldSize.height() + mInnerPadding),
            mFieldSize};
}

auto Grid::fieldSize() const noexcept -> Size
{
    return mFieldSize;
}

} // namespace HiLo
