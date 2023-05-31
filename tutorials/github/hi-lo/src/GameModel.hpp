#pragma once

#include <memory>
#include <random>

#include "Card.hpp"
#include "Score.hpp"

namespace HiLo
{

class GameModel
{
public:
    enum Option
    {
        over,
        under
    };

    GameModel() noexcept;

    auto reset() noexcept -> void;

    auto guess(Option) noexcept -> void;

    auto card() const noexcept -> Card;

    auto currentScore() const noexcept -> Score;

    auto highScore() const noexcept -> Score;

private:
    auto randomCard() const noexcept -> Card;

    auto goodGuess() noexcept -> void;

    auto badGuess() noexcept -> void;

    std::unique_ptr<std::mt19937> mRng;
    Card mCard;
    Score mCurrentScore;
    Score mHighScore;
};

} // namespace HiLo
