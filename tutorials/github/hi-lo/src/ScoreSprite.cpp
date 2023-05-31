#include "ScoreSprite.hpp"

#include <string>

#include "RectangleFunctions.hpp"
#include "TextRendering.hpp"

namespace HiLo {

ScoreSprite::ScoreSprite(Color textColor, Rectangle const& destinationBounds)
    noexcept
    : Sprite{getTextTexture("0", textColor)}
    , mTextColor{textColor}
    , mTextBounds{destinationBounds}
{
    // Cannot access member of Sprite before Sprite gets fully constructed.
    mDestinationBounds = fittingRectangle(mTexture.size(), mTextBounds);
}

auto ScoreSprite::setScore(Score score) noexcept -> void
{
    auto const text = std::to_string(score.count());
    mTexture = getTextTexture(text, mTextColor);
    mDestinationBounds = fittingRectangle(mTexture.size(), mTextBounds);
}

} // namespace HiLo
