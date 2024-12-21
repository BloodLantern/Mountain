#pragma once

#include <filesystem>
#include <functional>
#include <thread>

#include <Maths/quaternion.hpp>
#include <Maths/vector2.hpp>
#include <Maths/vector3.hpp>

#include "Mountain/core.hpp"

#include "Mountain/utils/concepts.hpp"
#include "Mountain/utils/pointer.hpp"

/// @file utils.hpp
/// @brief Defines general utility functions.

#define TO_STRING(x) #x
#define STRINGIFY(x) TO_STRING(x)

/// @namespace Utils
/// @brief Namespace containing utility functions that don't belong anywhere else
namespace Mountain::Utils
{
    enum class TrimOptions : uint8_t
    {
        None    = 0,
        Start   = 1 << 0,
        End     = 1 << 1,
        Both    = Start | End
    };

    template <typename T>
    using ProjectionFunc = T(*)(T);

    template <typename T>
    constexpr ProjectionFunc<T> Identity = [](T t) { return t; };

    /// @brief Converts a integral number to a valid pointer without illegal size operations
    /// @tparam PtrT Type of the pointer
    /// @tparam IntT Type of the number, must be integral
    /// @param number Number to convert
    /// @return Pointer representation of the number
    template <typename PtrT, Concepts::IntegralT IntT>
    [[nodiscard]]
    constexpr PtrT* IntToPointer(IntT number);

    /// @brief Gets the hash code of a specified type
    /// @tparam T Type
    /// @return Hash
    template <typename T>
    [[nodiscard]]
    size_t GetTypeHash();

    /// @brief Gets the hash code of a specified polymorphic pointer type
    /// @tparam T Type
    /// @param ptr Polymorphic pointer
    /// @return Hash
    template <typename T>
    [[nodiscard]]
    size_t GetTypeHash(const T* ptr);

    /// @brief Horizontally aligns the cursor of ImGui to be centered around a specific portion of the available space
    /// @param objectWidth Width of the element to align
    /// @param alignment In window alignment, 0.5f by default to center the object
    MOUNTAIN_API void AlignImGuiCursor(float_t objectWidth, float_t alignment = 0.5f);

    /// @brief Humanizes the provided string
    ///
    /// The process converts a PascalCase styled word to a humanized version that puts spaces between each words and adds an uppercase at the very beginning
    ///
    /// e.g. RequiresUIReloadAttribute will become Requires UI Reload Attribute
    /// @param str String to humanize
    /// @return Result
    [[nodiscard]]
    MOUNTAIN_API std::string HumanizeString(const std::string& str);

    /// @brief Humanizes the provided variable name
    ///
    /// The process converts a m_PascalCase styled word to a humanized version that puts spaces between each word and adds an uppercase at the very beginning, it also removes the m_ prefix
    ///
    /// e.g. m_ShouldChange will become Should Change
    /// @param str String to humanize
    /// @return Result
    [[nodiscard]]
    MOUNTAIN_API std::string HumanizeVariableName(const std::string& str);

    /// @brief Removes the namespaces indicators from the provided string
    ///
    /// e.g. Mountain::MyClass will become MyClass
    ///
    /// @param str String to modify
    /// @return Result
    [[nodiscard]]
    MOUNTAIN_API constexpr std::string RemoveNamespaces(const std::string& str);

#ifndef SWIG
    /// @brief Removes the namespaces indicators from the provided string
    ///
    /// e.g. Mountain::MyClass will become MyClass
    ///
    /// @param str String to modify
    /// @return Result
    [[nodiscard]]
    MOUNTAIN_API constexpr const char_t* RemoveNamespaces(const char_t* str);
#endif

    /// @brief Remaps a value from one range to another
    ///
    /// e.g., the number 5 in the range [0;10] will become .5 if remapped to the range [0;1]
    /// @param oldValue Value
    /// @param oldRange Old range
    /// @param newRange New range
    /// @return New value
    [[nodiscard]]
    MOUNTAIN_API constexpr float_t RemapValue(float_t oldValue, Vector2 oldRange, Vector2 newRange);

    /// @brief Remaps a value from one range to another
    ///
    /// e.g., the number 5 in the range [0;10] will become 1 if remapped to the range [0;2]
    /// @param oldValue Value
    /// @param oldRange Old range
    /// @param newRange New range
    /// @return New value
    [[nodiscard]]
    MOUNTAIN_API constexpr size_t RemapValue(size_t oldValue, Vector2i oldRange, Vector2i newRange);

