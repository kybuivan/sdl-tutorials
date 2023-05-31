#pragma once

#include "Button.hpp"

namespace HiLo
{

class GamePauseDialog : public Observer<Button>,
                        public Observable<GamePauseDialog>
{
public:
    enum class Event
    {
        ResumeButtonPressed,
        BackToMenuButtonPressed
    };

    auto receiveEvent(Button *, Button::Event const &) noexcept -> void final;

    GamePauseDialog() noexcept;

    auto handleEvent(SDL_Event const &) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    Texture mDialogPlate;
    Rectangle mDialogPlateDestination;
    Button mResumeButton;
    Button mBackToMenuButton;
};

} // namespace HiLo
