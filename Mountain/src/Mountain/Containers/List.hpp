#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/ContiguousIterator.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"

/// @file List.hpp
/// @brief Defines the Mountain::List class.

namespace Mountain
{
    template <Concepts::ContainerType T, usize Size>
    struct Array;

    /// @brief A dynamic array implementation.
    ///
    /// A more user-friendly list than @c std::vector, based on how @c List is in C#.
    /// The internal structure and workings are similar to how std::vector works,
    /// it uses a capacity that grows exponentially based on powers of 2.
    ///
    /// @tparam T Type stored
    ///
    /// @see <a href="https://en.cppreference.com/w/cpp/container/vector">std::vector</a>
    /// @see <a href="https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1">C# List</a>
    template <Concepts::DynamicContainerType T>
    class List
    {
    public:
        /// @brief The type of the List. Refers to T.
        using Type = T;
        using ContainedType = Type;
        using EnumeratedType = Type;
        using Iterator = ContiguousIterator<T>;
        using ConstIterator = ContiguousConstIterator<T>;

        List() noexcept = default;

        /// @brief Constructs a List from a range of elements.
        template <Concepts::ConvertibleTo<T>... U>
        explicit List(U&&... values) noexcept;

        /// @brief Constructs a List from a range of elements.
        List(std::initializer_list<T> initializer) noexcept;

        explicit List(usize initialSize) noexcept;

        /// @brief Constructs a List from the specified size, and fills it with the provided value.
        /// @param initialSize List size
        /// @param defaultValue Default value
        List(usize initialSize, const T& defaultValue);

        /// @brief Constructs a List from the specified size, and fills it with the provided values.
        /// @param initialSize List size
        /// @param values Provided values
        List(usize initialSize, const T* values);

        /// @brief Constructs a List from the specified array. This creates a copy of the given array contents.
        /// @tparam Size The @p array size
        template <usize Size>
        explicit List(const std::array<T, Size>& array);

        /// @brief Constructs a List from the specified array. This creates a copy of the given array contents.
        /// @tparam Size The @p array size
        template <usize Size>
        explicit List(const Array<T, Size>& array);

        /// @brief Constructs a List from the specified vector. This creates a copy of the given vector contents.
        explicit List(const std::vector<T>& vector);

        template <Concepts::Iterator InputIterator>
        List(InputIterator first, InputIterator last);

        ~List() noexcept;

        // Copy/Move operations
        List(const List& other) noexcept;
        List(List&& other) noexcept;
        List& operator=(const List& other) noexcept;
        List& operator=(List&& other) noexcept;

        /// @brief Checks if the given @p iterator is valid for this List.
        /// @return @c true if the @p iterator points to elements of this List, the List hasn't changed size since the iterator was constructed,
        /// and if it is still inbounds; or @c false if any of these conditions fail.
        ATTRIBUTE_NODISCARD
        bool CheckIterator(Iterator iterator) const;

        T& Add(T&& element);

        T& Add(const T& element);

        /// @brief Adds a range of elements to the end of the List.
        void AddRange(const T* data, usize count) requires Meta::IsTriviallyCopyable<T>;

        /// @brief Adds a range of elements to the end of the List.
        template <Concepts::Iterator InputIterator>
        void AddRange(InputIterator first, InputIterator last);

        /// @brief Adds a range of elements to the end of the List.
        template <Concepts::Enumerable EnumerableT>
        void AddRange(const EnumerableT& enumerable);

        /// @brief Adds a range of elements to the end of the List.
        template <Concepts::ConvertibleTo<T>... U>
        void AddRange(U&&... values);

        /// @brief Adds a range of elements to the end of the List.
        void AddRange(const std::initializer_list<T>& values);

        /// @brief Adds a range of elements to the end of the List. This creates a copy of the given array contents.
        /// @tparam Size The @p array size
        template <usize Size>
        void AddRange(const std::array<T, Size>& array);

        /// @brief Adds a range of elements to the end of the List. This creates a copy of the given array contents.
        /// @tparam Size The @p array size
        template <usize Size>
        void AddRange(const Array<T, Size>& array);

