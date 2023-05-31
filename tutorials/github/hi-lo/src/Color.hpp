#pragma once

#include <SDL.h>

namespace HiLo
{

class Color
{
public:
    Color() noexcept = default;

    constexpr Color(Uint8 red,
                    Uint8 green,
                    Uint8 blue,
                    Uint8 alpha = SDL_ALPHA_OPAQUE) noexcept;

    constexpr auto red() const noexcept -> Uint8;

    constexpr auto setRed(Uint8 value) noexcept -> void;

    constexpr auto green() const noexcept -> Uint8;

    constexpr auto setGreen(Uint8 value) noexcept -> void;

    constexpr auto blue() const noexcept -> Uint8;

    constexpr auto setBlue(Uint8 value) noexcept -> void;

    constexpr auto alpha() const noexcept -> Uint8;

    constexpr auto setAlpha(Uint8 value) noexcept -> void;

private:
    Uint8 mRed;
    Uint8 mGreen;
    Uint8 mBlue;
    Uint8 mAlpha;
};

constexpr Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) noexcept
    : mRed{red}, mGreen{green}, mBlue{blue}, mAlpha{alpha}
{
}

constexpr auto Color::red() const noexcept -> Uint8
{
    return mRed;
}

constexpr auto Color::setRed(Uint8 const value) noexcept -> void
{
    mRed = value;
}

constexpr auto Color::green() const noexcept -> Uint8
{
    return mGreen;
}

constexpr auto Color::setGreen(Uint8 const value) noexcept -> void
{
    mGreen = value;
}

constexpr auto Color::blue() const noexcept -> Uint8
{
    return mBlue;
}

constexpr auto Color::setBlue(Uint8 const value) noexcept -> void
{
    mBlue = value;
}

constexpr auto Color::alpha() const noexcept -> Uint8
{
    return mAlpha;
}

constexpr auto Color::setAlpha(Uint8 const value) noexcept -> void
{
    mAlpha = value;
}

} // namespace HiLo
