#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2.hpp>

#include <ImGui/imgui.h>

#include "Mountain/utils/utils.hpp"

BEGIN_MOUNTAIN

namespace ImGuiUtils
{
    MOUNTAIN_API void GridPlotting(std::string_view label, Vector2* value, float_t min = -1.f, float_t max = 1.f);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value, Vector2 expected);

    MOUNTAIN_API void ShowInputsWindow();
}

END_MOUNTAIN

// ReSharper disable CppInconsistentNaming
namespace ImGui
{
    MOUNTAIN_API bool DragAngle(
        const char* label, 
        float* v, 
        float v_speed = 1, 
        float v_min = 0, 
        float v_max = 0, 
        const char* format = "%.3f", 
        ImGuiSliderFlags flags = 0
    );

    template <Mountain::Concepts::EnumT T>
    bool ComboEnum(const char* label, T* v, ImGuiComboFlags flags = ImGuiComboFlags_None);
}
// ReSharper restore CppInconsistentNaming

#include "Mountain/utils/imgui_utils.inl"