        /// @brief Adds a range of elements to the end of the List. This creates a copy of the given vector contents.
        void AddRange(const std::vector<T>& vector);

        /// @brief Adds a range of elements to the end of the List. This creates a copy of the given enumerable contents.
        template <Requirements::MountainEnumerable EnumerableT>
        void AddRange(const EnumerableT& enumerable);

        /// @brief Fills the List with a specified value.
        void Fill(const T& value);

        /// @brief Constructs a new element with the given arguments and adds it to the end of the list.
        /// @tparam Args Constructor element types
        /// @param args Constructor arguments
        template <typename... Args>
        T& Emplace(Args&&... args);

        template <typename... Args>
        T& Emplace(usize index, Args&&... args);

        template <typename... Args>
        T& Emplace(Iterator iterator, Args&&... args);

        T& Insert(usize index, T&& element);

        T& Insert(usize index, const T& element);

        T& Insert(Iterator iterator, T&& element);

        T& Insert(Iterator iterator, const T& element);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(usize index, const T* data, usize count);

        /// @brief Inserts a range of elements at the given position.
        template <Concepts::Iterator InputIterator>
        void InsertRange(usize index, InputIterator first, InputIterator last);

        /// @brief Inserts a range of elements at the given position.
        template <Concepts::Enumerable EnumerableT>
        void InsertRange(usize index, EnumerableT enumerable);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(usize index, const std::initializer_list<T>& values);

