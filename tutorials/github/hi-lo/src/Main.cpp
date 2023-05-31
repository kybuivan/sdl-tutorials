#include "Game.hpp"
#include "IMGSubsystem.hpp"
#include "Renderer.hpp"
#include "SDLSubsystem.hpp"
#include "TTFSubsystem.hpp"
#include "Window.hpp"

namespace HiLo
{

auto Main() noexcept -> void
{
    SDLSubsystem::initialize();
    IMGSubsystem::initialize();
    TTFSubsystem::initialize();
    Window::instance();
    Renderer::instance();
    Game game;
    SDL_Event event;
    bool isRunning{true};
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            game.handleEvent(event);
        }
        Renderer::instance().setDrawColor({0, 0, 0, 255});
        Renderer::instance().clear();
        game.draw();
        Renderer::instance().present();
    }
}

} // namespace HiLo

auto main(int argc, char *argv[]) -> int
{
    HiLo::Main();
    return 0;
}
