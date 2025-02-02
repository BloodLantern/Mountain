#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2.hpp>

#include <ImGui/imgui.h>

#include "Mountain/utils/utils.hpp"

namespace Mountain::ImGuiUtils
{
    MOUNTAIN_API void GridPlotting(std::string_view label, Vector2* value, float_t min = -1.f, float_t max = 1.f);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value, Vector2 expected);

    template <typename T>
    bool_t Optional(
        std::optional<T>* value,
        const std::type_identity_t<T>& defaultValue,
        std::type_identity_t<T> nullValue,
        const std::type_identity_t<std::function<bool_t(T& value)>>& displayFunction
    );

    MOUNTAIN_API bool ComboEaser(const std::string& label, Easing::Easer* v, ImGuiComboFlags flags = ImGuiComboFlags_None);

    MOUNTAIN_API void ShowInputsWindow();

    MOUNTAIN_API void ShowFileManager();

    MOUNTAIN_API void ShowResourceManager();

    MOUNTAIN_API void PushSeparatorText(const char_t* label);

    MOUNTAIN_API void PopSeparatorText();

    MOUNTAIN_API bool_t PushCollapsingHeader(const char_t* label, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None);

    MOUNTAIN_API void PopCollapsingHeader();

    /// @brief Set the next item width to be the available width
    /// Shorthand for writing @code ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);@endcode
    MOUNTAIN_API void SetNextItemWidthAvail();

    MOUNTAIN_API void ShowPerformanceMonitoring();
}

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
