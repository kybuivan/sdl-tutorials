#pragma once

#include <memory>

#include <SDL_ttf.h>

namespace HiLo
{

class Font
{
public:
    enum class Style;

    static auto instance() noexcept -> Font &;

    auto getRawPointer() const noexcept -> TTF_Font *;

    auto setOutline(int) noexcept -> void;

    auto setStyle(Style) noexcept -> void;

private:
    Font() noexcept;

    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> mFont;
};

enum class Font::Style
{
    Normal = TTF_STYLE_NORMAL,
    Bold = TTF_STYLE_BOLD,
    Italic = TTF_STYLE_ITALIC,
    Underline = TTF_STYLE_UNDERLINE,
    Strikethrough = TTF_STYLE_STRIKETHROUGH
};

constexpr auto operator|(Font::Style lhs, Font::Style rhs) noexcept
    -> Font::Style;

constexpr auto operator|=(Font::Style &lhs, Font::Style rhs) noexcept
    -> Font::Style;

constexpr auto operator&(Font::Style lhs, Font::Style rhs) noexcept
    -> Font::Style;

constexpr auto operator&=(Font::Style &lhs, Font::Style rhs) noexcept
    -> Font::Style;

constexpr auto operator|(Font::Style lhs, Font::Style rhs) noexcept
    -> Font::Style
{
    return static_cast<Font::Style>(
        static_cast<std::underlying_type_t<Font::Style>>(lhs) |
        static_cast<std::underlying_type_t<Font::Style>>(rhs));
}

constexpr auto operator|=(Font::Style &lhs, Font::Style rhs) noexcept
    -> Font::Style
{
    lhs = lhs | rhs;
    return lhs;
}

constexpr auto operator&(Font::Style lhs, Font::Style rhs) noexcept
    -> Font::Style
{
    return static_cast<Font::Style>(
        static_cast<std::underlying_type_t<Font::Style>>(lhs) &
        static_cast<std::underlying_type_t<Font::Style>>(rhs));
}

constexpr auto operator&=(Font::Style &lhs, Font::Style rhs) noexcept
    -> Font::Style
{
    lhs = lhs & rhs;
    return lhs;
}

} // namespace HiLo
