#pragma once

namespace HiLo
{

class TTFSubsystem
{
public:
    static auto initialize() noexcept -> void;

private:
    TTFSubsystem() noexcept;

    ~TTFSubsystem();
};

} // namespace HiLo
