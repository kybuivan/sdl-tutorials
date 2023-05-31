#pragma once

#include "Button.hpp"
#include "FixedTextSprite.hpp"
#include "Sprite.hpp"

namespace HiLo
{

class MenuSceneView : public Observer<Button>, public Observable<MenuSceneView>
{
public:
    enum class Event
    {
        StartButtonPressed,
        CreditsButtonPressed
    };

    MenuSceneView() noexcept;

    auto receiveEvent(Button *, Button::Event const &) noexcept
        -> void override;

    auto handleEvent(SDL_Event const &) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    Sprite mBackgroundSprite;
    FixedTextSprite mGameTitleSprite;
    Button mStartButton;
    Button mCreditsButton;
};

} // namespace HiLo
