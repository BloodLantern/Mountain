#pragma once

#include "Mountain/Core.hpp"

namespace Mountain
{
    template <typename T>
    struct Optional
    {
        ATTRIBUTE_NODISCARD
        constexpr Optional();

        ATTRIBUTE_NODISCARD
        // ReSharper disable once CppNonExplicitConvertingConstructor
        constexpr Optional(T&& value);

        ATTRIBUTE_NODISCARD
        // ReSharper disable once CppNonExplicitConvertingConstructor
        constexpr Optional(const T& value);

        template <Concepts::ConvertibleTo<T> U>
        ATTRIBUTE_NODISCARD
        constexpr Optional(std::optional<U>&& otherOptional);

        template <Concepts::ConvertibleTo<T> U>
        ATTRIBUTE_NODISCARD
        constexpr Optional(const std::optional<U>& otherOptional);

        template <Concepts::ConvertibleTo<T> U>
        ATTRIBUTE_NODISCARD
        constexpr Optional(Optional<U>&& otherOptional);

        template <Concepts::ConvertibleTo<T> U>
        ATTRIBUTE_NODISCARD
        constexpr Optional(const Optional<U>& otherOptional);

        ATTRIBUTE_NODISCARD
        constexpr bool_t HasValue() const noexcept;

        ATTRIBUTE_NODISCARD
        constexpr T& Value() &;
        ATTRIBUTE_NODISCARD
        constexpr const T& Value() const &;

        ATTRIBUTE_NODISCARD
        constexpr T&& Value() &&;
        ATTRIBUTE_NODISCARD
        constexpr const T&& Value() const &&;

        template <Concepts::ConvertibleTo<T> U>
        ATTRIBUTE_NODISCARD
        constexpr T ValueOr(U defaultValue) const & noexcept;

        template <Concepts::ConvertibleTo<T> U>
        ATTRIBUTE_NODISCARD
        constexpr T ValueOr(U defaultValue) && noexcept;

        template <typename = Meta::EnableIf<Meta::IsDefaultConstructible<T>>>
        ATTRIBUTE_NODISCARD
        constexpr T ValueOrDefault() const noexcept;

        constexpr void Reset() noexcept;

        ATTRIBUTE_NODISCARD
        constexpr explicit operator bool_t() const noexcept;

    private:
        struct Dummy{};

        bool_t m_HasValue = false;
        union
        {
            Dummy dummy;
            T value;
        };
    };
}

// Start of Optional.inl

#define OPTIONAL_VALUE_BODY \
    if (!m_HasValue) \
        THROW(ThrowHelper::OptionalNoValueException()); \
    return value;

namespace Mountain
{
    template <typename T>
    constexpr Optional<T>::Optional() : dummy{} {}

    template <typename T>
    constexpr Optional<T>::Optional(T&& value) : m_HasValue{true}, value{std::move(value)} {}

    template <typename T>
    constexpr Optional<T>::Optional(const T& value) : m_HasValue{true}, value{value} {}

    template <typename T>
    template <Concepts::ConvertibleTo<T> U>
    constexpr Optional<T>::Optional(std::optional<U>&& otherOptional)  // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
        : m_HasValue{std::move(otherOptional.has_value())}
    {
        if (m_HasValue)
            new (&value) T{std::move(otherOptional.value())};
    }

    template <typename T>
    template <Concepts::ConvertibleTo<T> U>
    constexpr Optional<T>::Optional(const std::optional<U>& otherOptional)
        : m_HasValue{otherOptional.has_value()}
    {
        if (m_HasValue)
            new (&value) T{otherOptional.value()};
    }

    template <typename T>
    template <Concepts::ConvertibleTo<T> U>
    constexpr Optional<T>::Optional(Optional<U>&& otherOptional)  // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
        : m_HasValue{std::move(otherOptional.HasValue())}
    {
        if (m_HasValue)
            new (&value) T{std::move(otherOptional.Value())};
    }

    template <typename T>
    template <Concepts::ConvertibleTo<T> U>
    constexpr Optional<T>::Optional(const Optional<U>& otherOptional)
        : m_HasValue{otherOptional.HasValue()}
    {
        if (m_HasValue)
            new (&value) T{otherOptional.Value()};
    }

    template <typename T>
    constexpr bool_t Optional<T>::HasValue() const noexcept { return m_HasValue; }

    template <typename T>
    constexpr T& Optional<T>::Value() & { OPTIONAL_VALUE_BODY }

    template <typename T>
    constexpr const T& Optional<T>::Value() const & { OPTIONAL_VALUE_BODY }

    template <typename T>
    constexpr T&& Optional<T>::Value() && { OPTIONAL_VALUE_BODY }

    template <typename T>
    constexpr const T&& Optional<T>::Value() const && { OPTIONAL_VALUE_BODY }

    template <typename T>
    template <Concepts::ConvertibleTo<T> U>
    constexpr T Optional<T>::ValueOr(U defaultValue) const & noexcept { return m_HasValue ? value : defaultValue; }

    template <typename T>
    template <Concepts::ConvertibleTo<T> U>
    constexpr T Optional<T>::ValueOr(U defaultValue) && noexcept { return m_HasValue ? value : defaultValue; }

    template <typename T>
    template <typename>
    constexpr T Optional<T>::ValueOrDefault() const noexcept { return ValueOr(T{}); }

    template <typename T>
    constexpr void Optional<T>::Reset() noexcept { m_HasValue = false; }

    template <typename T>
    constexpr Optional<T>::operator bool() const noexcept { return m_HasValue; }
}

#undef OPTIONAL_VALUE_BODY
