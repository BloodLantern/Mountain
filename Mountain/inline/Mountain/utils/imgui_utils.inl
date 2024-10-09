#pragma once

#include "magic_enum/magic_enum.hpp"

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
