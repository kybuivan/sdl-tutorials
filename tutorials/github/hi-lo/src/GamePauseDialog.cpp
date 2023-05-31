#include "GamePauseDialog.hpp"

#include "ImageLoading.hpp"
#include "Renderer.hpp"

namespace HiLo
{

auto GamePauseDialog::receiveEvent(Button *button,
                                   Button::Event const &event) noexcept -> void
{
    if (button == &mResumeButton)
    {
        if (event == Button::Event::PressSuccess)
        {
            notifyObserver(*this, Event::ResumeButtonPressed);
        }
    }
    else if (button == &mBackToMenuButton)
    {
        if (event == Button::Event::PressSuccess)
        {
            notifyObserver(*this, Event::BackToMenuButtonPressed);
        }
    }
}

constexpr char const *dialogPlateTexturePath{"Assets/uiPlate.png"};
constexpr int dialogPlateWidth{800};
constexpr int dialogPlateHeight{525};
static Rectangle const dialogPlateBounds{540 - dialogPlateWidth / 2,
                                         960 - dialogPlateHeight / 2,
                                         dialogPlateWidth,
                                         dialogPlateHeight};

constexpr char const *resumeButtonTextureNormalPath{
    "Assets/buttonResumeNormal.png"};
constexpr char const *resumeButtonTextureMouseoverPath{
    "Assets/buttonResumeBubble.png"};
constexpr char const *resumeButtonTextureHoldPath{
    "Assets/buttonResumeInvert.png"};
static Rectangle const resumeButtonBounds{dialogPlateBounds.x() + 100,
                                          dialogPlateBounds.y() + 75,
                                          600,
                                          150};

constexpr char const *backToMenuButtonTextureNormalPath{
    "Assets/buttonBackToMenuNormal.png"};
constexpr char const *backToMenuButtonTextureMouseoverPath{
    "Assets/buttonBackToMenuBubble.png"};
constexpr char const *backToMenuButtonTextureHoldPath{
    "Assets/buttonBackToMenuInvert.png"};
static Rectangle const backToMenuButtonBounds{
    dialogPlateBounds.x() + 100,
    resumeButtonBounds.y() + resumeButtonBounds.height() + 75,
    600,
    150};

GamePauseDialog::GamePauseDialog() noexcept
    : mDialogPlate{loadTexture(dialogPlateTexturePath)},
      mDialogPlateDestination{dialogPlateBounds},
      mResumeButton{loadTexture(resumeButtonTextureNormalPath),
                    loadTexture(resumeButtonTextureMouseoverPath),
                    loadTexture(resumeButtonTextureHoldPath),
                    resumeButtonBounds},
      mBackToMenuButton{loadTexture(backToMenuButtonTextureNormalPath),
                        loadTexture(backToMenuButtonTextureMouseoverPath),
                        loadTexture(backToMenuButtonTextureHoldPath),
                        backToMenuButtonBounds}
{
    setObserver(mResumeButton, this);
    setObserver(mBackToMenuButton, this);
}

auto GamePauseDialog::handleEvent(SDL_Event const &event) noexcept -> void
{
    mResumeButton.handleEvent(event);
    mBackToMenuButton.handleEvent(event);
}

auto GamePauseDialog::draw() const noexcept -> void
{
    Renderer::instance().setDrawColor({0, 0, 0, 169});
    Renderer::instance().fill({0, 0, 1080, 1920});
    Renderer::instance().copy(mDialogPlate,
                              std::nullopt,
                              mDialogPlateDestination);
    mResumeButton.draw();
    mBackToMenuButton.draw();
}

} // namespace HiLo
