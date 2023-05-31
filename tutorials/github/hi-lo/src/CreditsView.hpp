#pragma once

#include "Button.hpp"
#include "Sprite.hpp"

namespace HiLo
{

class CreditsView : public Observable<CreditsView>, public Observer<Button>
{
public:
    enum class Event
    {
        BackToMenuButtonPressed
    };

    auto receiveEvent(Button *, Button::Event const &) noexcept
        -> void override;

    CreditsView() noexcept;

    auto handleEvent(SDL_Event const &) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    Sprite mBackground;
    Button mBackToMenuButton;
};

} // namespace HiLo
