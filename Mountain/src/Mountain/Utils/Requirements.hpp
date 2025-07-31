#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/FunctionTypes.hpp"

// ReSharper disable CppClangTidyBugproneMacroParentheses

#define CHECK_REQUIREMENT(requirement, ...) \
    static_assert(requirement<__VA_ARGS__>, "Type <" #__VA_ARGS__ "> doesn't match the requirements of " #requirement)

#define REQUIRES_FUNCTION(value, function, expectedReturnType, ...) \
    { value.function(__VA_ARGS__) } -> ::Mountain::Concepts::ConvertibleTo<expectedReturnType>

#define REQUIRES_OPERATOR(value, operator, expectedReturnType, otherValue) \
    { value operator otherValue } -> ::Mountain::Concepts::ConvertibleTo<expectedReturnType>

#define ENUMERABLE_WRAPPER_IMPLEMENTATION(wrappedEnumerableField) \
    using WrappedEnumerable = decltype(wrappedEnumerableField); \
    using Iterator = WrappedEnumerable::Iterator; \
    using ConstIterator = WrappedEnumerable::ConstIterator; \
    using EnumeratedType = Iterator::Type; \
    \
    ATTRIBUTE_NODISCARD \
    Iterator begin() noexcept { return wrappedEnumerableField.begin(); } \
    \
    ATTRIBUTE_NODISCARD \
    Iterator end() noexcept { return wrappedEnumerableField.end(); } \
    \
    ATTRIBUTE_NODISCARD \
    ConstIterator begin() const noexcept { return wrappedEnumerableField.begin(); } \
    \
    ATTRIBUTE_NODISCARD \
    ConstIterator end() const noexcept { return wrappedEnumerableField.end(); } \
    \
    ATTRIBUTE_NODISCARD \
    ConstIterator cbegin() const noexcept { return wrappedEnumerableField.cbegin(); } \
    \
    ATTRIBUTE_NODISCARD \
    ConstIterator cend() const noexcept { return wrappedEnumerableField.cend(); }

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
        typename T::ContainedType;
        requires Concepts::ContainerType<typename T::ContainedType>;
        REQUIRES_FUNCTION(cv, GetSize, size_t);
        REQUIRES_FUNCTION(cv, IsEmpty, bool_t);
    };

    template <typename T>
    concept MountainIteratorBase = requires (T& v, const T& cv)
    {
        typename T::IteratedType;
        cv.GetCurrent();
        REQUIRES_FUNCTION(v, Reset, void);
        *cv;
        cv.operator->();
        ++v;
        v++;
        REQUIRES_OPERATOR(cv, ==, bool_t, cv);
        REQUIRES_OPERATOR(cv, <=>, std::strong_ordering, cv);
    };

    template <typename T>
    concept MountainConstIterator = MountainIteratorBase<T> && requires (T& v, const T& cv)
    {
        REQUIRES_FUNCTION(cv, GetCurrent, const typename T::IteratedType*);
        REQUIRES_FUNCTION(cv, operator*, const typename T::IteratedType&);
        REQUIRES_FUNCTION(cv, operator->, const typename T::IteratedType*);
    };

    template <typename T>
    concept MountainIterator = MountainIteratorBase<T> && requires (T& v, const T& cv)
    {
        REQUIRES_FUNCTION(cv, GetCurrent, typename T::IteratedType*);
        REQUIRES_FUNCTION(cv, operator*, typename T::IteratedType&);
        REQUIRES_FUNCTION(cv, operator->, typename T::IteratedType*);
    };

    /// @brief A type is an Enumerable if it supports iterator enumerations itself, or if it is a wrapper around another Enumerable.
    template <typename T>
    concept MountainEnumerable = requires (T& v, const T& cv)
    {
        typename T::EnumeratedType;

        typename T::Iterator;
        requires MountainIterator<typename T::Iterator>;
        REQUIRES_FUNCTION(v, begin, typename T::Iterator);
        REQUIRES_FUNCTION(v, end, typename T::Iterator);

        typename T::ConstIterator;
        requires MountainConstIterator<typename T::ConstIterator>;
        REQUIRES_FUNCTION(cv, cbegin, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, cend, typename T::ConstIterator);

        REQUIRES_FUNCTION(cv, begin, typename T::ConstIterator);
        REQUIRES_FUNCTION(cv, end, typename T::ConstIterator);

        requires Meta::AllSame<typename T::EnumeratedType, typename T::Iterator::IteratedType, typename T::ConstIterator::IteratedType>;
    };

    /// @brief A type is an Enumerable if it supports iterator enumerations itself, or if it is a wrapper around another Enumerable.
    template <typename T>
    concept MountainEnumerableWrapper = MountainEnumerable<T> && requires(T& v, const T& cv)
    {
        typename T::WrappedEnumerable;
        requires MountainEnumerable<typename T::WrappedEnumerable>;

        typename T::WrappedEnumerable::Iterator;
        requires MountainIterator<typename T::WrappedEnumerable::Iterator>;
        REQUIRES_FUNCTION(v, begin, typename T::WrappedEnumerable::Iterator);
        REQUIRES_FUNCTION(v, end, typename T::WrappedEnumerable::Iterator);

        typename T::WrappedEnumerable::ConstIterator;
        requires MountainConstIterator<typename T::WrappedEnumerable::ConstIterator>;
        REQUIRES_FUNCTION(cv, cbegin, typename T::WrappedEnumerable::ConstIterator);
        REQUIRES_FUNCTION(cv, cend, typename T::WrappedEnumerable::ConstIterator);

        REQUIRES_FUNCTION(cv, begin, typename T::WrappedEnumerable::ConstIterator);
        REQUIRES_FUNCTION(cv, end, typename T::WrappedEnumerable::ConstIterator);
    };

    template <typename T>
    concept MountainEnumerableContainer = MountainContainer<T> && MountainEnumerable<T>;

    template <typename T, typename U = T>
    concept Equatable = requires (const T& t, const U& u)
    {
        REQUIRES_OPERATOR(t, ==, bool_t, u);
    };

    template <typename T, typename U = T>
    concept Comparable = requires (const T& t, const U& u)
    {
        // std::partial_ordering is implicitly convertible to both std::weak_ordering and std::strong_ordering
        REQUIRES_OPERATOR(t, <=>, std::partial_ordering, u);
    };
}

