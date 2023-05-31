#pragma once

#include <SDL.h>

#include "Rectangle.hpp"

namespace HiLo
{

class ButtonEventHandler
{
public:
    enum class Event
    {
        MouseoverStart,
        MouseoverEnd,
        HoldStart,
        HoldEnd,
        PressSuccess,
        PressFail
    };

    auto handleEvent(SDL_Event const &) -> void;

    auto isMouseovered() const noexcept -> bool;

    auto isHeld() const noexcept -> bool;

protected:
    virtual auto hitbox() const -> Rectangle = 0;

    virtual auto onMouseoverStart() -> void;

    virtual auto onMouseoverEnd() -> void;

    virtual auto onHoldStart() -> void;

    virtual auto onHoldEnd() -> void;

    virtual auto onPressSuccess() -> void;

    virtual auto onPressFail() -> void;

private:
    auto onMouseMotion(SDL_MouseMotionEvent const &) -> void;

    auto onMouseButtonDown(SDL_MouseButtonEvent const &) -> void;

    auto onMouseButtonUp(SDL_MouseButtonEvent const &) -> void;

    bool mIsMouseovered{false};
    bool mIsHeld{false};
};

} // namespace HiLo
