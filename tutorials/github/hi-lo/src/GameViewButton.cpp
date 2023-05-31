#include "GameViewButton.hpp"

#include "RectangleFunctions.hpp"
#include "Renderer.hpp"

namespace HiLo
{

GameViewButton::GameViewButton(Texture texture,
                               Rectangle const &bounds) noexcept
    : Sprite{std::move(texture)}
{
    mDestinationBounds = fittingRectangle(mTexture.size(), bounds);
}

auto GameViewButton::hitbox() const -> Rectangle
{
    return mDestinationBounds;
}

auto GameViewButton::onMouseoverStart() noexcept -> void
{
    mTexture.setColorMod(144, 144, 144);
}

auto GameViewButton::onMouseoverEnd() noexcept -> void
{
    mTexture.setColorMod(255, 255, 255);
}

auto GameViewButton::onHoldStart() noexcept -> void
{
    mTexture.setColorMod(255, 144, 144);
}

auto GameViewButton::onHoldEnd() noexcept -> void
{
    if (isMouseovered())
    {
        mTexture.setColorMod(144, 144, 144);
    }
    else
    {
        mTexture.setColorMod(255, 255, 255);
    }
}

auto GameViewButton::onPressSuccess() noexcept -> void
{
    notifyObserver(*this, Event::PressSuccess);
}

} // namespace HiLo
