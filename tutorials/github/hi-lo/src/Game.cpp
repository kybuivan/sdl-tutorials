#include "Game.hpp"

namespace HiLo
{

auto Game::receiveEvent(MenuSceneView *menuSceneView,
                        MenuSceneView::Event const &event) noexcept -> void
{
    if (menuSceneView == &mMenuSceneView)
    {
        switch (event)
        {
        case MenuSceneView::Event::StartButtonPressed:
            mActiveScene = Scene::Game;
            break;
        case MenuSceneView::Event::CreditsButtonPressed:
            mActiveScene = Scene::Credits;
            break;
        default:
            break;
        }
    }
}

auto Game::receiveEvent(GameScene *gameScene,
                        GameScene::Event const &event) noexcept -> void
{
    if (gameScene == &mGameScene)
    {
        if (event == GameScene::Event::BackToMenuRequested)
        {
            mActiveScene = Scene::Menu;
        }
    }
}

auto Game::receiveEvent(CreditsView *creditsView,
                        CreditsView::Event const &event) noexcept -> void
{
    if (creditsView == &mCreditsView)
    {
        if (event == CreditsView::Event::BackToMenuButtonPressed)
        {
            mActiveScene = Scene::Menu;
        }
    }
}

Game::Game() noexcept
{
    setObserver(mMenuSceneView, this);
    setObserver(mGameScene, this);
    setObserver(mCreditsView, this);
}

auto Game::handleEvent(SDL_Event const &event) noexcept -> void
{
    switch (mActiveScene)
    {
    case Scene::Menu:
        mMenuSceneView.handleEvent(event);
        break;
    case Scene::Game:
        mGameScene.handleEvent(event);
        break;
    case Scene::Credits:
        mCreditsView.handleEvent(event);
        break;
    default:
        break;
    }
}

auto Game::draw() const noexcept -> void
{
    switch (mActiveScene)
    {
    case Scene::Menu:
        mMenuSceneView.draw();
        break;
    case Scene::Game:
        mGameScene.draw();
        break;
    case Scene::Credits:
        mCreditsView.draw();
        break;
    default:
        break;
    }
}

} // namespace HiLo
