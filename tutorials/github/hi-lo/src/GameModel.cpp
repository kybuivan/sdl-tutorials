#include "GameModel.hpp"

namespace HiLo
{

GameModel::GameModel() noexcept
    : mRng{std::make_unique<std::mt19937>(std::random_device{}())},
      mCard{randomCard()}
{
}

auto GameModel::reset() noexcept -> void
{
    mCurrentScore.reset();
    auto const oldCard = mCard;
    while ((mCard = randomCard()) == oldCard)
    {
    }
}

auto GameModel::guess(GameModel::Option const option) noexcept -> void
{
    auto const oldCard = mCard;
    while ((mCard = randomCard()) == oldCard)
    {
    }
    if (option == Option::over)
    {
        if (mCard.rank() >= oldCard.rank())
        {
            goodGuess();
        }
        else
        {
            badGuess();
        }
    }
    else
    {
        if (mCard.rank() < oldCard.rank())
        {
            goodGuess();
        }
        else
        {
            badGuess();
        }
    }
}

auto GameModel::card() const noexcept -> Card
{
    return mCard;
}

auto GameModel::currentScore() const noexcept -> Score
{
    return mCurrentScore;
}

auto GameModel::highScore() const noexcept -> Score
{
    return mHighScore;
}

auto GameModel::randomCard() const noexcept -> Card
{
    auto const rank = [this]() {
        auto const min = static_cast<int>(Card::Rank::_2);
        auto const max = static_cast<int>(Card::Rank::A);
        std::uniform_int_distribution<> rankDistribution{min, max};
        return static_cast<Card::Rank>(rankDistribution(*mRng));
    }();
    auto const suit = [this]() {
        auto const min = static_cast<int>(Card::Suit::clubs);
        auto const max = static_cast<int>(Card::Suit::spades);
        std::uniform_int_distribution<> suitDistribution{min, max};
        return static_cast<Card::Suit>(suitDistribution(*mRng));
    }();
    return {rank, suit};
}

auto GameModel::goodGuess() noexcept -> void
{
    mCurrentScore.increment();
}

auto GameModel::badGuess() noexcept -> void
{
    if (mCurrentScore > mHighScore)
    {
        mHighScore = mCurrentScore;
    }
    mCurrentScore.reset();
}

} // namespace HiLo
