#pragma once

#include <filesystem>
#include <functional>
#include <thread>

#include <magic_enum/magic_enum.hpp>

#include <Math/quaternion.hpp>
#include <Math/vector2.hpp>
#include <Math/vector3.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file Utils.hpp
/// @brief Defines general utility functions.

/// @namespace Utils
/// @brief Namespace containing utility functions that don't belong anywhere else
namespace Mountain::Utils
{
    enum class TrimOptions : u8
    {
        None    = 0,
        Start   = 1 << 0,
        End     = 1 << 1,
        Both    = Start | End
    };

    /// @brief Converts an integral number to a valid pointer without illegal size operations
    /// @tparam PtrT Type of the pointer
    /// @tparam IntT Type of the number. Must be integral
    /// @param number Number to convert
    /// @return Pointer representation of the number
    template <typename PtrT, Concepts::Integral IntT>
    ATTRIBUTE_NODISCARD
    constexpr PtrT* IntToPointer(IntT number);

    ATTRIBUTE_NODISCARD
    constexpr usize PointerToInt(const void* pointer);

    /// @brief Gets the hash code of a specified type
    /// @tparam T Type
    /// @return Hash
    template <typename T>
    ATTRIBUTE_NODISCARD
    usize GetTypeHash();

    /// @brief Gets the hash code of a specified polymorphic pointer type
    /// @tparam T Type
    /// @param ptr Polymorphic pointer
    /// @return Hash
    template <typename T>
    ATTRIBUTE_NODISCARD
    usize GetTypeHash(const T* ptr);

    /// @brief Horizontally aligns the cursor of ImGui to be centered around a specific portion of the available space
    /// @param objectWidth Width of the element to align
    /// @param alignment In window alignment, 0.5f by default to center the object
    MOUNTAIN_API void AlignImGuiCursor(f32 objectWidth, f32 alignment = 0.5f);

    /// @brief Humanizes the provided string
    /// @details The process converts a PascalCase styled word to a humanized version
    /// that puts spaces between each word and adds an uppercase letter at the very beginning
    /// E.g., RequiresUIReloadAttribute will become Requires UI Reload Attribute
    /// @param str String to humanize
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string HumanizeString(const std::string& str);

    /// @brief Humanizes the provided variable name
    /// @details The process converts an m_PascalCase styled word to a humanized version
    /// that puts spaces between each word and adds an uppercase letter at the very beginning,
    /// it also removes the m_ prefix
    /// E.g., m_ShouldChange will become Should Change
    /// @param str String to humanize
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string HumanizeVariableName(const std::string& str);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become .5 if remapped to the range [0;1]
    /// @param oldValue Value
    /// @param oldRange Old range
    /// @param newRange New range
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr f32 RemapValue(f32 oldValue, Vector2 oldRange, Vector2 newRange);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become .5 if remapped to the range [0;1]
    /// @param oldValue Value
    /// @param oldMin Old range min
    /// @param oldMax Old range max
    /// @param newMin New range min
    /// @param newMax New range max
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr f32 RemapValue(f32 oldValue, f32 oldMin, f32 oldMax, f32 newMin, f32 newMax);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become 1 if remapped to the range [0;2]
    /// @param oldValue Value
    /// @param oldRange Old range
    /// @param newRange New range
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr usize RemapValue(usize oldValue, Vector2i oldRange, Vector2i newRange);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become 1 if remapped to the range [0;2]
    /// @param oldValue Value
    /// @param oldMin Old range min
    /// @param oldMax Old range max
    /// @param newMin New range min
    /// @param newMax New range max
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr usize RemapValue(usize oldValue, usize oldMin, usize oldMax, usize newMin, usize newMax);

    /// @brief Normalizes an angle (clamps its value between 0 and 2 * PI)
    /// @param angle Angle to normalize
    /// @return Normalized representation
    MOUNTAIN_API f32 NormalizeAngle(f32 angle);

    /// @brief Normalizes a set of three angles in a @c Vector3 (clamps their value between 0 and 2 * PI)
    /// @param angles @c Vector3 of angles to normalize
    /// @return Normalized representation
    MOUNTAIN_API Vector3 NormalizeAngles(Vector3 angles);

    /// @brief Converts a quaternion to its euler angle representation
    /// @param rot Quaternion to convert
    /// @return Euler representation
    MOUNTAIN_API Vector3 GetQuaternionEulerAngles(const Quaternion& rot);

