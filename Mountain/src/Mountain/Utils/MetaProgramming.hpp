#pragma once

// ReSharper disable CppInconsistentNaming

/// @file MetaProgramming.hpp
///
/// @brief Defines utilities for meta programming and template manipulation

#include "Mountain/Core.hpp"

#include <map>
#include <type_traits>

#include <Math/quaternion.hpp>
#include <Math/vector2.hpp>
#include <Math/vector3.hpp>

#include "Mountain/Utils/Concepts.hpp"

namespace Mountain
{
    template <typename>
    class Pointer;
    template <typename>
    class List;

    /// @namespace Meta
    /// @brief Defines utilities for meta programming and template manipulation
    namespace Meta
    {
        /// @brief Checks whether @c Derived is a derived class of @c Base
        /// @tparam Base Base class
        /// @tparam Derived Derived class
        template <typename Base, typename Derived>
        constexpr bool_t IsBaseOf = std::is_base_of_v<Base, Derived>;

        /// @brief Checks whether @c A and @c B are the same type
        /// @tparam A First type
        /// @tparam B Second type
        template <typename A, typename B>
        constexpr bool_t IsSame = std::is_same_v<A, B>;

        /// @brief Checks whether @c T is any of the provided types in @c Other
        /// @tparam T Type
        /// @tparam Other Other types
        template <typename T, typename... Other>
        constexpr bool_t IsAny = (std::is_same_v<T, Other> || ...);

        /// @brief Checks whether @c T is an array
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsArray = std::is_array_v<T>;

        /// @brief Checks whether @c T is a pointer
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsPointer = std::is_pointer_v<T>;

        /// @brief Checks whether @c T is a class
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsClass = std::is_class_v<T>;

        /// @brief Checks whether @c T is an enum
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsEnum = std::is_enum_v<T>;

        /// @brief Checks whether @c T is an integral type
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsIntegral = std::is_integral_v<T>;

        /// @brief Checks whether @c T is a floating type
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsFloatingPoint = std::is_floating_point_v<T>;

        /// @brief Checks whether @c T is an abstract class
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsAbstract = std::is_abstract_v<T>;

        /// @brief Checks whether @c T is default constructible (has a public constructor, with no parameters)
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsDefaultConstructible = std::is_default_constructible_v<T>;

        /// @brief Checks whether @c T can be copied without semantics
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsCopyAssignable = std::is_copy_assignable_v<T>;

        template <bool_t Test>
        using EnableIf = std::enable_if_t<Test>;

        /// @brief Removes the array specification from @c T
        ///
        /// e.g. if @c T was @c int[4], then @c RemoveArraySpecifier<T> will be @c int
        ///
        template <typename T>
        using RemoveArraySpecifier = std::remove_extent_t<T>;

        /// @brief Removes the pointer specification from @c T
        ///
        /// e.g. if @c T was @c int*, then @c RemovePointerSpecifier<T> will be @c int
        ///
        template <typename T>
        using RemovePointerSpecifier = std::remove_pointer_t<T>;

        /// @brief Removes the const specification from @c T
        ///
        /// e.g. if @c T was @c const int, then @c RemoveConstSpecifier<T> will be @c int
        ///
        template <typename T>
        using RemoveConstSpecifier = std::remove_const_t<T>;

        /// @brief Checks whether the type is a @c std::vector
        template <typename>
        constexpr bool_t IsStdVector = false;

        template <typename T, typename A>
        constexpr bool_t IsStdVector<std::vector<T, A>> = true;

        /// @brief Checks whether the type is a @c std::vector
        template <typename>
        constexpr bool_t IsStdFunction = false;

        template <typename T, typename... Args>
        constexpr bool_t IsStdFunction<std::function<T(Args...)>> = true;

        /// @brief Checks whether the type is a @c std::vector
        template <typename>
        constexpr bool_t IsStdMap = false;

        template <typename T, typename A>
        constexpr bool_t IsStdMap<std::map<T, A>> = true;

        /// @brief Checks whether the type is a List
        template <typename>
        constexpr bool_t IsMountainList = false;

        template <typename T>
        constexpr bool_t IsMountainList<List<T>> = true;

        /// @brief Checks whether the type is a Pointer
        template <typename>
        constexpr bool_t IsMountainPointer = false;

        /// @private
        template <typename T>
        constexpr bool_t IsMountainPointer<Pointer<T>> = true;

        /// @brief Checks if T is a native type.
        ///
        /// A native type is one of the following types:
        /// - uint8_t
        /// - int8_t
        /// - uint16_t
        /// - int16_t
        /// - uint32_t
        /// - int32_t
        /// - float_t
        /// - double_t
        /// - bool_t_t
        ///
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsNativeType = IsAny<T, uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float_t, double_t, bool_t>;

        /// @brief Checks if T is an integral or a floating type.
        ///
        /// A int/float type is one of the following types:
        /// - uint8_t
        /// - int8_t
        /// - uint16_t
        /// - int16_t
        /// - uint32_t
        /// - int32_t
        /// - float_t
        /// - double_t
        ///
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsIntegralOrFloating = IsAny<T, uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float_t, double_t>;

        /// @brief Checks if T is a math type.
        ///
        /// A math type is one of the following types:
        /// - Vector2
        /// - Vector2i
        /// - Vector3
        /// - Vector4
        /// - Quaternion
        ///
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsMathType = IsAny<T, Vector2, Vector2i, Vector3, Vector4, Quaternion>;

        /// @brief Checks if T is a color type.
        ///
        /// A color type is one of the following types:
        /// - Color
        /// - ColorHsva
        ///
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsColorType = IsAny<T, Color, ColorHsva>;

        template <Concepts::EnumT T>
        using UnderlyingEnumType = std::underlying_type_t<T>;

        template <Concepts::EnumT T>
        using Flags = UnderlyingEnumType<T>;
    }
};
