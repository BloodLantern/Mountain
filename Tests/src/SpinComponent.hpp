#pragma once

#include "Mountain/Ecs/Component/Component.ixx"

class SpinComponent : public Mountain::Component
{
public:
    void Added() override;
    void Update() override;
    void DebugRender() override;
};
