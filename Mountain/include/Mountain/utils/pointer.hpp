#pragma once

#include <format>
#include <ostream>
#include <sstream>
#include <utility>

#include "Mountain/core.hpp"
#include "Mountain/utils/reference_counter.hpp"

/// @file pointer.hpp
/// @brief Defines the Mountain::Pointer class

BEGIN_MOUNTAIN

/// @brief Custom Mountain smart pointer.
///        Represents both a @c std::shared_ptr and a @c std::weak_ptr.
///
/// ### Reason
/// While using @c std::weak_ptr, we realized that it was not very practical because a @c std::shared_ptr needs to be
/// constructed from the former for the pointed type to be used. The Pointer type is meant to fix this issue
/// by being both a strong and a weak shared pointer.
///
/// ### Usage
/// The simplest way to create a Pointer to wrap your type is by using the forwarding variadic template function
/// which allows you to do the following:
/// @code
/// struct Type { int i; explicit Type(int i) : i(i) {} };
///
/// Pointer<Type> ptr = Pointer<Type>::New(7);
/// @endcode
/// ... and 7 will be forwarded as a parameter to the @c Type(int) constructor.
///
/// There are 3 other ways of initializing a Pointer:
/// @code
/// // 1 - Default initialize the Pointer: this wraps a nullptr
/// Pointer<Type> ptr;
///
/// // 2 - Default initialize the wrapped value: this effectively calls the wrapped type's default constructor
/// Pointer<Type> ptr = Pointer<Type>::New();
///
/// // 3 - Manually set the Pointer to nullptr: this is actually the same as default initializing it
/// Pointer<Type> ptr = nullptr;
/// @endcode
///
/// ### Weak and Strong References
/// By default, creating a Pointer with constructor arguments from the pointed type allocates this type on the heap.
/// Copying this instance of Pointer creates a new weak reference by default, meaning that the copy won't keep the raw
/// pointer alive. When all the strong references go out of scope or are destroyed, the underlying pointed type is freed.
/// A strong reference can still be created if needed, by calling either Pointer::CreateStrongReference(),
/// Pointer::ToStrongReference(), or by creating a copy using @ref Pointer::Pointer(const Pointer&, bool) "the copy constructor"
/// and giving a @c true value to the second argument.
///
/// @tparam T The type to point to. Most of the time, this shouldn't be a pointer type.
/// 
/// @see <a href="https://en.cppreference.com/book/intro/smart_pointers">Smart Pointers</a>
/// @see <a href="https://en.cppreference.com/w/cpp/memory/shared_ptr">std::shared_ptr</a>
/// @see <a href="https://en.cppreference.com/w/cpp/memory/weak_ptr">std::weak_ptr</a>
template <typename T>
class Pointer final
{
public:
    /// @brief The type of ReferenceCounter, and therefore the type this Pointer is pointing to.
    using Type = T;

    /// @brief Creates a Pointer, calling @c new with @p T and forwarding all given arguments to its constructor.
    template <typename... Args>
    static Pointer New(Args&&... args);

    /// @brief Creates a @ref Pointer with a default-initialized value.
    static Pointer New();
    
    /// @brief Creates an empty @ref Pointer without a reference counter and pointing to @c nullptr.
    Pointer() = default;
    
    /// @brief Creates a copy of another @ref Pointer, specifying whether it is a weak or strong reference.
    Pointer(const Pointer& other, bool_t strongReference = false);

    /// @brief Creates a Pointer by moving all the values of an existing one.
    Pointer(Pointer&& other) noexcept;

    // ReSharper disable once CppNonExplicitConvertingConstructor
    /// @brief Creates a Pointer from a @c nullptr.
    Pointer(nullptr_t);

    /// @brief Creates a copy of an existing Pointer of a different Type, specifying whether it is a strong reference.
    ///
    /// @tparam U The type of the existing Pointer. This type must be convertible to Type.
    template <typename U>
    explicit Pointer(const Pointer<U>& other, bool_t strongReference = false);

    /// @brief Creates a copy of an existing Pointer of a different Type, specifying whether it is a strong reference.
    template <typename U>
    explicit Pointer(Pointer<U>& other, bool_t strongReference = false);

    /// @brief Creates a Pointer by moving the value of another one of a different Type.
    template <typename U>
    explicit Pointer(Pointer<U>&& other) noexcept;

    /// @brief Destroys this Pointer, deallocating any memory if this is the last strong reference.
    ~Pointer();

    /// @brief Creates a new strong reference to this pointer.
    [[nodiscard]]
    Pointer CreateStrongReference() const;

