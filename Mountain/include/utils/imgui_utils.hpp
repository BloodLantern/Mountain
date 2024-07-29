#pragma once

#include "core.hpp"

#include <Maths/vector2.hpp>

#include <ImGui/imgui.h>

#include "utils.hpp"

BEGIN_MOUNTAIN

namespace ImGuiUtils
{
    MOUNTAIN_API void GridPlotting(std::string_view label, Vector2* value, float_t min = -1.f, float_t max = 1.f);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value, Vector2 expected);

    MOUNTAIN_API void ShowInputsWindow();
}

END_MOUNTAIN
