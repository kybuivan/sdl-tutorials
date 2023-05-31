#pragma once

#include "ButtonEventHandler.hpp"
#include "Observer.hpp"
#include "Sprite.hpp"

namespace HiLo
{

class GameViewButton : public Sprite,
                       public ButtonEventHandler,
                       public Observable<GameViewButton>
{
public:
    using Event = ButtonEventHandler::Event;

    GameViewButton(Texture, Rectangle const &bounds) noexcept;

private:
    auto hitbox() const -> Rectangle final;

    auto onMouseoverStart() noexcept -> void final;

    auto onMouseoverEnd() noexcept -> void final;

    auto onHoldStart() noexcept -> void final;

    auto onHoldEnd() noexcept -> void final;

    auto onPressSuccess() noexcept -> void final;
};

} // namespace HiLo
