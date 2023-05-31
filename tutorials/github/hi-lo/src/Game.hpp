#pragma once

#include "CreditsView.hpp"
#include "GameScene.hpp"
#include "MenuSceneView.hpp"

namespace HiLo
{

class Game : public Observer<MenuSceneView>,
             public Observer<GameScene>,
             public Observer<CreditsView>
{
public:
    auto receiveEvent(MenuSceneView *, MenuSceneView::Event const &) noexcept
        -> void override;

    auto receiveEvent(GameScene *, GameScene::Event const &) noexcept
        -> void override;

    auto receiveEvent(CreditsView *, CreditsView::Event const &) noexcept
        -> void override;

    Game() noexcept;

    auto handleEvent(SDL_Event const &) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    enum class Scene
    {
        Menu,
        Game,
        Credits
    };

    Scene mActiveScene{Scene::Menu};
    MenuSceneView mMenuSceneView;
    GameScene mGameScene;
    CreditsView mCreditsView;
};

} // namespace HiLo
