#pragma once

namespace HiLo
{

class Size
{
public:
    Size() noexcept = default;

    Size(int width, int height) noexcept;

    auto width() const noexcept -> int;

    auto setWidth(int width) noexcept -> void;

    auto height() const noexcept -> int;

    auto setHeight(int height) noexcept -> void;

private:
    int mWidth;
    int mHeight;
};

} // namespace HiLo
