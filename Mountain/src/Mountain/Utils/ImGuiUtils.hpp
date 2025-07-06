#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include <ImGui/imgui.h>

#include "Mountain/Utils/Utils.hpp"

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
    /// Shorthand for writing @code ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x); @endcode
    MOUNTAIN_API void SetNextItemWidthAvail();

    MOUNTAIN_API void ShowPerformanceMonitoring();
}

// ReSharper disable CppInconsistentNaming
namespace ImGui
{
    MOUNTAIN_API bool DragAngle(
        const char* label,
        float* v_rad,
        float v_speed = 1,
        float v_degrees_min = -360,
        float v_degrees_max = +360,
        const char* format = "%.3f",
        ImGuiSliderFlags flags = 0
    );

    template <Mountain::Concepts::Enum T>
    bool ComboEnum(const char* label, T* v, ImGuiComboFlags flags = ImGuiComboFlags_None);
}
// ReSharper restore CppInconsistentNaming

// Start of ImGuiUtils.inl

#include "magic_enum/magic_enum.hpp"

namespace Mountain
{
    template <typename T>
    bool_t ImGuiUtils::Optional(
        std::optional<T>* value,
        const std::type_identity_t<T>& defaultValue,
        std::type_identity_t<T> nullValue,
        const std::type_identity_t<std::function<bool_t(T& value)>>& displayFunction
    )
    {
        bool_t result = false;
        if (value->has_value())
        {
            if (ImGui::Button("Unset value"))
            {
                value->reset();
                result = true;
            }
        }
        else
        {
            if (ImGui::Button("Set value"))
            {
                *value = defaultValue;
                result = true;
            }
        }

        ImGui::SameLine();

        // Need to check this again as this might have changed in the last if statement
        if (!value->has_value())
        {
            ImGui::BeginDisabled();
            displayFunction(nullValue);
            ImGui::EndDisabled();
            return result;
        }

        return displayFunction(value->value()) || result;
    }
}

// ReSharper disable CppInconsistentNaming
template <Mountain::Concepts::Enum T>
bool ImGui::ComboEnum(const char* label, T* const v, const ImGuiComboFlags flags)
{
    bool_t result = false;
    if (BeginCombo(label, magic_enum::enum_name(*v).data(), flags))
    {
        for (const T value : magic_enum::enum_values<T>())
        {
            if (Selectable(magic_enum::enum_name(value).data()))
            {
                *v = value;
                result = true;
            }
        }
        EndCombo();
    }
    return result;
}
// ReSharper restore CppInconsistentNaming
