﻿#pragma once

#include "Mountain/core.hpp"

#include "Mountain/utils/color.hpp"

namespace Mountain
{
    struct MOUNTAIN_API LightSource
    {
        Color color = Color::White();
        float_t intensity = 0.f;
        float_t radius = 0.f;
        float_t angleMin = 0.f;
        float_t angleMax = Calc::TwoPi;

        Vector2 position;
    };
}