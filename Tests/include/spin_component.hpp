#pragma once

#include "Mountain/scene/component/component.hpp"

class SpinComponent : public Mountain::Component
{
public:
    void Added() override;
    void Update() override;
    void DebugRender() override;
};
