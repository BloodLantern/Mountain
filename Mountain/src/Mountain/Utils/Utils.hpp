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
    enum class TrimOptions : uint8_t
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
    constexpr size_t PointerToInt(const void* pointer);

    /// @brief Gets the hash code of a specified type
    /// @tparam T Type
    /// @return Hash
    template <typename T>
    ATTRIBUTE_NODISCARD
    size_t GetTypeHash();

    /// @brief Gets the hash code of a specified polymorphic pointer type
    /// @tparam T Type
    /// @param ptr Polymorphic pointer
    /// @return Hash
    template <typename T>
    ATTRIBUTE_NODISCARD
    size_t GetTypeHash(const T* ptr);

    /// @brief Horizontally aligns the cursor of ImGui to be centered around a specific portion of the available space
    /// @param objectWidth Width of the element to align
    /// @param alignment In window alignment, 0.5f by default to center the object
    MOUNTAIN_API void AlignImGuiCursor(float_t objectWidth, float_t alignment = 0.5f);

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

    /// @brief Removes the namespaces indicators from the provided string
    /// @details E.g., Mountain::MyClass will become MyClass
    /// @param str String to modify
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr std::string RemoveNamespaces(const std::string& str);

    /// @brief Removes the namespace indicators from the provided string
    /// @details E.g., Mountain::MyClass will become MyClass
    /// @param str String to modify
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr const char_t* RemoveNamespaces(const char_t* str);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become .5 if remapped to the range [0;1]
    /// @param oldValue Value
    /// @param oldRange Old range
    /// @param newRange New range
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr float_t RemapValue(float_t oldValue, Vector2 oldRange, Vector2 newRange);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become .5 if remapped to the range [0;1]
    /// @param oldValue Value
    /// @param oldMin Old range min
    /// @param oldMax Old range max
    /// @param newMin New range min
    /// @param newMax New range max
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr float_t RemapValue(float_t oldValue, float_t oldMin, float_t oldMax, float_t newMin, float_t newMax);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become 1 if remapped to the range [0;2]
    /// @param oldValue Value
    /// @param oldRange Old range
    /// @param newRange New range
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr size_t RemapValue(size_t oldValue, Vector2i oldRange, Vector2i newRange);

    /// @brief Remaps a value from one range to another
    /// @details E.g., the number 5 in the range [0;10] will become 1 if remapped to the range [0;2]
    /// @param oldValue Value
    /// @param oldMin Old range min
    /// @param oldMax Old range max
    /// @param newMin New range min
    /// @param newMax New range max
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr size_t RemapValue(size_t oldValue, size_t oldMin, size_t oldMax, size_t newMin, size_t newMax);

    /// @brief Normalizes an angle (clamps its value between 0 and 2 * PI)
    /// @param angle Angle to normalize
    /// @return Normalized representation
    MOUNTAIN_API float_t NormalizeAngle(float_t angle);

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
    MOUNTAIN_API void OpenInExplorer(const std::filesystem::path& path, bool_t isFile);

    /// @brief Opens the specified file on the user's computer
    /// @param filepath File system path
    MOUNTAIN_API void OpenFile(const std::filesystem::path& filepath);

    /// @brief Returns whether an array contains an element
    template <Concepts::StandardContainer ContainerT, typename T>
    ATTRIBUTE_NODISCARD
    bool_t ArrayContains(const ContainerT& container, T element);

    /// @brief Returns whether a string array contains an element using @c Utils::StringEqualsIgnoreCase.
    template <Concepts::StandardContainer ContainerT>
    ATTRIBUTE_NODISCARD
    bool_t StringArrayContains(const ContainerT& container, const std::string& element);

    /// @brief Returns whether a string enumerable contains an element using @c Utils::StringEqualsIgnoreCase.
    template <Requirements::MountainEnumerable EnumerableT>
    ATTRIBUTE_NODISCARD
    bool_t StringEnumerableContains(const EnumerableT& enumerable, const std::string& element);

    /// @brief Checks if two strings are equal, case-insensitive.
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API bool_t StringEqualsIgnoreCase(std::string_view a, std::string_view b);

    /// @brief Checks if a string contains another one, case-insensitive.
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API bool_t StringContainsIgnoreCase(std::string_view a, std::string_view b);

    /// @brief Gets the address of a function
    /// @tparam Ret Function return type
    /// @tparam Args Function arguments types
    /// @param f Function
    /// @return Address
    template <typename Ret, typename... Args>
    ATTRIBUTE_NODISCARD
    constexpr size_t FunctionAddress(std::function<Ret(Args...)> f);

    MOUNTAIN_API int32_t TerminalCommand(const std::string& command, bool_t asynchronous = true);

    MOUNTAIN_API void CreateEmptyFile(const std::filesystem::path& path);

    MOUNTAIN_API void SetThreadName(std::thread& thread, const std::wstring& name);

    template <typename R, typename... Args>
    R CallSafe(const std::function<R(Args...)>& function, Args&&... args);

    MOUNTAIN_API std::wstring NarrowToWide(std::string_view str);

    MOUNTAIN_API std::string WideToNarrow(std::wstring_view str);

    MOUNTAIN_API std::string ToLower(std::string_view str);

    MOUNTAIN_API std::string ToUpper(std::string_view str);

    MOUNTAIN_API std::pair<float_t, std::string_view> ByteSizeUnit(int64_t size);

    MOUNTAIN_API std::string GetBuiltinShadersPath();

    MOUNTAIN_API std::string GetBuiltinAssetsPath();

    MOUNTAIN_API std::string Trim(std::string_view str, TrimOptions options = TrimOptions::Both);

    MOUNTAIN_API std::string GetLine(const std::string& str, size_t lineIndex);

    MOUNTAIN_API uint16_t Concat16(uint8_t right, uint8_t left);

    MOUNTAIN_API uint32_t Concat32(uint8_t right0, uint8_t right1, uint8_t left0, uint8_t left1);

    template <uint64_t Offset, uint64_t Count>
    constexpr uint64_t GetBits(uint64_t value);

    template <Concepts::Enum T>
    constexpr Meta::Flags<T> ToFlags(T enumValue);

    MOUNTAIN_API std::string RemoveByteOrderMark(const std::string& text);

    MOUNTAIN_API List<std::string> Split(std::string_view str, char_t separator);
}

