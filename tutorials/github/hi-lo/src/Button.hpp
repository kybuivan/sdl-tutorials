#pragma once

#include "ButtonEventHandler.hpp"
#include "Observer.hpp"
#include "Rectangle.hpp"
#include "Texture.hpp"

namespace HiLo
{

class Button : public ButtonEventHandler, public Observable<Button>
{
public:
    using Event = ButtonEventHandler::Event;

    Button(Texture normalTexture,
           Texture mouseoverTexture,
           Texture holdTexture,
           Rectangle const &bounds) noexcept;

    auto draw() const noexcept -> void;

private:
    virtual auto hitbox() const noexcept -> Rectangle final;

    virtual auto onMouseoverStart() noexcept -> void final;

    virtual auto onMouseoverEnd() noexcept -> void final;

    virtual auto onHoldStart() noexcept -> void final;

    virtual auto onHoldEnd() noexcept -> void final;

    virtual auto onPressSuccess() noexcept -> void final;

    Texture mNormalTexture;
    Texture mMouseoverTexture;
    Texture mHoldTexture;
    Texture *mActiveTexture;
    Rectangle mDestination;
};

} // namespace HiLo
