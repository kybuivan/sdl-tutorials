#include "Sprite.hpp"

#include "Renderer.hpp"

namespace HiLo
{

Sprite::Sprite(Texture texture, Rectangle const &destinationBounds) noexcept
    : mTexture{std::move(texture)}, mDestinationBounds{destinationBounds}
{
}

auto Sprite::draw() const noexcept -> void
{
    Renderer::instance().copy(mTexture, sourceBounds(), mDestinationBounds);
}

auto Sprite::sourceBounds() const noexcept -> std::optional<Rectangle>
{
    return std::nullopt;
}

} // namespace HiLo
