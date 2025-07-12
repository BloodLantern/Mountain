#pragma once

#include "Common.hpp"

#include <Mountain/Ecs/Component/Component.hpp>

class SpinComponent : public Component
{
public:
    void Added() override;
    void Update() override;
    void DebugRender() override;
};