        /// @brief Inserts a range of elements at the given position.
        /// @tparam Size The @p array size
        template <usize Size>
        void InsertRange(usize index, const std::array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        /// @tparam Size The @p array size
        template <usize Size>
        void InsertRange(usize index, const Array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(usize index, const std::vector<T>& vector);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(Iterator iterator, const T* data, usize count);

        /// @brief Inserts a range of elements at the given position.
        template <Concepts::Iterator InputIterator>
        void InsertRange(Iterator iterator, InputIterator first, InputIterator last);

        /// @brief Inserts a range of elements at the given position.
        template <Concepts::Enumerable EnumerableT>
        void InsertRange(Iterator iterator, EnumerableT enumerable);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(Iterator iterator, const std::initializer_list<T>& values);

        /// @brief Inserts a range of elements at the given position.
        /// @tparam Size The @p array size
        template <usize Size>
        void InsertRange(Iterator iterator, const std::array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        /// @tparam Size The @p array size
        template <usize Size>
        void InsertRange(Iterator iterator, const Array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(Iterator iterator, const std::vector<T>& vector);

        void Resize(usize newSize);

        void Resize(usize newSize, const T& newElementsValue);

        void Reserve(usize newMinimumCapacity);

        ATTRIBUTE_NODISCARD
        usize GetCapacity() const;

        void Shrink();

        void Clear();

        ATTRIBUTE_NODISCARD
        bool IsEmpty() const;

        void Remove(const T& value);

        void RemoveAt(usize index);

        void RemoveAt(Iterator iterator);

        void RemoveFirst();

        void RemoveLast();

        void RemoveAll(const Predicate<T>& predicate);

        void RemoveRange(usize index, usize count);

        void RemoveRange(Iterator iterator, usize count);

        T PopFront();

        T PopBack();

        /// @brief Get the element at the given index with bounds checking.
        ATTRIBUTE_NODISCARD
        T& At(usize index) const;

        /// @brief Get the element at the given iterator with bounds checking.
        ATTRIBUTE_NODISCARD
        T& At(Iterator iterator) const;

        /// @brief Get the size of the list.
        ATTRIBUTE_NODISCARD
        usize GetSize() const noexcept;

        ATTRIBUTE_NODISCARD
        T* GetData() const noexcept;

        /// @brief Get the element at the given index without bounds checking.
        ATTRIBUTE_NODISCARD
        T& operator[](usize index) const noexcept;

        ATTRIBUTE_NODISCARD
        Iterator begin() noexcept;

        ATTRIBUTE_NODISCARD
        Iterator end() noexcept;

        ATTRIBUTE_NODISCARD
        ConstIterator begin() const noexcept;

        ATTRIBUTE_NODISCARD
        ConstIterator end() const noexcept;

        ATTRIBUTE_NODISCARD
        ConstIterator cbegin() const noexcept;

        ATTRIBUTE_NODISCARD
        ConstIterator cend() const noexcept;

        ENUMERABLE_EXTENSIONS_IMPLEMENTATION

        template <typename U, typename = Meta::EnableIf<Meta::IsConvertibleTo<EnumeratedType, U>>>
        ATTRIBUTE_NODISCARD
        List<U> Cast() const
        {
            List<U> result;
            result.Reserve(m_Size);

            for (const EnumeratedType& element : *this)
                result.Add(static_cast<U>(element));

            return result;
        }

        template <Concepts::Invocable<EnumeratedType> ProjectionFunctionT, typename U = decltype(ProjectionFunctionT{}(EnumeratedType{}))>
        ATTRIBUTE_NODISCARD
        List<U> Select(const ProjectionFunctionT& function) const
        {
            List<U> result;
            result.Reserve(m_Size);

            for (const EnumeratedType& element : *this)
                result.Add(function(element));

            return result;
        }

    private:
        T* m_Data = nullptr;
        usize m_Size = 0;
        usize m_Capacity = 0;

        void Reallocate(usize targetCapacity);
        void IncreaseCapacity();
        void IncreaseCapacityIfFull();
        void DestroyElements(usize first, usize last);
        /// @brief Shift all elements in the range [@p first, @p last) by @p amount elements.
        void ShiftElements(ptrdiff_t amount, usize first, usize last);
        void CheckIteratorThrow(Iterator iterator);
    };

    CHECK_REQUIREMENT(Requirements::MountainEnumerableContainer, List<Requirements::DefaultType>);
}

// Start of List.inl

#include "Mountain/Containers/Array.hpp"

namespace Mountain
{
    template <Concepts::DynamicContainerType T>
    template <Concepts::ConvertibleTo<T>... U>
    List<T>::List(U&&... values) noexcept : List{{std::forward<U>(values)...}} {}

    template <Concepts::DynamicContainerType T>
    List<T>::List(std::initializer_list<T> initializer) noexcept
    {
        const usize size = initializer.size();

        Reserve(size);

        const T* first = initializer.begin();
        for (usize i = 0; i < size; i++)
            new (m_Data + i) T{first[i]};

        m_Size = size;
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(const usize initialSize) noexcept
    {
        Resize(initialSize);
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(const usize initialSize, const T& defaultValue)
    {
        Resize(initialSize, defaultValue);
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(const usize initialSize, const T* values)
    {
        Reserve(initialSize);
        m_Size = initialSize;
        for (usize i = 0; i < initialSize; i++)
            new (m_Data + i) T{values[i]};
    }

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    List<T>::List(const std::array<T, Size>& array) : List(array.begin(), array.end()) {}

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    List<T>::List(const Array<T, Size>& array) : List(array.begin(), array.end()) {}

    template <Concepts::DynamicContainerType T>
    List<T>::List(const std::vector<T>& vector) : List(vector.begin(), vector.end()) {}

    template <Concepts::DynamicContainerType T>
    template <Concepts::Iterator InputIterator>
    List<T>::List(InputIterator first, InputIterator last)
    {
        const usize newSize = last - first;
        Reserve(newSize);
        m_Size = newSize;
        for (InputIterator it = first; it != last; ++it)
        {
            const usize index = it - first;
            new (m_Data + index) T{*it};
        }
    }

    template <Concepts::DynamicContainerType T>
    List<T>::~List() noexcept
    {
        DestroyElements(0, m_Size);
        std::free(static_cast<void*>(m_Data));
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(const List& other) noexcept
    {
        *this = other;
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(List&& other) noexcept
        : m_Data(std::move(other.m_Data))
        , m_Size(other.m_Size)
        , m_Capacity(other.m_Capacity)
    {
        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;
    }

    template <Concepts::DynamicContainerType T>
    List<T>& List<T>::operator=(const List& other) noexcept
    {
        if (&other == this)
            return *this;

        Reallocate(other.m_Capacity);
        m_Size = other.m_Size;
        for (usize i = 0; i < m_Size; i++)
            new (m_Data + i) T{other.m_Data[i]};

        return *this;
    }

    template <Concepts::DynamicContainerType T>
    List<T>& List<T>::operator=(List&& other) noexcept
    {
        if (&other == this)
            return *this;

        m_Data = std::move(other.m_Data);
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;

        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;

        return *this;
    }

    template <Concepts::DynamicContainerType T>
    bool List<T>::CheckIterator(Iterator iterator) const
    {
        return iterator.GetFirstElement() == m_Data && iterator.GetIndex() < m_Size;
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::Add(T&& element)
    {
        IncreaseCapacityIfFull();

        return *new (static_cast<void*>(m_Data + m_Size++)) T{std::move(element)};
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::Add(const T& element)
    {
        IncreaseCapacityIfFull();

        return *new (static_cast<void*>(m_Data + m_Size++)) T{element};
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::AddRange(const T* data, const usize count) requires Meta::IsTriviallyCopyable<T>
    {
        Reserve(m_Size + count);

        if constexpr (Meta::IsTriviallyCopyConstructible<T>)
        {
            std::memcpy(static_cast<void*>(m_Data + m_Size), static_cast<const void*>(data), count * sizeof(T));  // NOLINT(bugprone-sizeof-expression)
        }
        else
        {
            for (usize i = 0; i < count; i++)
                new (m_Size + i) T{data[i]};
        }

        m_Size += count;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Iterator InputIterator>
    void List<T>::AddRange(InputIterator first, InputIterator last)
    {
        static_assert(Meta::IsConvertibleTo<Meta::IteratorType<InputIterator>, T>, "List::AddRange() needs the type of the iterator to be the same as the List");

        const usize additionalSize = last - first;

        Reserve(m_Size + additionalSize);

        for (InputIterator it = first; it != last; ++it)
        {
            const usize index = it - first;
            new (static_cast<void*>(m_Data + m_Size + index)) T{*it};
        }

        m_Size += additionalSize;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Enumerable EnumerableT>
    void List<T>::AddRange(const EnumerableT& enumerable)
    {
        static_assert(Meta::IsConvertibleTo<Meta::EnumerableType<EnumerableT>, T>, "List::AddRange() needs the type of the enumerable to be the same as the List");

        AddRange(enumerable.begin(), enumerable.end());
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::ConvertibleTo<T> ... U>
    void List<T>::AddRange(U&&... values)
    {
        AddRange({std::forward<U>(values)...});
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::AddRange(const std::initializer_list<T>& values)
    {
        AddRange(values.begin(), values.end());
    }

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    void List<T>::AddRange(const std::array<T, Size>& array)
    {
        AddRange(array.data(), Size);
    }

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    void List<T>::AddRange(const Array<T, Size>& array)
    {
        AddRange(array.GetData(), Size);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::AddRange(const std::vector<T>& vector)
    {
        AddRange(vector.data(), vector.size());
    }

    template <Concepts::DynamicContainerType T>
    template <Requirements::MountainEnumerable EnumerableT>
    void List<T>::AddRange(const EnumerableT& enumerable)
    {
        AddRange(enumerable.begin(), enumerable.end());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::Fill(const T& value)
    {
        for (usize i = 0; i < m_Size; i++)
            m_Data[i] = value;
    }

    template <Concepts::DynamicContainerType T>
    template <typename... Args>
    T& List<T>::Emplace(Args&&... args)
    {
        IncreaseCapacityIfFull();

        return *new (static_cast<void*>(m_Data + m_Size++)) T{std::forward<Args>(args)...};
    }

    template <Concepts::DynamicContainerType T>
    template <typename... Args>
    T& List<T>::Emplace(usize index, Args&&... args)
    {
        if (index > m_Size)
            THROW(ArgumentOutOfRangeException{"Cannot insert element at index > m_Size", "index"});

        if (index == m_Size)
            return Emplace(std::forward<Args>(args)...);

        IncreaseCapacityIfFull();

        ShiftElements(1, index, m_Size++);

        return *new (static_cast<void*>(m_Data + index)) T{std::forward<Args>(args)...};
    }

    template <Concepts::DynamicContainerType T>
    template <typename... Args>
    T& List<T>::Emplace(Iterator iterator, Args&&... args)
    {
        CheckIteratorThrow(iterator);
        return Emplace(iterator.GetIndex(), std::forward<Args>(args)...);
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::Insert(const usize index, T&& element)
    {
        if (index > m_Size)
            THROW(ArgumentOutOfRangeException{"Cannot insert element at index > m_Size", "index"});

        if (index == m_Size)
            return Add(std::move(element));

        IncreaseCapacityIfFull();

        ShiftElements(1, index, m_Size++);

        return *new (static_cast<void*>(m_Data + index)) T{std::move(element)};
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::Insert(const usize index, const T& element)
    {
        if (index > m_Size)
            THROW(ArgumentOutOfRangeException{"Cannot insert element at index > m_Size", "index"});

        if (index == m_Size)
            return Add(element);

        IncreaseCapacityIfFull();

        ShiftElements(1, index, m_Size++);

        return *new (static_cast<void*>(m_Data + index)) T{element};
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::Insert(Iterator iterator, T&& element)
    {
        CheckIteratorThrow(iterator);
        return Insert(iterator.GetIndex(), std::move(element));
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::Insert(Iterator iterator, const T& element)
    {
        CheckIteratorThrow(iterator);
        return Insert(iterator.GetIndex(), element);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const usize index, const T* data, const usize count)
    {
        if (index > m_Size)
            THROW(ArgumentOutOfRangeException{"Cannot insert elements at index > m_Size", "index"});

        if (index == m_Size)
        {
            AddRange(data, count);
            return;
        }

        Reserve(m_Size + count);
        ShiftElements(count, index, m_Size);

        if constexpr (Meta::IsTriviallyCopyConstructible<T>)
        {
            std::memcpy(static_cast<void*>(m_Data + index), static_cast<const void*>(data), count * sizeof(T));  // NOLINT(bugprone-sizeof-expression)
        }
        else
        {
            for (usize i = 0; i < count; i++)
                new (index + i) T{data[i]};
        }

        m_Size += count;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Iterator InputIterator>
    void List<T>::InsertRange(const usize index, InputIterator first, InputIterator last)
    {
        static_assert(Meta::IsConvertibleTo<Meta::IteratorType<InputIterator>, T>, "List::InsertRange() needs the type of the iterator to be the same as the List");

        const usize additionalSize = last - first;

        Reserve(m_Size + additionalSize);
        ShiftElements(additionalSize, index, m_Size);

        for (InputIterator it = first; it != last; ++it)
        {
            const usize i = it - first;
            new (static_cast<void*>(m_Data + index + i)) T{*it};
        }

        m_Size += additionalSize;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Enumerable EnumerableT>
    void List<T>::InsertRange(const usize index, EnumerableT enumerable)
    {
        static_assert(Meta::IsConvertibleTo<Meta::EnumerableType<EnumerableT>, T>, "List::InsertRange() needs the type of the enumerable to be the same as the List");

        return InsertRange(index, enumerable.begin(), enumerable.end());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const usize index, const std::initializer_list<T>& values)
    {
        return InsertRange(index, values.begin(), values.size());
    }

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    void List<T>::InsertRange(const usize index, const std::array<T, Size>& array)
    {
        return InsertRange(index, array.data(), Size);
    }

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    void List<T>::InsertRange(const usize index, const Array<T, Size>& array)
    {
        return InsertRange(index, array.GetData(), Size);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const usize index, const std::vector<T>& vector)
    {
        return InsertRange(index, vector.data(), vector.size());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const Iterator iterator, const T* data, usize count)
    {
        CheckIteratorThrow(iterator);
        return InsertRange(iterator.GetIndex(), data, count);
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Iterator InputIterator>
    void List<T>::InsertRange(Iterator iterator, InputIterator first, InputIterator last)
    {
        CheckIteratorThrow(iterator);
        return InsertRange(iterator.GetIndex(), first, last);
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Enumerable EnumerableT>
    void List<T>::InsertRange(Iterator iterator, EnumerableT enumerable)
    {
        return InsertRange(iterator, enumerable.begin(), enumerable.end());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const Iterator iterator, const std::initializer_list<T>& values)
    {
        return InsertRange(iterator, values.begin(), values.size());
    }

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    void List<T>::InsertRange(const Iterator iterator, const std::array<T, Size>& array)
    {
        return InsertRange(iterator, array.data(), Size);
    }

    template <Concepts::DynamicContainerType T>
    template <usize Size>
    void List<T>::InsertRange(const Iterator iterator, const Array<T, Size>& array)
    {
        return InsertRange(iterator, array.GetData(), Size);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const Iterator iterator, const std::vector<T>& vector)
    {
        return InsertRange(iterator, vector.data(), vector.size());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::Resize(const usize newSize) { Resize(newSize, {}); }

    template <Concepts::DynamicContainerType T>
    void List<T>::Resize(const usize newSize, const T& newElementsValue)
    {
        if (m_Size == newSize)
            return;

        if (m_Size > newSize)
        {
            // Container size is decreasing, we need to destroy elements
            DestroyElements(newSize, m_Size);
        }
        else //if (m_Size < newSize)
        {
            Reserve(newSize); // Make sure we have enough allocated storage

            // Container size is increasing, we need to emplace the new elements
            const usize difference = newSize - m_Size;
            for (usize i = 0; i < difference; i++)
                new (static_cast<void*>(m_Data + m_Size + i)) T{newElementsValue};
        }

        m_Size = newSize;
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::Reserve(const usize newMinimumCapacity)
    {
        if (m_Capacity >= newMinimumCapacity)
            return;

        Reallocate(std::bit_ceil(newMinimumCapacity));
    }

    template <Concepts::DynamicContainerType T>
    usize List<T>::GetCapacity() const { return m_Capacity; }

    template <Concepts::DynamicContainerType T>
    void List<T>::Shrink()
    {
        if (m_Size == m_Capacity)
            return;

        Reallocate(m_Size);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::Clear()
    {
        DestroyElements(0, m_Size);
        m_Size = 0;
    }

    template <Concepts::DynamicContainerType T>
    bool List<T>::IsEmpty() const { return m_Size == 0; }

    template <Concepts::DynamicContainerType T>
    void List<T>::Remove(const T& value)
    {
        for (usize i = 0; i < m_Size; i++)
        {
            if (m_Data[i] != value)
                continue;

            RemoveAt(i);
            break;
        }
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveAt(usize index)
    {
        m_Data[index].~T();
        ShiftElements(-1, index + 1, m_Size--);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveAt(Iterator iterator)
    {
        CheckIteratorThrow(iterator);
        RemoveAt(iterator.GetIndex());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveFirst()
    {
        RemoveAt(0);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveLast()
    {
        RemoveAt(m_Size - 1);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveAll(const Predicate<T>& predicate)
    {
        for (usize i = 0; i < m_Size; i++)
        {
            if (predicate(*m_Data[i]))
                RemoveAt(i--);
        }
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveRange(const usize index, const usize count)
    {
        if (count == 0)
            return;

        if (index + count > m_Size)
            THROW(ArgumentException{"Invalid element count", "count"});

        if constexpr (!Meta::IsTriviallyDestructible<T>)
        {
            for (usize i = index; i < index + count; i++)
                m_Data[i].~T();
        }

        if (index + count != m_Size)
            ShiftElements(-static_cast<ptrdiff_t>(count), index + count, m_Size);

        m_Size -= count;
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveRange(const Iterator iterator, const usize count)
    {
        CheckIteratorThrow(iterator);

        return RemoveRange(iterator.GetIndex(), count);
    }

    template <Concepts::DynamicContainerType T>
    T List<T>::PopFront()
    {
        T result{First()};
        RemoveFirst();
        return result;
    }

    template <Concepts::DynamicContainerType T>
    T List<T>::PopBack()
    {
        T result{Last()};
        RemoveLast();
        return result;
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::At(const usize index) const
    {
        if (index >= m_Size)
            THROW(ThrowHelper::IndexOutOfRangeException("index"));
        return m_Data[index];
    }

    template <Concepts::DynamicContainerType T>
    T& List<T>::At(Iterator iterator) const
    {
        CheckIteratorThrow(iterator);
        return *iterator;
    }

    template <Concepts::DynamicContainerType T>
    usize List<T>::GetSize() const noexcept { return m_Size; }

    template <Concepts::DynamicContainerType T>
    T* List<T>::GetData() const noexcept { return m_Data; }

    template <Concepts::DynamicContainerType T>
    T& List<T>::operator[](const usize index) const noexcept
    {
#ifdef _DEBUG
        return At(index);
#else
        return m_Data[index]; // No bounds checking when in release mode
#endif
    }

    template <Concepts::DynamicContainerType T>
    List<T>::Iterator List<T>::begin() noexcept { return Iterator{m_Data, 0}; }

    template <Concepts::DynamicContainerType T>
    List<T>::Iterator List<T>::end() noexcept { return Iterator{m_Data, m_Size}; }

    template <Concepts::DynamicContainerType T>
    List<T>::ConstIterator List<T>::begin() const noexcept { return cbegin(); }

    template <Concepts::DynamicContainerType T>
    List<T>::ConstIterator List<T>::end() const noexcept { return cend(); }

    template <Concepts::DynamicContainerType T>
    List<T>::ConstIterator List<T>::cbegin() const noexcept { return ConstIterator{m_Data, 0}; }

    template <Concepts::DynamicContainerType T>
    List<T>::ConstIterator List<T>::cend() const noexcept { return ConstIterator{m_Data, m_Size}; }

    template <Concepts::DynamicContainerType T>
    void List<T>::Reallocate(const usize targetCapacity)
    {
        const usize targetCapacityBytes = targetCapacity * sizeof(T);  // NOLINT(bugprone-sizeof-expression)

        if constexpr (Meta::IsTriviallyMoveConstructible<T>)
        {
            m_Data = static_cast<T*>(std::realloc(static_cast<void*>(m_Data), targetCapacityBytes));
        }
        else
        {
            T* newData = static_cast<T*>(std::malloc(targetCapacityBytes));
            for (usize i = 0; i < m_Size; i++)
                new (newData + i) T{std::move(m_Data[i])};

            std::free(m_Data);
            m_Data = newData;
        }

        m_Capacity = targetCapacity;
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::IncreaseCapacity() { Reserve(std::max(m_Capacity * 2, 2ull)); }

    template <Concepts::DynamicContainerType T>
    void List<T>::IncreaseCapacityIfFull()
    {
        if (m_Size == m_Capacity)
            IncreaseCapacity();
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::DestroyElements(const usize first, const usize last)
    {
        const usize difference = last - first;
        for (usize i = 0; i < difference; i++)
            m_Data[first + i].~T();
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::ShiftElements(const ptrdiff_t amount, const usize first, const usize last)
    {
        if (amount == 0)
            return;

        T* source = m_Data + first;
        T* destination = source + amount;
        const usize amountToShift = last - first;

        if constexpr (Meta::IsTriviallyMoveConstructible<T>)
        {
            std::memmove(static_cast<void*>(destination), static_cast<void*>(source), amountToShift * sizeof(T));  // NOLINT(bugprone-sizeof-expression)
        }
        else
        {
            if (amount > 0)
            {
                for (auto i = static_cast<ptrdiff_t>(amountToShift - 1); i >= 0; i--)
                    new (destination + i) T{std::move(source[i])};
            }
            else // if (amount < 0)
            {
                for (usize i = 0; i < amountToShift; i++)
                    new (destination + i) T{std::move(source[i])};
            }
        }
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::CheckIteratorThrow(Iterator iterator)
    {
        if (CheckIterator(iterator))
            THROW(ThrowHelper::InvalidIteratorException());
    }
}
