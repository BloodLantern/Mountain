#pragma once

/// @file MetaProgramming.hpp
///
/// @brief Defines utilities for meta-programming and template manipulation as well as some concepts.

#include "Mountain/Core.hpp"

#include <map>
#include <type_traits>

#include <Math/quaternion.hpp>
#include <Math/vector2.hpp>
#include <Math/vector3.hpp>

namespace Mountain
{
    class Entity;
    class Component;
    class Entry;
    class Font;
    class Resource;
    class Exception;
    struct Color;
    struct ColorHsva;
    class Effect;
    template <typename>
    struct Pointer;
    template <typename>
    class List;

    /// @namespace Meta
    /// @brief Defines utilities for meta-programming and template manipulation.
    namespace Meta
    {
        /// @brief Result of a logical AND (@c &&) between all the given conditions.
        template <bool_t... Conditions>
        constexpr bool_t LogicalAnd = (Conditions && ...);

        /// @brief Result of a logical OR (@c ||) between all the given conditions.
        template <bool_t... Conditions>
        constexpr bool_t LogicalOr = (Conditions || ...);

        /// @brief Checks whether @p Derived is a derived class of @p Base.
        /// @tparam Base Base class
        /// @tparam Derived Derived class
        template <typename Base, typename Derived>
        constexpr bool_t IsBaseOf = std::is_base_of_v<Base, Derived>;

        /// @brief Checks whether @p A and @p B are the same type.
        /// @tparam A First type
        /// @tparam B Second type
        template <typename A, typename B>
        constexpr bool_t IsSame = std::is_same_v<A, B>;

        /// @brief Checks whether @p T is any of the provided types in @p Other.
        /// @tparam T Type
        /// @tparam Other Other types
        template <typename T, typename... Other>
        constexpr bool_t AllSame = LogicalAnd<IsSame<T, Other>...>;

        /// @brief Checks whether @p T is any of the provided types in @p Other.
        /// @tparam T Type
        /// @tparam Other Other types
        template <typename T, typename... Other>
        constexpr bool_t IsAny = LogicalOr<IsSame<T, Other>...>;

        /// @brief Checks whether @p T is an array.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsArray = std::is_array_v<T>;

        /// @brief Checks whether @p T is a pointer.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsPointer = std::is_pointer_v<T>;

        /// @brief Checks whether @p T is a class.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsClass = std::is_class_v<T>;

        /// @brief Checks whether @p T is an enum.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsEnum = std::is_enum_v<T>;

        /// @brief Checks whether @p T is an integral type.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsIntegral = std::is_integral_v<T>;

        /// @brief Checks whether @p T is a floating type.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsFloatingPoint = std::is_floating_point_v<T>;

        /// @brief Checks whether @p T is an abstract class.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsAbstract = std::is_abstract_v<T>;

        /// @brief Checks whether @p T is default constructible (has a public constructor, with no parameters).
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsDefaultConstructible = std::is_default_constructible_v<T>;

        /// @brief Checks whether @p T can be copied without semantics.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsCopyAssignable = std::is_copy_assignable_v<T>;

        /// @brief Checks whether @p T is a @c const type.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsConst = std::is_const_v<T>;

        /// @brief Checks whether @p T is a @c volatile type.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsVolatile = std::is_volatile_v<T>;

        /// @brief Checks whether @p T is qualified either with @c const, @c volatile, or both.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsConstVolatileQualified = IsConst<T> || IsVolatile<T>;

        /// @brief Checks whether @p T is a reference type.
        /// @tparam T Type
        template <typename T>
        constexpr bool_t IsReference = std::is_reference_v<T>;

        template <bool_t Test>
        using EnableIf = std::enable_if_t<Test>;

        /// @brief Removes the array specification from @p T
        ///
        /// e.g. if @p T was @c int[4], then @c RemoveArraySpecifier<T> will be @c int
        ///
        template <typename T>
        using RemoveArraySpecifier = std::remove_extent_t<T>;

        /// @brief Removes the pointer specification from @p T
        ///
        /// e.g. if @p T was @c int*, then @c RemovePointerSpecifier<T> will be @c int
        ///
        template <typename T>
        using RemovePointerSpecifier = std::remove_pointer_t<T>;

