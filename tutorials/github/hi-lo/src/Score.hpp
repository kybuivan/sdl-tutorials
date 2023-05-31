#pragma once

namespace HiLo {

class Score {
public:
    constexpr Score() noexcept;

    constexpr auto count() const noexcept -> int;

    constexpr auto increment() noexcept -> void;

    constexpr auto reset() noexcept -> void;

private:
    int mCount;
};

constexpr auto operator==(Score lhs, Score rhs) noexcept -> bool;

constexpr auto operator!=(Score lhs, Score rhs) noexcept -> bool;

constexpr auto operator<(Score lhs, Score rhs) noexcept -> bool;

constexpr auto operator>(Score lhs, Score rhs) noexcept -> bool;

constexpr auto operator<=(Score lhs, Score rhs) noexcept -> bool;

constexpr auto operator>=(Score lhs, Score rhs) noexcept -> bool;

constexpr Score::Score() noexcept
    : mCount{0}
{
}

constexpr auto Score::count() const noexcept -> int
{
    return mCount;
}

constexpr auto Score::increment() noexcept -> void
{
    ++mCount;
}

constexpr auto Score::reset() noexcept -> void
{
    mCount = 0;
}

constexpr auto operator==(Score lhs, Score rhs) noexcept -> bool
{
    return lhs.count() == rhs.count();
}

constexpr auto operator!=(Score lhs, Score rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

constexpr auto operator<(Score lhs, Score rhs) noexcept -> bool
{
    return lhs.count() < rhs.count();
}

constexpr auto operator>(Score lhs, Score rhs) noexcept -> bool
{
    return lhs.count() > rhs.count();
}

constexpr auto operator<=(Score lhs, Score rhs) noexcept -> bool
{
    return !(lhs > rhs);
}

constexpr auto operator>=(Score lhs, Score rhs) noexcept -> bool
{
    return !(lhs < rhs);
}

} // namespace HiLo
