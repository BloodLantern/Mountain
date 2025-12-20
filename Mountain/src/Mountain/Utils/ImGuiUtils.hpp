#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include <ImGui/imgui.h>
#include <ImGui/imgui_stdlib.h>

#include "Mountain/Window.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/Optional.hpp"
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
    MOUNTAIN_API void GridPlotting(std::string_view label, Vector2* value, f32 min = -1.f, f32 max = 1.f);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value);

    MOUNTAIN_API void DirectionVector(std::string_view label, Vector2* value, Vector2 expected);

    template <typename T>
    bool Optional(
        Optional<T>* value,
        const Meta::Identity<T>& defaultValue,
        Meta::Identity<T> nullValue,
        const Meta::Identity<std::function<bool(T&)>>& displayFunction
    );

    MOUNTAIN_API bool ComboEaser(const std::string& label, Easing::Easer* v, ImGuiComboFlags flags = ImGuiComboFlags_None);

    MOUNTAIN_API void ShowInputsWindow();

    MOUNTAIN_API void ShowFileManager();

    MOUNTAIN_API void ShowResourceManager();

    MOUNTAIN_API bool PushSeparatorText(const c8* label);

    MOUNTAIN_API void PopSeparatorText();

    MOUNTAIN_API bool PushCollapsingHeader(const c8* label, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None);

    MOUNTAIN_API void PopCollapsingHeader();

    /// @brief Set the next item width to be the available width
    /// Shorthand for writing @code ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x); @endcode
    MOUNTAIN_API void SetNextItemWidthAvail();

    MOUNTAIN_API void ShowPerformanceMonitoring();

    MOUNTAIN_API void DrawEasingFunction(const c8* label, Easing::Easer function, s32 pointCount = 30);

    MOUNTAIN_API void OpenPointerPopupModal();

    template <typename T>
    bool FilterPointerPopupModal(
        Pointer<T>* value,
        const List<Pointer<T>>& pointers,
        std::string& filter,
        const std::function<const c8*(const Pointer<T>&)>& getNameFunction
    );

    MOUNTAIN_API bool FilterFilePopupModal(Pointer<File>* value, std::string_view extension = "");

    template <Concepts::Resource T>
    bool FilterResourcePopupModal(Pointer<T>* value);

    template <typename T>
    bool SelectPointer(
        const c8* label,
        Pointer<T>* value,
        bool enableResetButton,
        const std::function<bool(Pointer<T>*)>& filterFunction,
        const std::function<const c8*(const Pointer<T>&)>& getNameFunction
    );

    MOUNTAIN_API bool SelectFile(const c8* label, Pointer<File>* value, bool enableResetButton, std::string_view extension = "");

    template <Concepts::Resource T>
    bool SelectResource(const c8* label, Pointer<T>* value, bool enableResetButton);
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

    MOUNTAIN_API bool DragAngle3(
        const char* label,
        float v_rad[3],
        float v_speed = 1,
        float v_degrees_min = -360,
        float v_degrees_max = +360,
        const char* format = "%.3f",
        ImGuiSliderFlags flags = 0
    );

    template <Mountain::Concepts::Enum T>
    bool ComboEnum(const char* label, T* v, ImGuiComboFlags flags = ImGuiComboFlags_None);

    template <>
    MOUNTAIN_API bool ComboEnum<Easing::Type>(const char* label, Easing::Type* v, ImGuiComboFlags flags);
}
// ReSharper restore CppInconsistentNaming

// Start of ImGuiUtils.inl

#include "magic_enum/magic_enum.hpp"