    /// @brief Gets the underlying raw pointer.
    ///
    /// This is equivalent to calling Pointer::operator T*() const;
    [[nodiscard]]
    const T* Get() const;

    /// @brief Gets the underlying raw pointer.
    ///
    /// This is equivalent to calling Pointer::operator T*();
    [[nodiscard]]
    T* Get();

    /// @brief Returns whether this Pointer is @c nullptr.
    [[nodiscard]]
    bool_t IsValid() const;

    /// @brief Converts this @ref Pointer to a strong reference.
    void ToStrongReference();

    /// @brief Converts this @ref Pointer to a weak reference.
    void ToWeakReference();

    /// @brief Returns the underlying ReferenceCounter.
    [[nodiscard]]
    const ReferenceCounter<T>* GetReferenceCounter() const;

    /// @brief Returns whether this Pointer is holding a strong reference.
    [[nodiscard]]
    bool_t GetIsStrongReference() const;

    /// @brief Resets this Pointer to a @c nullptr.
    ///
    /// @warning
    /// This function is used internally and is not meant to be used except if you really know what you
    /// are doing. This doesn't free the potentially allocated memory. Use it at your own risks.
    void Reset();

    /// @brief Sets this Pointer to the values of @p other.
    Pointer& operator=(const Pointer& other);

    /// @brief Sets this Pointer to the values of @p other, moving all the data.
    Pointer& operator=(Pointer&& other) noexcept;

    /// @brief Sets this Pointer to @c nullptr.
    Pointer& operator=(nullptr_t);

    /// @brief Sets this Pointer to the values of @p other which is a Pointer of another Type.
    template <typename U>
    Pointer& operator=(const Pointer<U>& other);

    /// @brief Sets this Pointer to the values of @p other which is a Pointer of another Type, moving all the data.
    template <typename U>
    Pointer& operator=(Pointer<U>&& other) noexcept;

    /// @brief Converts this @c const Pointer to its underlying @c const raw pointer.
    [[nodiscard]]
    explicit operator const T*() const;

    /// @brief Converts this Pointer to its underlying raw pointer.
    [[nodiscard]]
    explicit operator T*();
    
    // ReSharper disable once CppNonExplicitConversionOperator
    /// @brief Converts this @ref Pointer to a @c bool_t the same way a raw pointer would.
    [[nodiscard]]
    operator bool_t() const;

    /// @brief Dereferences this Pointer, which gives a reference to the underlying Type.
    [[nodiscard]]
    T& operator*();
    
    /// @brief Dereferences this @c const Pointer, which gives a @c const reference to the underlying Type.
    [[nodiscard]]
    const T& operator*() const;

    /// @brief Dereferences this Pointer, which gives a reference to the underlying Type.
    [[nodiscard]]
    T* operator->();
    
    /// @brief Dereferences this @c const Pointer, which gives a @c const reference to the underlying Type.
    [[nodiscard]]
    const T* operator->() const;
    
private:
    ReferenceCounter<T>* m_ReferenceCounter = nullptr;

    bool_t m_IsStrongReference = false;

    explicit Pointer(ReferenceCounter<T>*&& referenceCounter, bool_t strongReference);

    void SetReferenceCounter(ReferenceCounter<T>* newReferenceCounter);

    void CheckReferenceCounterValid();
};

END_MOUNTAIN

#include "Mountain/utils/pointer.inl"

/// @brief @c std::formatter template specialization for the Mountain::Pointer type.
template <typename T>
struct std::formatter<Mountain::Pointer<T>>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;
 
        if (*it != '}')
            throw std::format_error("Invalid format args for Mountain::Pointer");
 
        return it;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    /// @brief Formats a string using the given instance of Mountain::Pointer, according to the given options in the parse function.
    template <class FormatContext>
    typename FormatContext::iterator format(const Mountain::Pointer<T>& pointer, FormatContext& ctx) const
    {
        std::ostringstream out;
        
        out << "0x" << static_cast<const T*>(pointer);
        
        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

/// @brief @c std::hash template specialization for the Mountain::Pointer type.
template<typename T>
struct std::hash<Mountain::Pointer<T>>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Hashes the given Mountain::Pointer.
    std::size_t operator()(const Mountain::Pointer<T>& p) const noexcept
    {
        const std::size_t h1 = std::hash<decltype(p.GetReferenceCounter())>{}(const_cast<decltype(p.GetReferenceCounter())>(p.GetReferenceCounter()));
        const std::size_t h2 = std::hash<bool_t>{}(p.GetIsStrongReference());
        return h1 ^ (h2 << 1);
    }
};
