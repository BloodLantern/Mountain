﻿#pragma once

#include "scene/component.hpp"

class SpinComponent : public Mountain::Component
{
public:
    void Added() override;
    void Update() override;
    void DebugRender() override;
};