namespace Mountain
{
    template <typename T>
    bool ImGuiUtils::Optional(
        Mountain::Optional<T>* value,
        const Meta::Identity<T>& defaultValue,
        Meta::Identity<T> nullValue,
        const Meta::Identity<std::function<bool(T& value)>>& displayFunction
    )
    {
        bool result = false;
        if (value->HasValue())
        {
            if (ImGui::Button("Unset value"))
            {
                value->Reset();
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
        if (!value->HasValue())
        {
            ImGui::BeginDisabled();
            displayFunction(nullValue);
            ImGui::EndDisabled();
            return result;
        }

        return displayFunction(value->Value()) || result;
    }

    template <typename T>
    bool ImGuiUtils::FilterPointerPopupModal(
        Pointer<T>* value,
        const List<Pointer<T>>& pointers,
        std::string& filter,
        const std::function<const c8*(const Pointer<T>&)>& getNameFunction
    )
    {
        ENSURE_NOT_NULL(value);

        ImGui::SetNextWindowSizeConstraints({300.f, 300.f}, static_cast<Vector2>(Window::GetSize()));

        if (!ImGui::BeginPopupModal("PointerFilter"))
            return false;

        static usize selectedIndex = 0;

        if (ImGui::IsWindowAppearing())
        {
            filter = "";
            ImGui::SetKeyboardFocusHere(); // Focus the filter input text

            selectedIndex = 0;

            if (*value)
            {
                for (usize i = 0; i < pointers.GetSize(); i++)
                {
                    if (pointers[i] != *value)
                        continue;

                    selectedIndex = i;
                    break;
                }
            }
        }

        if (ImGui::InputText("Filter", &filter))
            selectedIndex = 0;

        ImGui::Separator();

        if (ImGui::IsKeyPressed(ImGuiKey_DownArrow))
            selectedIndex = (selectedIndex + 1) % pointers.GetSize();
        if (ImGui::IsKeyPressed(ImGuiKey_UpArrow))
            selectedIndex = (selectedIndex - 1) % pointers.GetSize();

        Pointer<T> selectedPointer;
        for (usize i = 0; i < pointers.GetSize(); i++)
        {
            const Pointer<T>& pointer = pointers[i];

            if (ImGui::Selectable(getNameFunction(pointer), pointer == pointers[selectedIndex]))
            {
                selectedPointer = pointer;
                break;
            }
        }

        if (pointers.IsValidIndex(selectedIndex) && (ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter)))
            selectedPointer = pointers[selectedIndex];

        if (selectedPointer != nullptr)
        {
            *value = selectedPointer;
            ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
            return true;
        }

        // If pressed escape or clicked outside the popup window, close the popup
        if (ImGui::IsKeyPressed(ImGuiKey_Escape) ||
            (ImGui::IsMouseClicked(ImGuiMouseButton_Left) &&
                !(ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows) || ImGui::IsAnyItemHovered())
            )
        )
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
        return false;
    }

    template <Concepts::Resource T>
    bool ImGuiUtils::FilterResourcePopupModal(Pointer<T>* value)
    {
        static std::string filter;

        const List<Pointer<T>> resources = ResourceManager::FindAll<T>(
            [&](const Pointer<T>& resource)
            {
                return Utils::StringContainsIgnoreCase(resource->GetName(), filter);
            }
        );

        return FilterPointerPopupModal<T>(value, resources, filter, [](const Pointer<T>& p) { return p->GetName().c_str(); });
    }

    template <typename T>
    bool ImGuiUtils::SelectPointer(
        const c8* label,
        Pointer<T>* value,
        const bool enableResetButton,
        const std::function<bool(Pointer<T>*)>& filterFunction,
        const std::function<const c8*(const Pointer<T>&)>& getNameFunction
    )
    {
        ENSURE_NOT_NULL(value);

        ImGui::PushID(value);

        ImGui::Text("%s", label);

        ImGui::SameLine();

        // Display resource name
        if (*value != nullptr)
        {
            const f32 textSize = Calc::Clamp(ImGui::CalcTextSize(getNameFunction(*value)).x, 0.f, 5.f);
            ImGui::SetNextItemWidth(textSize);
            ImGui::Text("%s", getNameFunction(*value));
        }
        else
        {
            ImGui::Text("No value");
        }

        ImGui::SameLine();

        if (ImGui::Button("..."))
            OpenPointerPopupModal();

        if (enableResetButton)
        {
            ImGui::SameLine();

            const bool resetButtonDisabled = *value == nullptr;

            if (resetButtonDisabled)
                ImGui::BeginDisabled();

            if (ImGui::Button("Reset"))
                *value = nullptr;

            if (resetButtonDisabled)
                ImGui::EndDisabled();
        }

        const bool result = filterFunction(value);

        ImGui::PopID();

        return result;
    }

    template <Concepts::Resource T>
    bool ImGuiUtils::SelectResource(const c8* label, Pointer<T>* value, const bool enableResetButton)
    {
        return SelectPointer<T>(label, value, enableResetButton, FilterResourcePopupModal<T>, [](const Pointer<T>& p) { return p->GetName().c_str(); });
    }
}

namespace ImGui
{
    // ReSharper disable CppInconsistentNaming
    template <Mountain::Concepts::Enum T>
    bool ComboEnum(const char* label, T* const v, const ImGuiComboFlags flags)
    {
        bool result = false;
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
