#include "Button.hpp"
#include "RectangleFunctions.hpp"
#include "Renderer.hpp"

namespace HiLo
{

Button::Button(Texture normalTexture,
               Texture mouseoverTexture,
               Texture holdTexture,
               Rectangle const &bounds) noexcept
    : mNormalTexture{std::move(normalTexture)},
      mMouseoverTexture{std::move(mouseoverTexture)},
      mHoldTexture{std::move(holdTexture)}, mActiveTexture{&mNormalTexture},
      mDestination{fittingRectangle(mNormalTexture.size(), bounds)}
{
}

auto Button::draw() const noexcept -> void
{
    Renderer::instance().copy(*mActiveTexture, std::nullopt, mDestination);
}

auto Button::hitbox() const noexcept -> Rectangle
{
    return mDestination;
}

auto Button::onMouseoverStart() noexcept -> void
{
    mActiveTexture = &mMouseoverTexture;
}

auto Button::onMouseoverEnd() noexcept -> void
{
    mActiveTexture = &mNormalTexture;
}

auto Button::onHoldStart() noexcept -> void
{
    mActiveTexture = &mHoldTexture;
}

auto Button::onHoldEnd() noexcept -> void
{
    if (isMouseovered())
    {
        mActiveTexture = &mMouseoverTexture;
    }
    else
    {
        mActiveTexture = &mNormalTexture;
    }
}

auto Button::onPressSuccess() noexcept -> void
{
    notifyObserver(*this, Event::PressSuccess);
}

} // namespace HiLo
