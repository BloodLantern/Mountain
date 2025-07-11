#pragma once

/// @file MetaProgramming.hpp
///
/// @brief Defines utilities for meta-programming and template manipulation as well as some concepts.

#include "Mountain/Core.hpp"

#include <functional>
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

    /// @namespace Meta
    /// @brief Defines utilities for meta-programming and template manipulation.
    namespace Meta
    {
        /// @brief Equivalent to @p T with the exception that it won't participate in template argument deduction.
        template <typename T>
        using Identity = std::type_identity_t<T>;

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
        /// @tparam Other Other types
        template <typename T, typename... Other>
        constexpr bool_t AllSame = LogicalAnd<IsSame<T, Other>...>;

        /// @brief Checks whether @p T is any of the provided types in @p Other.
        /// @tparam Other Other types
        template <typename T, typename... Other>
        constexpr bool_t IsAny = LogicalOr<IsSame<T, Other>...>;

        /// @brief Checks whether @p T is an array.
        template <typename T>
        constexpr bool_t IsArray = std::is_array_v<T>;

        /// @brief Checks whether @p T is a class.
        template <typename T>
        constexpr bool_t IsClass = std::is_class_v<T>;

        /// @brief Checks whether @p T is an abstract class.
        template <typename T>
        constexpr bool_t IsAbstract = std::is_abstract_v<T>;

        /// @brief Checks whether @p T is default-constructible (has a public constructor, with no parameters).
        template <typename T>
        constexpr bool_t IsDefaultConstructible = std::is_default_constructible_v<T>;

        /// @brief Checks whether @p T can be assigned a copied value.
        template <typename T>
        constexpr bool_t IsCopyAssignable = std::is_copy_assignable_v<T>;

        /// @brief Checks whether @p T can be assigned a moved value.
        template <typename T>
        constexpr bool_t IsMoveAssignable = std::is_move_assignable_v<T>;

        /// @brief Checks whether @p T is trivially copyable.
        template <typename T>
        constexpr bool_t IsTriviallyCopyable = std::is_trivially_copyable_v<T>;

        /// @brief Checks whether @p From is trivially assignable to @p To.
        template <typename To, typename From>
        constexpr bool_t IsTriviallyAssignable = std::is_trivially_assignable_v<To, From>;

        /// @brief Checks whether @p T is trivially constructible.
        template <typename T>
        constexpr bool_t IsTriviallyConstructible = std::is_trivially_constructible_v<T>;

        /// @brief Checks whether @p T is trivially copy-assignable.
        template <typename T>
        constexpr bool_t IsTriviallyCopyAssignable = std::is_trivially_copy_assignable_v<T>;

        /// @brief Checks whether @p T is trivially copy-constructible.
        template <typename T>
        constexpr bool_t IsTriviallyCopyConstructible = std::is_trivially_copy_constructible_v<T>;

        /// @brief Checks whether @p T is trivially default-constructible.
        template <typename T>
        constexpr bool_t IsTriviallyDefaultConstructible = std::is_trivially_default_constructible_v<T>;

        /// @brief Checks whether @p T is trivially destructible.
        template <typename T>
        constexpr bool_t IsTriviallyDestructible = std::is_trivially_destructible_v<T>;

        /// @brief Checks whether @p T is trivially move-assignable.
        template <typename T>
        constexpr bool_t IsTriviallyMoveAssignable = std::is_trivially_move_assignable_v<T>;

        /// @brief Checks whether @p T is trivially move-constructible.
        template <typename T>
        constexpr bool_t IsTriviallyMoveConstructible = std::is_trivially_move_constructible_v<T>;

        /// @brief Checks whether @p T is a @c const type.
        template <typename T>
        constexpr bool_t IsConst = std::is_const_v<T>;

        /// @brief Checks whether @p T is a @c volatile type.
        template <typename T>
        constexpr bool_t IsVolatile = std::is_volatile_v<T>;

        /// @brief Checks whether @p T is qualified either with @c const, @c volatile, or both.
        template <typename T>
        constexpr bool_t IsConstVolatileQualified = IsConst<T> || IsVolatile<T>;

        /// @brief Checks whether @p T is a reference type.
        template <typename T>
        constexpr bool_t IsReference = std::is_reference_v<T>;

        template <bool_t Condition>
        using EnableIf = std::enable_if_t<Condition>;

        /// @brief Removes the array specification from @p T
        /// @details e.g., if @p T is @code int[4]@endcode, then @c RemoveArraySpecifier<T> will be @c int
        template <typename T>
        using RemoveArraySpecifier = std::remove_extent_t<T>;

        /// @brief Removes the pointer specification from @p T
        /// @details e.g., if @p T is @c int*, then @c RemovePointerSpecifier<T> will be @c int
        template <typename T>
        using RemovePointerSpecifier = std::remove_pointer_t<T>;

        /// @brief Removes the const specification from @p T
        /// @details e.g., if @p T is @code const int@endcode, then @c RemoveConstSpecifier<T> will be @c int
        template <typename T>
        using RemoveConstSpecifier = std::remove_const_t<T>;

        /// @brief Removes the volatile specification from @p T
        /// @details e.g., if @p T is @code volatile int@endcode, then @c RemoveVolatileSpecifier<T> will be @c int
        template <typename T>
        using RemoveVolatileSpecifier = std::remove_volatile_t<T>;

        /// @brief Removes any const and volatile specifications from @p T
        /// @details e.g., if @p T is @code const volatile int@endcode, then @c RemoveCvSpecifier<T> will be @c int
        template <typename T>
        using RemoveCvSpecifier = RemoveVolatileSpecifier<RemoveConstSpecifier<T>>;

        /// @brief Removes the reference specification from @p T
        /// @details e.g., if @p T is @c int& or @c int&&, then @c RemoveReferenceSpecifier<T> will be @c int
        template <typename T>
        using RemoveReferenceSpecifier = std::remove_reference_t<T>;

        /// @brief Removes any const, volatile and reference specifications from @p T
        template <typename T>
        using RemoveCvRefSpecifier = RemoveCvSpecifier<RemoveReferenceSpecifier<T>>;

        /// @brief Removes any const, volatile and pointer specifications from @p T
        template <typename T>
        using RemoveCvPointerSpecifier = RemoveCvSpecifier<RemovePointerSpecifier<T>>;

        /// @brief Checks whether the type is a @c std::function
        template <typename>
        constexpr bool_t IsStandardFunction = false;

        template <typename T, typename... Args>
        constexpr bool_t IsStandardFunction<std::function<T(Args...)>> = true;

        /// @brief Checks whether the type is a Pointer
        template <typename>
        constexpr bool_t IsMountainPointer = false;

        template <typename T>
        constexpr bool_t IsMountainPointer<Pointer<T>> = true;

        /// @brief Checks if T is a native type.
        ///
        /// A native type is one of the following types:
        /// - char_t
        /// - uint8_t
        /// - int8_t
        /// - uint16_t
        /// - int16_t
        /// - uint32_t
        /// - int32_t
        /// - float_t
        /// - double_t
        /// - bool_t
        ///
        template <typename T>
        constexpr bool_t IsNativeType = IsAny<T, char_t, uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float_t, double_t, bool_t>;

        /// @brief Checks if T is a math type.
        ///
        /// A math type is one of the following types:
        /// - Vector2
        /// - Vector2i
        /// - Vector3
        /// - Vector4
        /// - Quaternion
        /// - Matrix2
        /// - Matrix3
        /// - Matrix
        ///
        template <typename T>
        constexpr bool_t IsMathType = IsAny<T, Vector2, Vector2i, Vector3, Vector4, Quaternion, Matrix2, Matrix3, Matrix>;

        template <typename T>
        constexpr bool_t IsEqualityComparable = std::equality_comparable<T>;

        template <typename T, typename U>
        constexpr bool_t IsEqualityComparableWith = std::equality_comparable_with<T, U>;

        template <typename T>
        constexpr bool_t IsResource = Meta::IsBaseOf<Resource, T>;

        template <typename T>
        constexpr bool_t IsLoadableResource = IsResource<T> && !Meta::IsSame<T, Font>;

        template <typename T>
        constexpr bool_t IsEntry = Meta::IsBaseOf<Entry, T>;

        template <typename T>
        constexpr bool_t IsComponent = Meta::IsBaseOf<Component, T>;

        template <typename T>
        constexpr bool_t IsEntity = Meta::IsBaseOf<Entity, T>;

        template <typename T>
        constexpr bool_t IsException = IsBaseOf<std::exception, T>;

        template <typename T>
        constexpr bool_t IsMountainException = IsBaseOf<Exception, T>;

        template <typename T>
        constexpr bool_t IsStandardException = IsException<T> && !IsMountainException<T>;

        /// @brief Checks whether the type is a function type
        /// <a href="https://en.cppreference.com/w/cpp/types/is_function.html">as defined in the C++ standard</a>.
        template <typename T>
        constexpr bool_t IsFunction = std::is_function_v<T>;

        /// @brief Checks whether @p T is invocable with the given argument types.
        template <typename T, typename... Args>
        constexpr bool_t IsInvocable = std::is_invocable_v<T, Args...>;

        /// @brief Checks if @p From is **implicitly** convertible to @p To.
        template <typename From, typename To>
        constexpr bool_t IsConvertibleTo = std::is_convertible_v<From, To>;

        /// @brief Checks if T is a color type.
        ///
        /// A color type is one of the following types:
        /// - Color
        /// - ColorHsva
        ///
        template <typename T>
        constexpr bool_t IsColor = IsAny<T, Color, ColorHsva>;

        /// @brief Checks whether @p T is a pointer.
        template <typename T>
        constexpr bool_t IsPointer = std::is_pointer_v<T>;

        /// @brief Checks whether @p T is an integral type.
        template <typename T>
        constexpr bool_t IsIntegral = std::is_integral_v<T>;

        /// @brief Checks whether @p T is a floating type.
        template <typename T>
        constexpr bool_t IsFloatingPoint = std::is_floating_point_v<T>;

        /// @brief Checks if T is an integral or a floating type.
        ///
        /// An int/float type is one of the following types:
        /// - char_t
        /// - uint8_t
        /// - int8_t
        /// - uint16_t
        /// - int16_t
        /// - uint32_t
        /// - int32_t
        /// - float_t
        /// - double_t
        /// - bool_t
        ///
        template <typename T>
        constexpr bool_t IsIntegralOrFloating = IsIntegral<T> || IsFloatingPoint<T>;

        /// @brief Checks whether @p T is an enum.
        template <typename T>
        constexpr bool_t IsEnum = std::is_enum_v<T>;

        template <typename T>
        constexpr bool_t IsEffect = IsBaseOf<Effect, T>;

        template <typename T>
        constexpr bool_t IsContainerType = !IsConst<T> && !IsFunction<T> && !IsReference<T>;
    }

    /// @namespace Concepts
    /// @brief Contains useful general-use concepts.
    namespace Concepts
    {
        /// @brief Concept that forces a type to be derived from @c Resource.
        template <class T>
        concept Resource = Meta::IsResource<T>;

        /// @brief Concept that forces a type to be derived from @c Resource and is not the @c Font class.
        template <class T>
        concept LoadableResource = Meta::IsLoadableResource<T>;

        /// @brief Concept that forces a type to be derived from @c Entry.
        template <class T>
        concept Entry = Meta::IsEntry<T>;

        /// @brief Concept that forces a type to be derived from @c Component
        template <class T>
        concept Component = Meta::IsComponent<T>;

        /// @brief Concept that forces a type to be derived from @c Entity
        template <class T>
        concept Entity = Meta::IsEntity<T>;

        /// @brief Concept that forces a type to be derived from @c std::exception.
        template<typename T>
        concept Exception = Meta::IsException<T>;

        /// @brief Concept that forces a type to be derived from @c Mountain::Exception.
        template<typename T>
        concept MountainException = Meta::IsMountainException<T>;

        /// @brief Concept that forces a type to be derived from @c std::exception and not from @c Exception.
        template<typename T>
        concept StandardException = Meta::IsStandardException<T>;

        /// @brief Concept that forces a type to be a function
        template <typename T>
        concept Function = Meta::IsFunction<T>;

        /// @brief Concept that forces a type to be invocable
        template <typename T, typename... Args>
        concept Invocable = Meta::IsInvocable<T, Args...>;

        template <typename From, typename To>
        concept ConvertibleTo = Meta::IsConvertibleTo<From, To>;

        template <typename T, typename U>
        concept SameAs = Meta::IsSame<T, U>;

        /// @brief Concept that forces a type to be a color, e.g., either @c Color or @c ColorHsva
        template <typename T>
        concept Color = Meta::IsColor<T>;

        /// @brief Concept that forces a type to be a raw pointer
        template <typename T>
        concept Pointer = Meta::IsPointer<T>;

        /// @brief Concept that forces a type to be of an integral type
        template <typename T>
        concept Integral = Meta::IsIntegral<T>;

        /// @brief Concept that forces a type to be of a floating point type
        template <typename T>
        concept FloatingPoint = Meta::IsFloatingPoint<T>;

        /// @brief Concept that forces a type to be of either an integral or a floating pointer type
        template <typename T>
        concept IntegralOrFloating = Meta::IsIntegralOrFloating<T>;

        template <typename T>
        concept Enum = Meta::IsEnum<T>;

        template <class T>
        concept Effect = Meta::IsEffect<T>;

        /// @brief A container type is any non-const, non-function, non-reference type.
        template <typename T>
        concept ContainerType = Meta::IsContainerType<T>;

        /// @brief A container type is any non-const, non-function, non-reference type that can be default, copy and move constructed.
        template <typename T>
        concept DynamicContainerType = ContainerType<T>;
    }

    namespace Meta
    {
        template <Concepts::Enum T>
        using UnderlyingEnumType = std::underlying_type_t<T>;

        template <Concepts::Enum T>
        using Flags = UnderlyingEnumType<T>;
    }
};
