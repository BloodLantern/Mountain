#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"

// ReSharper disable CppClangTidyBugproneMacroParentheses

#define CHECK_REQUIREMENT(requirement, ...) \
    static_assert(requirement<__VA_ARGS__>, "Type " #__VA_ARGS__ " doesn't match the requirements of " #requirement)

#define REQUIRES_FUNCTION(value, function, expectedReturnType, ...) \
    { value.function(__VA_ARGS__) } -> ::Mountain::Concepts::ConvertibleTo<expectedReturnType>

#define REQUIRES_OPERATOR(value, operator, expectedReturnType, otherValue) \
    { value operator otherValue } -> ::Mountain::Concepts::ConvertibleTo<expectedReturnType>

// ReSharper enable CppClangTidyBugproneMacroParentheses

namespace Mountain::Requirements
{
    /// @brief Default type for template instantiation in the @c CHECK_REQUIREMENT() macro.
    using DefaultType = int;

    /// @brief Default size for template instantiation in the @c CHECK_REQUIREMENT() macro.
    constexpr size_t DefaultSize = 1;

    /// @brief Requires a type to be formattable.
    /// @details A type @p T is considered formattable if a template specialization of @c std::formatter exists for @p T.
    template<typename T>
    concept Formattable = requires(T& v, std::format_context ctx)
    {
        std::formatter<std::remove_cvref_t<T>>().format(v, ctx);
    };

    /// @brief Requires a type to have a member @c ToString() function that returns a @c std::string.
    template <typename T>
    concept StringConvertible = requires (const T& cv)
    {
        REQUIRES_FUNCTION(cv, ToString, std::string);
    };

    /// @brief Requires a type to have a member @c GetHashCode() function that returns a @c size_t.
    template <typename T>
    concept Hashable = requires (const T& cv)
    {
        REQUIRES_FUNCTION(cv, GetHashCode, size_t);
    };

    template <typename T>
    concept MountainContainer = requires (T& v, const T& cv)
    {
        typename T::Type;
        requires Concepts::ContainerType<typename T::Type>;
        REQUIRES_FUNCTION(cv, GetSize, size_t);
        REQUIRES_FUNCTION(cv, IsEmpty, bool_t);
    };

    template <typename T>
    concept MountainIteratorBase = requires (T& v, const T& cv)
    {
        typename T::Type;
        cv.GetCurrent();
        REQUIRES_FUNCTION(v, Reset, void);
        *cv;
        cv.operator->();
        ++v;
        v++;
        REQUIRES_OPERATOR(cv, <=>, std::strong_ordering, cv);
    };

    template <typename T>
    concept MountainConstIterator = MountainIteratorBase<T> && requires (T& v, const T& cv)
    {
        REQUIRES_FUNCTION(cv, GetCurrent, const typename T::Type*);
        REQUIRES_FUNCTION(cv, operator*, const typename T::Type&);
        REQUIRES_FUNCTION(cv, operator->, const typename T::Type*);
    };

    template <typename T>
    concept MountainIterator = MountainIteratorBase<T> && requires (T& v, const T& cv)
    {
        REQUIRES_FUNCTION(cv, GetCurrent, typename T::Type*);
        REQUIRES_FUNCTION(cv, operator*, typename T::Type&);
        REQUIRES_FUNCTION(cv, operator->, typename T::Type*);
    };

    template <typename T>
    concept MountainEnumerable = requires (T& v, const T& cv)
    {
        typename T::Iterator;
        requires MountainIterator<typename T::Iterator>;
        REQUIRES_FUNCTION(v, GetBeginIterator, typename T::Iterator);
        REQUIRES_FUNCTION(v, GetEndIterator, typename T::Iterator);
        REQUIRES_FUNCTION(v, begin, typename T::Iterator);
        REQUIRES_FUNCTION(v, end, typename T::Iterator);

        typename T::ConstIterator;
        requires MountainConstIterator<typename T::ConstIterator>;
        REQUIRES_FUNCTION(cv, GetBeginConstIterator, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, GetEndConstIterator, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, cbegin, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, cend, typename T::ConstIterator);

        REQUIRES_FUNCTION(cv, GetBeginIterator, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, GetEndIterator, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, begin, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, end, typename T::ConstIterator);
    };

    template <typename T>
    concept MountainEnumerableContainer = MountainContainer<T> && MountainEnumerable<T>;

    template <typename T, typename U = T>
    concept Swappable = requires (T&& t, U&& u)
    {
        swap(std::forward<T>(t), std::forward<U>(u));
        swap(std::forward<U>(u), std::forward<T>(t));
    };
}

namespace Mountain::Concepts
{
    template <typename T>
    concept Iterator = StandardIterator<T> || Requirements::MountainIterator<T>;

    template <typename T>
    concept Container = StandardContainer<T> || Requirements::MountainContainer<T>;

    template <typename T>
    concept Enumerable = StandardContainer<T> || Requirements::MountainEnumerable<T>;
}

namespace Mountain::Meta
{
    template <Requirements::MountainIterator T>
    using MountainIteratorType = typename T::Type;

    template <Requirements::MountainContainer T>
    using MountainContainerType = typename T::Type;

    template <Requirements::MountainEnumerable T>
    using MountainEnumerableType = typename T::Iterator::Type;

    template <Requirements::MountainEnumerable T>
    using MountainEnumerableIteratorType = typename T::Iterator;

    // ReSharper disable once CppStaticAssertFailure
    template <Concepts::Iterator>
    struct IteratorTypeS { static_assert(false); };

    template <Concepts::StandardIterator T>
    struct IteratorTypeS<T> { using Type = StandardIteratorType<T>; };

    template <Requirements::MountainIterator T>
    struct IteratorTypeS<T> { using Type = MountainIteratorType<T>; };

    template <Concepts::Iterator T>
    using IteratorType = typename IteratorTypeS<T>::Type;

    // ReSharper disable once CppStaticAssertFailure
    template <Concepts::Container>
    struct ContainerTypeS { static_assert(false); };

    template <Concepts::StandardContainer T>
    struct ContainerTypeS<T> { using Type = StandardContainerType<T>; };

    template <Requirements::MountainContainer T>
    struct ContainerTypeS<T> { using Type = MountainContainerType<T>; };

    template <Concepts::Container T>
    using ContainerType = typename ContainerTypeS<T>::Type;

    // ReSharper disable once CppStaticAssertFailure
    template <Concepts::Enumerable>
    struct EnumerableTypeS { static_assert(false); };

    template <Concepts::StandardContainer T>
    struct EnumerableTypeS<T> { using Type = StandardContainerType<T>; };

    template <Requirements::MountainEnumerable T>
    struct EnumerableTypeS<T> { using Type = MountainEnumerableType<T>; };

    template <Concepts::Enumerable T>
    using EnumerableType = typename EnumerableTypeS<T>::Type;

    // ReSharper disable once CppStaticAssertFailure
    template <Concepts::Enumerable>
    struct EnumerableIteratorTypeS { static_assert(false); };

    template <Concepts::StandardContainer T>
    struct EnumerableIteratorTypeS<T> { using Type = StandardContainerIteratorType<T>; };

    template <Requirements::MountainEnumerable T>
    struct EnumerableIteratorTypeS<T> { using Type = MountainEnumerableIteratorType<T>; };

    template <Concepts::Enumerable T>
    using EnumerableIteratorType = typename EnumerableIteratorTypeS<T>::Type;
}

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppClangTidyCertDcl58Cpp

/// @brief @c std::formatter template specialization for the types that support @c Mountain::Requirements::StringConvertible.
/// @details The goal of this formatter specialization is to allow any type that provides a member function @c ToString()
/// to be used in a call to @c std::format().
template <Mountain::Requirements::StringConvertible StringConvertibleT>
struct std::formatter<StringConvertibleT>
{
    /// @brief Parses the input formatting options.
    template <class ParseContextT>
    constexpr typename ParseContextT::iterator parse(ParseContextT& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw Mountain::FormatException{"Invalid format arguments for Mountain::ToString()"};

        return it;
    }

    /// @brief Formats a string using the given type supporting @c ToString(), according to the given options in the parse function.
    template <class FormatContextT>
    typename FormatContextT::iterator format(const StringConvertibleT& sc, FormatContextT& ctx) const
    {
        std::ostringstream out;

        out << sc.ToString();

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

/// @brief @c std::hash template specialization for the types that support @c GetHashCode().
/// @details The real goal of this formatter specialization is to allow any type that provides a member function @c GetHashCode()
/// to be used in a call to @c std::hash::operator().
template<Mountain::Requirements::Hashable HashableT>
struct std::hash<HashableT>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Hashes the given type supporting @c GetHashCode().
    std::size_t operator()(const HashableT& p) const noexcept { return p.GetHashCode(); }
};

// ReSharper enable CppMemberFunctionMayBeStatic
// ReSharper enable CppClangTidyCertDcl58Cpp
