#include "ButtonEventHandler.hpp"

#include "RectangleFunctions.hpp"

namespace HiLo
{

auto ButtonEventHandler::handleEvent(SDL_Event const &event) -> void
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        onMouseMotion(event.motion);
        break;
    case SDL_MOUSEBUTTONDOWN:
        onMouseButtonDown(event.button);
        break;
    case SDL_MOUSEBUTTONUP:
        onMouseButtonUp(event.button);
        break;
    default:
        break;
    }
}

auto ButtonEventHandler::isMouseovered() const noexcept -> bool
{
    return mIsMouseovered;
}

auto ButtonEventHandler::isHeld() const noexcept -> bool
{
    return mIsHeld;
}

auto ButtonEventHandler::onMouseoverStart() -> void
{
}

auto ButtonEventHandler::onMouseoverEnd() -> void
{
}

auto ButtonEventHandler::onHoldStart() -> void
{
}

auto ButtonEventHandler::onHoldEnd() -> void
{
}

auto ButtonEventHandler::onPressSuccess() -> void
{
}

auto ButtonEventHandler::onPressFail() -> void
{
}

auto ButtonEventHandler::onMouseMotion(SDL_MouseMotionEvent const &event)
    -> void
{
    Point const mousePosition{event.x, event.y};
    if (isPointInRectangle(mousePosition, hitbox()))
    {
        if (!mIsMouseovered)
        {
            mIsMouseovered = true;
            onMouseoverStart();
        }
    }
    else
    {
        if (mIsMouseovered)
        {
            mIsMouseovered = false;
            onMouseoverEnd();
        }
        if (mIsHeld)
        {
            mIsHeld = false;
            mIsMouseovered = false;
            onMouseoverEnd();
            onHoldEnd();
            onPressFail();
        }
    }
}

auto ButtonEventHandler::onMouseButtonDown(SDL_MouseButtonEvent const &event)
    -> void
{
    if (mIsMouseovered)
    {
        mIsHeld = true;
        onHoldStart();
    }
}

auto ButtonEventHandler::onMouseButtonUp(SDL_MouseButtonEvent const &event)
    -> void
{
    if (mIsHeld)
    {
        mIsHeld = false;
        onHoldEnd();
        onPressSuccess();
    }
}

} // namespace HiLo
