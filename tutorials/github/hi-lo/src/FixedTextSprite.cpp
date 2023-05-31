#include "FixedTextSprite.hpp"

#include "RectangleFunctions.hpp"
#include "TextRendering.hpp"

namespace HiLo
{

FixedTextSprite::FixedTextSprite(std::string const &text,
                                 Color textColor,
                                 Rectangle const &destinationBounds) noexcept
    : Sprite{getTextTexture(text, textColor)}
{
    // Cannot access member of Sprite before Sprite gets fully constructed.
    mDestinationBounds = fittingRectangle(mTexture.size(), destinationBounds);
}

} // namespace HiLo
