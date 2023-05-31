#pragma once

#include <string>

#include "Color.hpp"
#include "Texture.hpp"

namespace HiLo
{

auto getTextTexture(std::string const &text, Color color) noexcept -> Texture;

} // namespace HiLo
