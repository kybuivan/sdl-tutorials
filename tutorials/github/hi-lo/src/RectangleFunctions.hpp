#pragma once

#include "Rectangle.hpp"
#include "Size.hpp"

namespace HiLo
{

auto scale(Size &, double factor) noexcept -> void;

auto scaleToFit(Size &source, Size const &destination) noexcept -> void;

auto fittingRectangle(Size, Rectangle const &destination) noexcept -> Rectangle;

auto scaleInPlace(Rectangle &, double scaleFactor) noexcept -> void;

auto isPointInRectangle(Point const &, Rectangle const &) noexcept -> bool;

} // namespace HiLo
