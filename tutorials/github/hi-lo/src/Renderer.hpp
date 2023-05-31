#pragma once

#include <memory>
#include <optional>

#include <SDL.h>

#include "Color.hpp"
#include "Rectangle.hpp"
#include "Size.hpp"
#include "Texture.hpp"

namespace HiLo {

class Renderer {
public:
    static auto instance() noexcept -> Renderer&;

    auto getRawPointer() const noexcept -> SDL_Renderer*;

    auto setDrawColor(Color) noexcept -> void;

    auto clear() noexcept -> void;

    auto fill(Rectangle const&) noexcept -> void;

    auto copy(Texture const&, std::optional<Rectangle> const& sourceBounds,
        std::optional<Rectangle> const& destinationBounds) noexcept -> void;

    auto present() noexcept -> void;

    auto setLogicalSize(Size const&) noexcept -> void;

private:
    Renderer() noexcept;

    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> mRenderer;
};

} // namespace HiLo
