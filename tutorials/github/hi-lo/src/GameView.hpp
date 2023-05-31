#pragma once

#include "CardView.hpp"
#include "GameModel.hpp"
#include "Observer.hpp"

#include "FixedTextSprite.hpp"
#include "GameViewButton.hpp"
#include "ScoreSprite.hpp"
#include "Sprite.hpp"

namespace HiLo
{

class GameView : public Observer<GameViewButton>, public Observable<GameView>
{
public:
    enum Event
    {
        DownButtonPressed,
        UpButtonPressed,
        PauseButtonPressed
    };

    auto receiveEvent(GameViewButton *, GameViewButton::Event const &)
        -> void final;

    GameView() noexcept;

    auto update(GameModel const &) noexcept -> void;

    auto handleEvent(SDL_Event const &) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    Sprite mBackgroundSprite;
    FixedTextSprite mHighScoreTitleSprite;
    ScoreSprite mHighScoreNumberSprite;
    FixedTextSprite mCurrentScoreTitleSprite;
    ScoreSprite mCurrentScoreNumberSprite;
    CardView mCardView;
    GameViewButton mPauseButton;
    GameViewButton mDownButton;
    GameViewButton mUpButton;
};

} // namespace HiLo