namespace Easing
{
    enum class Type : uint8_t
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

    MOUNTAIN_API float_t FromType(Type type, float_t t);
}

ENUM_FLAGS(Mountain::Utils::TrimOptions)

// Start of Utils.inl

#include "Math/vector2i.hpp"

namespace Mountain
{
    template <typename PtrT, Concepts::Integral IntT>
    constexpr PtrT* Utils::IntToPointer(const IntT number) { return reinterpret_cast<PtrT*>(reinterpret_cast<uint8_t*>(1) + static_cast<const size_t>(number) - 1); }

    constexpr size_t Utils::PointerToInt(const void* pointer) { return std::bit_cast<size_t>(pointer); }

    constexpr std::string Utils::RemoveNamespaces(const std::string& str)
    {
        const size_t pos = str.find_last_of(':');

        if (pos == std::string::npos)
            return str;

        return str.substr(pos + 1);
    }

    constexpr const char_t* Utils::RemoveNamespaces(const char_t* const str)
    {
        const char_t* s = str;
        size_t l = 0;

        while (*s++)
            l++;

        while (s != str)
        {
            if (*s == ':')
                return s + 1;

            s--;
        }

        return str;
    }

    constexpr float_t Utils::RemapValue(const float_t oldValue, const Vector2 oldRange, const Vector2 newRange)
    {
        return (oldValue - oldRange.x) * (newRange.y - newRange.x) / (oldRange.y - oldRange.x) + newRange.x;
    }

    constexpr float_t Utils::RemapValue(const float_t oldValue, const float_t oldMin, const float_t oldMax, const float_t newMin, const float_t newMax)
    {
        return RemapValue(oldValue, Vector2{oldMin, oldMax}, Vector2{newMin, newMax});
    }

    constexpr size_t Utils::RemapValue(const size_t oldValue, const Vector2i oldRange, const Vector2i newRange)
    {
        return (oldValue - oldRange.x) * (newRange.y - newRange.x) / (oldRange.y - oldRange.x) + newRange.x;
    }

    constexpr size_t Utils::RemapValue(const size_t oldValue, const size_t oldMin, const size_t oldMax, const size_t newMin, const size_t newMax)
    {
        return (oldValue - oldMin) * (newMax - newMin) / (oldMax - oldMin) + newMin;
    }

    template <typename T>
    size_t Utils::GetTypeHash()
    {
        return typeid(T).hash_code();
    }

    template <typename T>
    size_t Utils::GetTypeHash(ATTRIBUTE_MAYBE_UNUSED const T* const ptr)
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
    bool_t Utils::ArrayContains(const Container& container, T element)
    {
        return std::ranges::find(container, element) != container.end();
    }

    template <Concepts::StandardContainer Container>
    bool_t Utils::StringArrayContains(const Container& container, const std::string& element)
    {
        return std::ranges::any_of(container, [&](const std::string& elem) { return StringEqualsIgnoreCase(elem, element); });
    }

    template <Requirements::MountainEnumerable EnumerableT>
    bool_t Utils::StringEnumerableContains(const EnumerableT& enumerable, const std::string& element)
    {
        return Any(enumerable, [&](const std::string& elem) { return StringEqualsIgnoreCase(elem, element); });
    }

    template <typename Ret, typename... Args>
    constexpr size_t Utils::FunctionAddress(std::function<Ret(Args...)> f)
    {
        using Func = Ret(Args...);
        Func** fnPointer = f.template target<Func*>();
        if (!fnPointer)
            return 0;

        return reinterpret_cast<size_t>(*fnPointer);
    }

    template <typename R, typename ... Args>
    R Utils::CallSafe(const std::function<R(Args...)>& function, Args&&... args)
    {
        if (function)
            return function(std::forward<Args>(args)...);

        return R{}; // Might not compile if R isn't default-constructible
    }

    template <uint64_t Offset, uint64_t Count>
    constexpr uint64_t Utils::GetBits(const uint64_t value)
    {
        constexpr uint64_t mask = (1ull << Count) - 1;
        return value >> Offset & mask;
    }

    template <Concepts::Enum T>
    constexpr Meta::Flags<T> Utils::ToFlags(T enumValue){ return static_cast<Meta::Flags<T>>(enumValue); }
}
