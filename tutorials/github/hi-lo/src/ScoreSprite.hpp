#pragma once

#include "Color.hpp"
#include "Score.hpp"
#include "Sprite.hpp"

namespace HiLo
{

class ScoreSprite : public Sprite
{
public:
    ScoreSprite(Color textColor, Rectangle const &destinationBounds) noexcept;

    auto setScore(Score) noexcept -> void;

private:
    Color mTextColor;
    Rectangle mTextBounds;
};

} // namespace HiLo
