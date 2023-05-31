#pragma once

namespace HiLo
{

class SDLSubsystem
{
public:
    static auto initialize() noexcept -> void;

private:
    SDLSubsystem() noexcept;

    ~SDLSubsystem();
};

} // namespace HiLo
