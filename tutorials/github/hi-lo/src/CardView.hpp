#pragma once

#include "Card.hpp"
#include "Rectangle.hpp"
#include "Texture.hpp"

namespace HiLo
{

class CardView
{
public:
    CardView() noexcept;

    auto setCard(Card const &) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    Texture mCardSpritesheet;
    Rectangle mSource;
    Rectangle mDestination;
};

} // namespace HiLo
