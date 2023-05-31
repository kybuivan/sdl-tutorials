#pragma once

#include <memory>

#include <SDL.h>

namespace HiLo
{

class Window
{
public:
    static auto instance() noexcept -> Window &;

    auto getRawPointer() const noexcept -> SDL_Window *;

private:
    Window() noexcept;

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> mWindow;
};

} // namespace HiLo