        /// @brief Removes the const specification from @p T
        ///
        /// e.g. if @p T was @c const int, then @c RemoveConstSpecifier<T> will be @c int
        ///
        template <typename T>
        using RemoveConstSpecifier = std::remove_const_t<T>;

        /// @brief Checks whether the type is a @c std::vector
        template <typename>
        constexpr bool_t IsStdVector = false;

        template <typename T, typename A>
        constexpr bool_t IsStdVector<std::vector<T, A>> = true;

        /// @brief Checks whether the type is a function type
        /// <a href="https://en.cppreference.com/w/cpp/types/is_function.html">as defined in the C++ standard</a>.
        template <typename T>
        constexpr bool_t IsFunction = std::is_function_v<T>;

        /// @brief Checks whether the type is a @c std::function
        template <typename>
        constexpr bool_t IsStdFunction = false;

        template <typename T, typename... Args>
        constexpr bool_t IsStdFunction<std::function<T(Args...)>> = true;

        /// @brief Checks whether the type is a @c std::map
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

        template <typename T>
        constexpr bool_t IsMountainPointer<Pointer<T>> = true;

        template <typename T>
        constexpr bool_t IsException = IsBaseOf<std::exception, T>;

        template <typename T>
        constexpr bool_t IsMountainException = IsBaseOf<Exception, T>;

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

        template <typename From, typename To>
        constexpr bool_t IsConvertibleTo = std::is_convertible_v<From, To>;

        template <typename T>
        constexpr bool_t IsMountainContainer = requires(T& v)
        {
            v.GetSize();
        };
    }

    /// @namespace Concepts
    /// @brief Contains useful general-use concepts.
    namespace Concepts
    {
        /// @brief A class satisfies the Resource concept if it is derived from @c Resource.
        template <class T>
        concept Resource = Meta::IsBaseOf<Resource, T>;

        /// @brief A class satisfies the LoadableResource concept if it is derived from @c Resource and is not the @c Font class.
        template <class T>
        concept LoadableResource = Meta::IsBaseOf<Mountain::Resource, T> && !Meta::IsSame<T, Font>;

        /// @brief A class satisfies the Entry concept if it is derived from @c Entry.
        template <class T>
        concept Entry = Meta::IsBaseOf<Entry, T>;

        /// @brief Concept that forces a class to be the same as the others
        template <class T, class U>
        concept IsTSameAsU = Meta::IsSame<T, U>;

        /// @brief Concept that forces a type to be a child of @c Component
        template <class T>
        concept Component = Meta::IsBaseOf<Component, T>;

        /// @brief Concept that forces a type to be a child of @c Entity
        template <class T>
        concept Entity = Meta::IsBaseOf<Entity, T>;

        /// @brief A class satisfies the Exception concept if it is derived from @c std::exception.
        template<typename T>
        concept Exception = Meta::IsException<T>;

        /// @brief A class satisfies the Exception concept if it is derived from @c Mountain::Exception.
        template<typename T>
        concept MountainException = Meta::IsMountainException<T>;

        /// @brief A class satisfies the StdException concept if it is derived from @c std::exception and not from @c Exception.
        template<typename T>
        concept StdException = Exception<T> && !MountainException<T>;

        /// @brief Concept that forces a type to be a function
        template <class T>
        concept Function = Meta::IsFunction<T>;

        template <typename From, typename To>
        concept ConvertibleTo = Meta::IsConvertibleTo<From, To>;

        /// @brief Concept that forces a type to be a color, e.g., either @c Color or @c ColorHsva
        template <class T>
        concept Color = Meta::IsColorType<T>;

        /// @brief Concept that forces a type to be a raw pointer
        template <typename T>
        concept Pointer = Meta::IsPointer<T>;

        /// @brief Concept that forces a type to be of an integral type
        template <typename T>
        concept Integral = Meta::IsIntegral<T>;

        template <typename T>
        concept Enum = Meta::IsEnum<T>;

        template <class T>
        concept Effect = Meta::IsBaseOf<Effect, T>;

        /// @brief A container type is any non-const, non-function, non-reference type.
        template <typename T>
        concept ContainerType = !Meta::IsConst<T> && !Meta::IsStdFunction<T> && !Meta::IsReference<T>;
    }

    namespace Meta
    {
        template <Concepts::Enum T>
        using UnderlyingEnumType = std::underlying_type_t<T>;

        template <Concepts::Enum T>
        using Flags = UnderlyingEnumType<T>;
    }
};