    /// @brief Normalizes an angle (clamps its value between 0 and 2 * PI)
    /// @param angle Angle to normalize
    /// @return Normalized representation
    MOUNTAIN_API float_t NormalizeAngle(float_t angle);

    /// @brief Normalizes a set of 3 angles in a Vector3 (clamps their value between 0 and 2 * PI)
    /// @param angles Vector3 of angles to normalize
    /// @return Normalized representation
    MOUNTAIN_API Vector3 NormalizeAngles(Vector3 angles);

    /// @brief Converts a quaternion to its euler angle representation
    /// @param rot Quaternion to convert
    /// @return Euler representation
    MOUNTAIN_API Vector3 GetQuaternionEulerAngles(const Quaternion& rot);

    /// @brief Equivalent of a @c dynamic_cast for Pointer "Pointers".
    ///
    /// This function first checks if the given Pointer is @c nullptr, and returns @c nullptr if so.
    /// It then checks if one type is derived from the other, and returns the cast result if so. This actually performs a @c reinterpret_cast under the hood.
    /// If all other conditions failed, the function returns @c nullptr.
    ///
    /// @tparam T The type to dynamically cast to.
    /// @tparam U The type to dynamically cast from.
    /// @param value The Pointer to cast from.
    /// @return A null Pointer if the cast failed. Otherwise, the cast result.
    template <typename T, typename U>
    [[nodiscard]]
    Pointer<T> DynamicPointerCast(const Pointer<U>& value);

    /// @brief Opens the specified path in the file explorer
    /// @param path File system path
    MOUNTAIN_API void OpenInExplorer(const std::filesystem::path& path);

    /// @brief Opens the specified path in the file explorer
    /// @param path File system path
    /// @param isFile Whether path is a file or a directory
    MOUNTAIN_API void OpenInExplorer(const std::filesystem::path& path, bool_t isFile);

    /// @brief Opens the specified file on the user's computer
    /// @param filepath File system path
    MOUNTAIN_API void OpenFile(const std::filesystem::path& filepath);

    /// @brief Returns whether an array contains an element
    template <std::ranges::input_range Container, typename T>
    [[nodiscard]]
    bool_t ArrayContains(const Container& container, T element);

    /// @brief Returns whether a string array contains an element using Utils::StringEqualsIgnoreCase.
    template <std::ranges::input_range Container>
    [[nodiscard]]
    bool_t StringArrayContains(const Container& container, const std::string& element);

    /// @brief Checks if two strings are equal, case-insensitive.
    [[nodiscard]]
    MOUNTAIN_API bool_t StringEqualsIgnoreCase(std::string_view a, std::string_view b);

    /// @brief Checks if a string contains another one, case-insensitive.
    [[nodiscard]]
    MOUNTAIN_API bool_t StringContainsIgnoreCase(std::string_view a, std::string_view b);

    /// @brief Gets the address of a function
    /// @tparam Ret Function return type
    /// @tparam Args Function arguments types
    /// @param f Function
    /// @return Address
    template <typename Ret, typename... Args>
    [[nodiscard]]
    constexpr size_t FunctionAddress(std::function<Ret(Args...)> f);

    MOUNTAIN_API int32_t TerminalCommand(const std::string& command, bool_t asynchronous = true);

    MOUNTAIN_API void CreateEmptyFile(const std::filesystem::path& path);

    MOUNTAIN_API void SetThreadName(std::thread& thread, const std::wstring& name);

    template <typename R, typename... Args>
    R CallSafe(const std::function<R(Args...)>& function, Args&&... args);

    MOUNTAIN_API std::wstring StringNarrowToWide(std::string_view str);

    MOUNTAIN_API std::string StringWideToNarrow(std::wstring_view str);

    MOUNTAIN_API std::string StringToLower(std::string_view str);

    MOUNTAIN_API std::string StringToUpper(std::string_view str);

    MOUNTAIN_API std::pair<int32_t, std::string_view> ByteSizeUnit(int64_t size);

    MOUNTAIN_API std::string GetBuiltinShadersPath();

    MOUNTAIN_API std::string Trim(std::string_view str, TrimOptions options = TrimOptions::Both);
}

ENUM_FLAGS(Mountain::Utils::TrimOptions)

#include "Mountain/utils/utils.inl"
