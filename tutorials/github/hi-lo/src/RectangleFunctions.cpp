#include "RectangleFunctions.hpp"

#include "Assert.hpp"

namespace HiLo
{

auto scale(Size &size, double const factor) noexcept -> void
{
    SDL_assert(0 <= factor);
    size.setWidth(static_cast<int>(size.width() * factor));
    size.setHeight(static_cast<int>(size.height() * factor));
}

auto scaleToFit(Size &source, Size const &destination) noexcept -> void
{
    auto factor = static_cast<double>(destination.width()) / source.width();
    if (factor * source.height() > destination.height())
    {
        factor = static_cast<double>(destination.height()) / source.height();
    }
    scale(source, factor);
}

auto fittingRectangle(Size size, Rectangle const &destination) noexcept
    -> Rectangle
{
    scaleToFit(size, destination.size());
    return {destination.x() + (destination.width() - size.width()) / 2,
            destination.y() + (destination.height() - size.height()) / 2,
            size};
}

static auto scale(Rectangle &rectangle, double scaleFactor) noexcept -> void
{
    SDL_assert(0 <= scaleFactor);
    rectangle.setWidth(static_cast<int>(rectangle.width() * scaleFactor));
    rectangle.setHeight(static_cast<int>(rectangle.height() * scaleFactor));
}

auto scaleInPlace(Rectangle &rectangle, double scaleFactor) noexcept -> void
{
    auto const oldSize = rectangle.size();
    scale(rectangle, scaleFactor);
    rectangle.setX(rectangle.x() + (oldSize.width() - rectangle.width()) / 2);
    rectangle.setY(rectangle.y() + (oldSize.height() - rectangle.height()) / 2);
}

auto isPointInRectangle(Point const &point, Rectangle const &rectangle) noexcept
    -> bool
{
    return SDL_PointInRect(reinterpret_cast<SDL_Point const *>(&point),
                           reinterpret_cast<SDL_Rect const *>(&rectangle));
}

} // namespace HiLo
