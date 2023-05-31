#pragma once

#include <optional>

#include "Rectangle.hpp"
#include "Texture.hpp"

namespace HiLo {

class Sprite {
public:
    Sprite(Texture, Rectangle const& destinationBounds = Rectangle{}) noexcept;

    auto draw() const noexcept -> void;

protected:
    virtual auto sourceBounds() const noexcept -> std::optional<Rectangle>;

    Texture mTexture;
    Rectangle mDestinationBounds;
};

} // namespace HiLo
