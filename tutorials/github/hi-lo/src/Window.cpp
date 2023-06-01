#include "Window.hpp"

#include "Assert.hpp"
#include "Display.hpp"
#include "RectangleFunctions.hpp"
#include <size.hpp>

namespace HiLo
{

auto Window::instance() noexcept -> Window &
{
    static Window window;
    return window;
}

auto Window::getRawPointer() const noexcept -> SDL_Window *
{
    return mWindow.get();
}

static Size const aspectRatio{9, 16};
constexpr double debugScale{0.9};

static auto getWindowPointer() noexcept -> SDL_Window *
{
    auto windowSize = aspectRatio;
    scaleToFit(windowSize, getDisplaySize());
    scale(windowSize, debugScale);
    return SDL_CreateWindow("Hi-Lo",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            windowSize.width(),
                            windowSize.height(),
                            SDL_WINDOW_SHOWN);
}

Window::Window() noexcept : mWindow{getWindowPointer(), SDL_DestroyWindow}
{
    SDL_assert(mWindow);
}

} // namespace HiLo