    /// @brief Equivalent of a @c dynamic_cast for the @c Pointer type.
    ///
    /// This function first checks if the given @c Pointer is @c nullptr and returns @c nullptr if so.
    /// It then checks if one type is derived from the other and returns the cast result if so. This actually performs a @c reinterpret_cast under the hood.
    /// If all other conditions fail, the function returns @c nullptr.
    ///
    /// @tparam T The type to dynamically cast to.
    /// @tparam U The type to dynamically cast from.
    /// @param value The Pointer to cast from.
    /// @return A null Pointer if the cast failed. Otherwise, the cast result.
    template <typename T, typename U>
    ATTRIBUTE_NODISCARD
    Pointer<T> DynamicPointerCast(const Pointer<U>& value);

    /// @brief Opens the specified path in the file explorer
    /// @param path File system path
    MOUNTAIN_API void OpenInExplorer(const std::filesystem::path& path);

    /// @brief Opens the specified path in the file explorer
    /// @param path File system path
    /// @param isFile Whether path is a file or a directory
    MOUNTAIN_API void OpenInExplorer(const std::filesystem::path& path, bool isFile);

    /// @brief Opens the specified file on the user's computer
    /// @param filepath File system path
    MOUNTAIN_API void OpenFile(const std::filesystem::path& filepath);

    /// @brief Returns whether an array contains an element
    template <Concepts::StandardContainer ContainerT, typename T>
    ATTRIBUTE_NODISCARD
    bool ArrayContains(const ContainerT& container, T element);

    /// @brief Returns whether a string array contains an element using @c Utils::StringEqualsIgnoreCase.
    template <Concepts::StandardContainer ContainerT>
    ATTRIBUTE_NODISCARD
    bool StringArrayContains(const ContainerT& container, const std::string& element);

    /// @brief Returns whether a string enumerable contains an element using @c Utils::StringEqualsIgnoreCase.
    template <Requirements::MountainEnumerable EnumerableT>
    ATTRIBUTE_NODISCARD
    bool StringEnumerableContains(const EnumerableT& enumerable, const std::string& element);

    /// @brief Checks if two strings are equal, case-insensitive.
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API bool StringEqualsIgnoreCase(std::string_view a, std::string_view b);

    /// @brief Checks if a string contains another one, case-insensitive.
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API bool StringContainsIgnoreCase(std::string_view a, std::string_view b);

    /// @brief Gets the address of a function
    /// @tparam Ret Function return type
    /// @tparam Args Function arguments types
    /// @param f Function
    /// @return Address
    template <typename Ret, typename... Args>
    ATTRIBUTE_NODISCARD
    constexpr usize FunctionAddress(std::function<Ret(Args...)> f);

    MOUNTAIN_API s32 TerminalCommand(const std::string& command, bool asynchronous = true);

    MOUNTAIN_API void CreateEmptyFile(const std::filesystem::path& path);

    MOUNTAIN_API void SetThreadName(std::thread& thread, const std::string& name);

    template <typename R, typename... Args>
    R CallSafe(const std::function<R(Args...)>& function, Args&&... args);

    MOUNTAIN_API std::wstring NarrowToWide(std::string_view str);

    MOUNTAIN_API std::string WideToNarrow(std::wstring_view str);

    MOUNTAIN_API std::string ToLower(std::string_view str);

    MOUNTAIN_API std::string ToUpper(std::string_view str);

    MOUNTAIN_API std::pair<f32, std::string_view> ByteSizeUnit(s64 size);

    MOUNTAIN_API std::string GetBuiltinShadersPath();

    MOUNTAIN_API std::string GetBuiltinAssetsPath();

    MOUNTAIN_API std::string Trim(std::string_view str, TrimOptions options = TrimOptions::Both);

    MOUNTAIN_API std::string GetLine(const std::string& str, usize lineIndex);

    MOUNTAIN_API u16 Concat16(u8 right, u8 left);

    MOUNTAIN_API u32 Concat32(u8 right0, u8 right1, u8 left0, u8 left1);

    template <u64 Offset, u64 Count>
    constexpr u64 GetBits(u64 value);

    template <Concepts::Enum T>
    constexpr Meta::Flags<T> ToFlags(T enumValue);

    MOUNTAIN_API std::string RemoveByteOrderMark(const std::string& text);

    MOUNTAIN_API List<std::string> Split(std::string_view str, c8 separator);
}

namespace Easing
{
    enum class Type : u8
    {
        Linear,

        SineIn,
        SineOut,
        SineInOut,

        QuadIn,
        QuadOut,
        QuadInOut,

        CubicIn,
        CubicOut,
        CubicInOut,

