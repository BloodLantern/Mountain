#pragma once

#include <format>

#include "Mountain/Core.hpp"

/// @file Concepts.hpp
/// @brief Defines the Mountain::Concepts namespace which contains useful concepts used in the engine.

namespace Mountain
{
    class Resource;
    class Entry;
    class Component;
    class Entity;
    class Font;
    class Effect;
    struct Color;
    struct ColorHsva;

    /// @namespace Concepts
    /// @brief Contains useful general-use concepts.
    namespace Concepts
    {
        /// @brief A class satisfies the ResourceT concept if it is derived of Resource.
        template <class T>
        concept ResourceT = std::is_base_of_v<Resource, T>;

        /// @brief A class satisfies the LoadableResourceT concept if it is derived of Resource and is not the Font class.
        template <class T>
        concept LoadableResourceT = std::is_base_of_v<Resource, T> && !std::is_same_v<T, Font>;

        /// @brief A class satisfies the EntryT concept if it is derived of Entry.
        template <class T>
        concept EntryT = std::is_base_of_v<Entry, T>;

        /// @brief Concept that forces a class to be same as the others
        template <class T, class U>
        concept IsTSameAsU = std::is_same_v<T, U>;

        /// @brief Concept that forces a type to be a child of Component
        template <class T>
        concept ComponentT = std::is_base_of_v<Component, T>;

        /// @brief Concept that forces a type to be a child of Entity
        template <class T>
        concept EntityT = std::is_base_of_v<Entity, T>;

        /// @brief The Formattable concept requires a type to be formattable.
        ///
        /// A type @p T is considered formattable if a template specialization of the @c std::formatter for @p T exists.
        ///
        /// @tparam T The type to require to be formattable.
        template<typename T>
        concept FormattableT = requires(T& v, std::format_context ctx)
        {
            std::formatter<std::remove_cvref_t<T>>().format(v, ctx);
        };

        /// @brief A class satisfies the ExceptionT concept if it is derived of Exception.
        template<typename T>
        concept ExceptionT = std::is_base_of_v<std::exception, T>;

        /// @brief Concept that forces a type to be a function
        template <class T>
        concept FunctionT = std::is_function_v<T>;

        template <typename From, typename To>
        concept ConvertibleToT = std::convertible_to<From, To>;

        /// @brief Concept that forces a type to be a color, e.g. either Color or ColorHsva
        template <class T>
        concept ColorT = std::is_same_v<Color, T> || std::is_same_v<ColorHsva, T>;

        /// @brief Concept that forces a type to be a raw pointer
        template <typename T>
        concept PointerT = std::is_pointer_v<T>;

        /// @brief Concept that forces a type to be of an integral type
        template <typename T>
        concept IntegralT = std::is_integral_v<T>;

        template <typename T>
        concept EnumT = std::is_enum_v<T>;

        template <class T>
        concept EffectT = std::is_base_of_v<Effect, T>;
    }
}
