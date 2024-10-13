#pragma once

#include "magic_enum/magic_enum.hpp"

template <typename T>
bool_t Mountain::ImGuiUtils::Optional(
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
    
    return result || displayFunction(value->value());
}

// ReSharper disable CppInconsistentNaming
template <Mountain::Concepts::EnumT T>
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
