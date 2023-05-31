#pragma once

#include <string>

#include "Color.hpp"
#include "Sprite.hpp"

namespace HiLo
{

class FixedTextSprite : public Sprite
{
public:
    FixedTextSprite(std::string const &text,
                    Color textColor,
                    Rectangle const &destinationBounds) noexcept;
};

} // namespace HiLo
