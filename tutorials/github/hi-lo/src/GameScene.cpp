#include "GameScene.hpp"

namespace HiLo
{

auto GameScene::receiveEvent(GameView *gameView,
                             GameView::Event const &event) noexcept -> void
{
    if (gameView == &mGameView)
    {
        switch (event)
        {
        case GameView::Event::DownButtonPressed:
            mGameModel.guess(GameModel::Option::under);
            mGameView.update(mGameModel);
            break;
        case GameView::Event::UpButtonPressed:
            mGameModel.guess(GameModel::Option::over);
            mGameView.update(mGameModel);
            break;
        case GameView::Event::PauseButtonPressed:
            mIsPauseDialogInFocus = true;
            break;
        default:
            break;
        }
    }
}

auto GameScene::receiveEvent(GamePauseDialog *pauseDialog,
                             GamePauseDialog::Event const &event) noexcept
    -> void
{
    if (pauseDialog == &mGamePauseDialog)
    {
        switch (event)
        {
        case GamePauseDialog::Event::ResumeButtonPressed:
            mIsPauseDialogInFocus = false;
            break;
        case GamePauseDialog::Event::BackToMenuButtonPressed:
            notifyObserver(*this, Event::BackToMenuRequested);
            mIsPauseDialogInFocus = false;
            mGameModel.reset();
            mGameView.update(mGameModel);
            break;
        default:
            break;
        }
    }
}

GameScene::GameScene() noexcept
{
    mGameView.update(mGameModel);
    setObserver(mGameView, this);
    setObserver(mGamePauseDialog, this);
}

auto GameScene::handleEvent(SDL_Event const &event) noexcept -> void
{
    if (mIsPauseDialogInFocus)
    {
        mGamePauseDialog.handleEvent(event);
    }
    else
    {
        mGameView.handleEvent(event);
    }
}

auto GameScene::draw() const noexcept -> void
{
    mGameView.draw();
    if (mIsPauseDialogInFocus)
    {
        mGamePauseDialog.draw();
    }
}

} // namespace HiLo
