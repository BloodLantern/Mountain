#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include <ImGui/imgui.h>
#include <ImGui/imgui_stdlib.h>

#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/Utils.hpp"

/// @brief Calls the given @p imguiFunction using the get/set accessors to the given @p field of @p variableAccess.
/// @param imguiFunction The @c ImGui function to call. This can be @c ImGui::SliderFloat(), @c ImGui::ComboEnum, etc...
/// @param label The label to give the @c ImGui function.
/// @param variableAccess The variable to use the get/set accessors from.
/// Note that you must explicitly use the dot (.) or pointer-to-member (->) operators when calling this macro.
/// For example, this parameter can be @c pointerValue-> or @c value. including the arrow/dot.
/// @param field The field to access. This is actually just the name of the get/set accessors without the Get/Set prefix.
#define IMGUI_GET_SET(imguiFunction, label, variableAccess, field, ...) \
    do \
    { \
        auto var = variableAccess##Get##field(); \
        imguiFunction(label, &var, __VA_ARGS__); \
        variableAccess##Set##field(var); \
    } \
    while (false)

namespace Mountain::ImGuiUtils
{
    MOUNTAIN_API void GridPlotting(std::string_view label, Vector2* value, float_t min = -1.f, float_t max = 1.f);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value, Vector2 expected);

    template <typename T>
    bool_t Optional(
        std::optional<T>* value,
        const Meta::Identity<T>& defaultValue,
        Meta::Identity<T> nullValue,
        const Meta::Identity<std::function<bool(T&)>>& displayFunction
    );

    MOUNTAIN_API bool ComboEaser(const std::string& label, Easing::Easer* v, ImGuiComboFlags flags = ImGuiComboFlags_None);

    MOUNTAIN_API void ShowInputsWindow();

    MOUNTAIN_API void ShowFileManager();

    MOUNTAIN_API void ShowResourceManager();

    MOUNTAIN_API bool_t PushSeparatorText(const char_t* label);

    MOUNTAIN_API void PopSeparatorText();

    MOUNTAIN_API bool_t PushCollapsingHeader(const char_t* label, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None);

    MOUNTAIN_API void PopCollapsingHeader();

    /// @brief Set the next item width to be the available width
    /// Shorthand for writing @code ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x); @endcode
    MOUNTAIN_API void SetNextItemWidthAvail();

    MOUNTAIN_API void ShowPerformanceMonitoring();

    MOUNTAIN_API void DrawEasingFunction(const char_t* label, Easing::Easer function, int32_t pointCount = 30);

    MOUNTAIN_API void OpenResourcePopupModal();

    template <Concepts::Resource T>
    void FilterResourcePopupModal(Pointer<T>* value);

    template <Concepts::Resource T>
    void SelectResource(const char_t* label, Pointer<T>* value);
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

    template <>
    bool ComboEnum<Easing::Type>(const char* label, Easing::Type* v, ImGuiComboFlags flags);
}
// ReSharper restore CppInconsistentNaming

// Start of ImGuiUtils.inl

#include "magic_enum/magic_enum.hpp"

namespace Mountain
{
    template <typename T>
    bool_t ImGuiUtils::Optional(
        std::optional<T>* value,
        const Meta::Identity<T>& defaultValue,
        Meta::Identity<T> nullValue,
        const Meta::Identity<std::function<bool_t(T& value)>>& displayFunction
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

    template <Concepts::Resource T>
    void ImGuiUtils::FilterResourcePopupModal(Pointer<T>* value)
    {
        ENSURE_NOT_NULL(value);

        ImGui::SetNextWindowSizeConstraints({200.f, 200.f}, {-1.f, -1.f});

        if (!ImGui::BeginPopupModal("ResourceFilter"))
            return;

        static std::string filter;

        if (ImGui::IsWindowAppearing())
        {
            filter = "";
            ImGui::SetKeyboardFocusHere(); // Focus the filter input text
        }

        ImGui::InputText("Filter", &filter);

        ImGui::Separator();

        List<Pointer<T>> resources = ResourceManager::FindAll<T>(
            [&](const Pointer<T>& resource)
            {
                return Utils::StringContainsIgnoreCase(resource->GetName(), filter);
            }
        );

        Pointer<T> selectedResource;
        for (const Pointer<T>& resource : resources)
        {
            if (ImGui::Selectable(resource->GetName().c_str()))
            {
                selectedResource = resource;
                break;
            }
        }

        if (selectedResource != nullptr)
        {
            *value = selectedResource;
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }

    template <Concepts::Resource T>
    void ImGuiUtils::SelectResource(const char_t* label, Pointer<T>* value)
    {
        ENSURE_NOT_NULL(value);

        ImGui::PushID(value);

        ImGui::Text(label);

        ImGui::SameLine();

        // Display resource name
        if (*value != nullptr)
        {
            const std::string resourceName = (*value)->GetName();
            const float_t textSize = Calc::Clamp(ImGui::CalcTextSize(resourceName.c_str()).x, 0.f, 5.f);
            ImGui::SetNextItemWidth(textSize);
            ImGui::Text("%s", resourceName.c_str());
        }
        else
        {
            ImGui::Text("No resource");
        }

        // Pop up context to clear the resource
        if (ImGui::BeginPopupContextItem("RemoveResource"))
        {
            if (ImGui::Selectable("Remove"))
                *value = nullptr;

            ImGui::EndPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("+"))
            OpenResourcePopupModal();

        FilterResourcePopupModal(value);

        ImGui::PopID();
    }
}

namespace ImGui
{
    // ReSharper disable CppInconsistentNaming
    template <Mountain::Concepts::Enum T>
    bool ComboEnum(const char* label, T* const v, const ImGuiComboFlags flags)
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
}
