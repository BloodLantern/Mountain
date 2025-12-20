#pragma once

#include "Mountain/Core.hpp"

#include "Mountain/Utils/Color.hpp"

namespace Mountain
{
    struct MOUNTAIN_API LightSource
    {
        Color color = Color::White();
        f32 intensity = 0.f;
        f32 radius = 0.f;
        f32 angleMin = 0.f;
        f32 angleMax = Calc::TwoPi;

        Vector2 position;
    };
}
