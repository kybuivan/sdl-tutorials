#pragma once

namespace HiLo
{

class IMGSubsystem
{
public:
    static auto initialize() noexcept -> void;

private:
    IMGSubsystem() noexcept;

    ~IMGSubsystem();
};

} // namespace HiLo
