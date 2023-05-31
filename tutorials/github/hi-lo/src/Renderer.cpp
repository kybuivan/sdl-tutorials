#include "Renderer.hpp"

#include "Assert.hpp"
#include "Window.hpp"

namespace HiLo {

auto Renderer::instance() noexcept -> Renderer&
{
    static Renderer renderer;
    return renderer;
}

auto Renderer::getRawPointer() const noexcept -> SDL_Renderer*
{
    return mRenderer.get();
}

auto Renderer::setDrawColor(Color color) noexcept -> void
{
    if (SDL_SetRenderDrawColor(mRenderer.get(), color.red(), color.green(),
        color.blue(), color.alpha()) < 0) {
        SDL_assert(false);
    }
}

auto Renderer::clear() noexcept -> void
{
    if (SDL_RenderClear(mRenderer.get()) < 0) {
        SDL_assert(false);
    }
}

auto Renderer::fill(Rectangle const& rectangle) noexcept -> void
{
    if (SDL_RenderFillRect(mRenderer.get(),
        reinterpret_cast<SDL_Rect const*>(&rectangle)) < 0) {
        SDL_assert(false);
    }
}

auto Renderer::copy(Texture const& texture,
    std::optional<Rectangle> const& sourceBounds,
    std::optional<Rectangle> const& destinationBounds) noexcept -> void
{
    auto const srcrect = [&]() {
        if (sourceBounds.has_value()) {
            return reinterpret_cast<SDL_Rect const*>(&sourceBounds.value());
        } else {
            return static_cast<SDL_Rect const*>(nullptr);
        }
    }();
    auto const dstrect = [&]() {
        if (destinationBounds.has_value()) {
            return reinterpret_cast<SDL_Rect const*>(
                &destinationBounds.value());
        } else {
            return static_cast<SDL_Rect const*>(nullptr);
        }
    }();
    if (SDL_RenderCopy(mRenderer.get(), texture.getRawPointer(), srcrect,
        dstrect) < 0) {
        SDL_assert(false);
    }
}

auto Renderer::present() noexcept -> void
{
    SDL_RenderPresent(mRenderer.get());
}

auto Renderer::setLogicalSize(Size const& size) noexcept -> void
{
    if (SDL_RenderSetLogicalSize(mRenderer.get(), size.width(), size.height())
        < 0) {
        SDL_assert(false);
    }
}

static Size const canvasSize{1080, 1920};

Renderer::Renderer() noexcept
    : mRenderer{SDL_CreateRenderer(Window::instance().getRawPointer(), -1,
        SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer}
{
    SDL_assert(mRenderer);
    setLogicalSize(canvasSize);
    if (SDL_SetRenderDrawBlendMode(mRenderer.get(), SDL_BLENDMODE_BLEND) < 0) {
        SDL_assert(false);
    }
}

} // namespace HiLo
