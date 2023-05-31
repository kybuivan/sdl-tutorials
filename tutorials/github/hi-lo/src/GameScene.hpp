#pragma once

#include "GameModel.hpp"
#include "GamePauseDialog.hpp"
#include "GameView.hpp"

namespace HiLo
{

class GameScene : public Observable<GameScene>,
                  public Observer<GameView>,
                  public Observer<GamePauseDialog>
{
public:
    enum class Event
    {
        BackToMenuRequested
    };

    auto receiveEvent(GameView *, GameView::Event const &) noexcept
        -> void override;

    auto receiveEvent(GamePauseDialog *,
                      GamePauseDialog::Event const &) noexcept -> void override;

    GameScene() noexcept;

    auto handleEvent(SDL_Event const &) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    GameView mGameView;
    GamePauseDialog mGamePauseDialog;
    bool mIsPauseDialogInFocus{false};
    GameModel mGameModel;
};

} // namespace HiLo
