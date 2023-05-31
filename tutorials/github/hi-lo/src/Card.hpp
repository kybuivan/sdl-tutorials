#pragma once

namespace HiLo {

class Card {
public:
    enum class Rank {
        _2, _3, _4, _5, _6, _7, _8, _9, T, J, Q, K, A
    };

    enum class Suit {
        clubs, diamonds, hearts, spades
    };

    Card() noexcept = default;

    constexpr Card(Rank, Suit) noexcept;

    constexpr auto rank() const noexcept -> Rank;

    constexpr auto suit() const noexcept -> Suit;

private:
    Rank mRank;
    Suit mSuit;
};

constexpr auto operator==(Card const& lhs, Card const& rhs) noexcept -> bool;

constexpr auto operator!=(Card const& lhs, Card const& rhs) noexcept -> bool;

constexpr Card::Card(Card::Rank const rank, Card::Suit const suit) noexcept
    : mRank{rank}
    , mSuit{suit}
{
}

constexpr auto Card::rank() const noexcept -> Card::Rank
{
    return mRank;
}

constexpr auto Card::suit() const noexcept -> Card::Suit
{
    return mSuit;
}

constexpr auto operator==(Card const& lhs, Card const& rhs) noexcept -> bool
{
    return lhs.rank() == rhs.rank() && lhs.suit() == rhs.suit();
}

constexpr auto operator!=(Card const& lhs, Card const& rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace HiLo