namespace Mountain::Concepts
{
    template <typename T>
    concept StandardIterator = std::forward_iterator<T> && !Pointer<T> && !Requirements::MountainIterator<T>;

    template <typename T>
    concept StandardContainer = std::ranges::input_range<T> && !Requirements::MountainContainer<T> && !Requirements::MountainEnumerable<T>;
}

namespace Mountain::Meta
{
    template <Concepts::StandardIterator T>
    using StandardIteratorType = typename T::value_type;

    template <Concepts::StandardContainer T>
    using StandardContainerType = typename T::value_type;

    template <Concepts::StandardContainer T>
    using StandardContainerIteratorType = typename T::iterator;
}

namespace Mountain::Concepts
{
    template <typename T>
    concept Iterator = Pointer<T> || StandardIterator<T> || Requirements::MountainIterator<T>;

    template <typename T>
    concept Container = StandardContainer<T> || Requirements::MountainContainer<T>;

    template <typename T>
    concept Enumerable = StandardContainer<T> || Requirements::MountainEnumerable<T>;
}

namespace Mountain::Meta
{
    template <Requirements::MountainIterator T>
    using MountainIteratorType = typename T::IteratedType;

    template <Requirements::MountainContainer T>
    using MountainContainerType = typename T::ContainedType;

    template <Requirements::MountainEnumerable T>
    using MountainEnumerableType = typename T::EnumeratedType;

    template <Requirements::MountainEnumerable T>
    using MountainEnumerableIteratorType = typename T::Iterator;

    // ReSharper disable once CppStaticAssertFailure
    template <Concepts::Iterator>
    struct IteratorTypeS { static_assert(false); };

    template <Concepts::Pointer T>
    struct IteratorTypeS<T> { using Type = RemoveCvSpecifier<RemovePointerSpecifier<T>>; };

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

    /// @brief Checks whether @p T is sortable.
    template <Concepts::Iterator Iterator, typename Comparer, typename Projection = Mountain::Identity>
    constexpr bool_t IsSortable = std::sortable<Iterator, Comparer, Projection>;
}

#include "Mountain/Exceptions/Exception.hpp"

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
