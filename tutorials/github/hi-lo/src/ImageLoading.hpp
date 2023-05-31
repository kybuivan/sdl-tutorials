#pragma once

#include <string>

#include "Texture.hpp"

namespace HiLo
{

auto loadTexture(std::string const &path) noexcept -> Texture;

} // namespace HiLo