        QuartIn,
        QuartOut,
        QuartInOut,

        QuintIn,
        QuintOut,
        QuintInOut,

        ExpoIn,
        ExpoOut,
        ExpoInOut,

        CircIn,
        CircOut,
        CircInOut,

        BackIn,
        BackOut,
        BackInOut,

        ElasticIn,
        ElasticOut,
        ElasticInOut,

        BounceIn,
        BounceOut,
        BounceInOut
    };

    MOUNTAIN_API Easer FromType(Type type);

    MOUNTAIN_API f32 FromType(Type type, f32 t);
}

ENUM_FLAGS(Mountain::Utils::TrimOptions)

// Start of Utils.inl

#include "Math/vector2i.hpp"

namespace Mountain
{
    template <typename PtrT, Concepts::Integral IntT>
    constexpr PtrT* Utils::IntToPointer(const IntT number) { return reinterpret_cast<PtrT*>(reinterpret_cast<u8*>(1) + static_cast<const usize>(number) - 1); }

    constexpr usize Utils::PointerToInt(const void* pointer) { return std::bit_cast<usize>(pointer); }

    constexpr f32 Utils::RemapValue(const f32 oldValue, const Vector2 oldRange, const Vector2 newRange)
    {
        return (oldValue - oldRange.x) * (newRange.y - newRange.x) / (oldRange.y - oldRange.x) + newRange.x;
    }

    constexpr f32 Utils::RemapValue(const f32 oldValue, const f32 oldMin, const f32 oldMax, const f32 newMin, const f32 newMax)
    {
        return RemapValue(oldValue, Vector2{oldMin, oldMax}, Vector2{newMin, newMax});
    }

    constexpr usize Utils::RemapValue(const usize oldValue, const Vector2i oldRange, const Vector2i newRange)
    {
        return (oldValue - oldRange.x) * (newRange.y - newRange.x) / (oldRange.y - oldRange.x) + newRange.x;
    }

    constexpr usize Utils::RemapValue(const usize oldValue, const usize oldMin, const usize oldMax, const usize newMin, const usize newMax)
    {
        return (oldValue - oldMin) * (newMax - newMin) / (oldMax - oldMin) + newMin;
    }

    template <typename T>
    usize Utils::GetTypeHash()
    {
        return typeid(T).hash_code();
    }

    template <typename T>
    usize Utils::GetTypeHash(ATTRIBUTE_MAYBE_UNUSED const T* const ptr)
    {
        return typeid(*ptr).hash_code();
    }

    template <typename T, typename U>
    Pointer<T> Utils::DynamicPointerCast(const Pointer<U>& value)
    {
        if (!value)
            return nullptr;

        if (dynamic_cast<T*>(const_cast<U*>(static_cast<const U*>(value))))
            return Pointer<T>(value, value.GetIsStrongReference());

        return nullptr;
    }

    template <Concepts::StandardContainer Container, typename T>
    bool Utils::ArrayContains(const Container& container, T element)
    {
        return std::ranges::find(container, element) != container.end();
    }

    template <Concepts::StandardContainer Container>
    bool Utils::StringArrayContains(const Container& container, const std::string& element)
    {
        return std::ranges::any_of(container, [&](const std::string& elem) { return StringEqualsIgnoreCase(elem, element); });
    }

    template <Requirements::MountainEnumerable EnumerableT>
    bool Utils::StringEnumerableContains(const EnumerableT& enumerable, const std::string& element)
    {
        return Any(enumerable, [&](const std::string& elem) { return StringEqualsIgnoreCase(elem, element); });
    }

    template <typename Ret, typename... Args>
    constexpr usize Utils::FunctionAddress(std::function<Ret(Args...)> f)
    {
        using Func = Ret(Args...);
        Func** fnPointer = f.template target<Func*>();
        if (!fnPointer)
            return 0;

        return reinterpret_cast<usize>(*fnPointer);
    }

    template <typename R, typename ... Args>
    R Utils::CallSafe(const std::function<R(Args...)>& function, Args&&... args)
    {
        if (function)
            return function(std::forward<Args>(args)...);

        return R{}; // Might not compile if R isn't default-constructible
    }

    template <u64 Offset, u64 Count>
    constexpr u64 Utils::GetBits(const u64 value)
    {
        constexpr u64 mask = (1ull << Count) - 1;
        return value >> Offset & mask;
    }

    template <Concepts::Enum T>
    constexpr Meta::Flags<T> Utils::ToFlags(T enumValue){ return static_cast<Meta::Flags<T>>(enumValue); }
}
