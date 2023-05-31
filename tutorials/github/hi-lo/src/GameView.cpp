#include "GameView.hpp"

#include "ImageLoading.hpp"

namespace HiLo {

auto GameView::receiveEvent(GameViewButton* button,
    GameViewButton::Event const& event) -> void
{
    if (button == &mDownButton) {
        if (event == GameViewButton::Event::PressSuccess) {
            notifyObserver(*this, Event::DownButtonPressed);
        }
    } else if (button == &mUpButton) {
        if (event == GameViewButton::Event::PressSuccess) {
            notifyObserver(*this, Event::UpButtonPressed);
        }
    } else if (button == &mPauseButton) {
        if (event == GameViewButton::Event::PressSuccess) {
            notifyObserver(*this, Event::PauseButtonPressed);
        }
    }
}

constexpr char const* backgroundSpriteTexturePath{"Assets/game-bg.png"};
static Rectangle const backgroundSpriteBounds{0, 0, 1080, 1920};

constexpr char const* highScoreTitleText{"High score:"};
constexpr Color highScoreTitleColor{255, 255, 255};
static Rectangle const highScoreTitleBounds{0, 0, 540, 144};

constexpr Color highScoreNumberColor{255, 255, 255};
static Rectangle const highScoreNumberBounds{540, 0, 540, 144};

constexpr char const* currentScoreTitleText{"Score:"};
constexpr Color currentScoreTitleColor{255, 255, 255};
static Rectangle const currentScoreTitleBounds{0, 144, 540, 144};

constexpr Color currentScoreNumberColor{255, 255, 255};
static Rectangle const currentScoreNumberBounds{540, 144, 540, 144};

constexpr char const* pauseButtonTexturePath{"Assets/pause.png"};
static Rectangle const pauseButtonBounds{960, 20, 100, 100};

constexpr char const* downButtonTexturePath{"Assets/downButton.png"};
constexpr int downButtonBottomOffset{20};
static Rectangle const downButtonBounds{0, 1632 - downButtonBottomOffset, 540,
    288};

constexpr char const* upButtonTexturePath{"Assets/upButton.png"};
constexpr int upButtonBottomOffset{20};
static Rectangle const upButtonBounds{540, 1632 - upButtonBottomOffset, 540,
    288};

GameView::GameView() noexcept
    : mBackgroundSprite{loadTexture(backgroundSpriteTexturePath),
        backgroundSpriteBounds}
    , mHighScoreTitleSprite{highScoreTitleText, highScoreTitleColor,
        highScoreTitleBounds}
    , mHighScoreNumberSprite{highScoreNumberColor, highScoreNumberBounds}
    , mCurrentScoreTitleSprite{currentScoreTitleText, currentScoreTitleColor,
        currentScoreTitleBounds}
    , mCurrentScoreNumberSprite{currentScoreNumberColor,
        currentScoreNumberBounds}
    , mPauseButton{loadTexture(pauseButtonTexturePath), pauseButtonBounds}
    , mDownButton{loadTexture(downButtonTexturePath), downButtonBounds}
    , mUpButton{loadTexture(upButtonTexturePath), upButtonBounds}
{
    setObserver(mDownButton, this);
    setObserver(mUpButton, this);
    setObserver(mPauseButton, this);
}

auto GameView::update(GameModel const& gameModel) noexcept -> void
{
    mHighScoreNumberSprite.setScore(gameModel.highScore());
    mCurrentScoreNumberSprite.setScore(gameModel.currentScore());
    mCardView.setCard(gameModel.card());
}

auto GameView::handleEvent(SDL_Event const& event) noexcept -> void
{
    mPauseButton.handleEvent(event);
    mDownButton.handleEvent(event);
    mUpButton.handleEvent(event);
}

auto GameView::draw() const noexcept -> void
{
    mBackgroundSprite.draw();
    mHighScoreTitleSprite.draw();
    mHighScoreNumberSprite.draw();
    mPauseButton.draw();
    mCurrentScoreTitleSprite.draw();
    mCurrentScoreNumberSprite.draw();
    mCardView.draw();
    mDownButton.draw();
    mUpButton.draw();
}

} // namespace HiLo
