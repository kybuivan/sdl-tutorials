#include "CreditsView.hpp"

#include "ImageLoading.hpp"

namespace HiLo
{

constexpr char const *backgroundTexturePath{"Assets/creditsBackground.png"};
static Rectangle const backgroundBounds{0, 0, 1080, 1920};

constexpr char const *backToMenuButtonTextureNormalPath{
    "Assets/buttonBackToMenuNormal.png"};
constexpr char const *backToMenuButtonTextureMouseoverPath{
    "Assets/buttonBackToMenuBubble.png"};
constexpr char const *backToMenuButtonTextureHoldPath{
    "Assets/buttonBackToMenuInvert.png"};
static Rectangle const backToMenuButtonBounds{540 - 300, 1920 - 300, 600, 150};

auto CreditsView::receiveEvent(Button *button,
                               Button::Event const &event) noexcept -> void
{
    if (button == &mBackToMenuButton)
    {
        if (event == Button::Event::PressSuccess)
        {
            notifyObserver(*this, Event::BackToMenuButtonPressed);
        }
    }
}

CreditsView::CreditsView() noexcept
    : mBackground{loadTexture(backgroundTexturePath), backgroundBounds},
      mBackToMenuButton{loadTexture(backToMenuButtonTextureNormalPath),
                        loadTexture(backToMenuButtonTextureMouseoverPath),
                        loadTexture(backToMenuButtonTextureHoldPath),
                        backToMenuButtonBounds}
{
    setObserver(mBackToMenuButton, this);
}

auto CreditsView::handleEvent(SDL_Event const &event) noexcept -> void
{
    mBackToMenuButton.handleEvent(event);
}

auto CreditsView::draw() const noexcept -> void
{
    mBackground.draw();
    mBackToMenuButton.draw();
}

} // namespace HiLo
