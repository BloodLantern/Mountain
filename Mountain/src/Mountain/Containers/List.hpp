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
    template <Concepts::ContainerType T, size_t Size>
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

        explicit List(size_t initialSize) noexcept;

        /// @brief Constructs a List from the specified size, and fills it with the provided value.
        /// @param initialSize List size
        /// @param defaultValue Default value
        List(size_t initialSize, const T& defaultValue);

        /// @brief Constructs a List from the specified size, and fills it with the provided values.
        /// @param initialSize List size
        /// @param values Provided values
        List(size_t initialSize, const T* values);

        /// @brief Constructs a List from the specified array. This creates a copy of the given array contents.
        /// @tparam Size The @p array size
        template <size_t Size>
        explicit List(const std::array<T, Size>& array);

        /// @brief Constructs a List from the specified array. This creates a copy of the given array contents.
        /// @tparam Size The @p array size
        template <size_t Size>
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
        [[nodiscard]]
        bool_t CheckIterator(Iterator iterator) const;

        T& Add(T&& element);

        T& Add(const T& element);

        /// @brief Adds a range of elements to the end of the List.
        template <typename = Meta::EnableIf<Meta::IsTriviallyCopyable<T>>>
        void AddRange(const T* data, size_t count);

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
        template <size_t Size>
        void AddRange(const std::array<T, Size>& array);

        /// @brief Adds a range of elements to the end of the List. This creates a copy of the given array contents.
        /// @tparam Size The @p array size
        template <size_t Size>
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
        T& Emplace(size_t index, Args&&... args);

        template <typename... Args>
        T& Emplace(Iterator iterator, Args&&... args);

        T& Insert(size_t index, T&& element);

        T& Insert(size_t index, const T& element);

        T& Insert(Iterator iterator, T&& element);

        T& Insert(Iterator iterator, const T& element);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(size_t index, const T* data, size_t count);

        /// @brief Inserts a range of elements at the given position.
        template <Concepts::Iterator InputIterator>
        void InsertRange(size_t index, InputIterator first, InputIterator last);

        /// @brief Inserts a range of elements at the given position.
        template <Concepts::Enumerable EnumerableT>
        void InsertRange(size_t index, EnumerableT enumerable);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(size_t index, const std::initializer_list<T>& values);

        /// @brief Inserts a range of elements at the given position.
        /// @tparam Size The @p array size
        template <size_t Size>
        void InsertRange(size_t index, const std::array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        /// @tparam Size The @p array size
        template <size_t Size>
        void InsertRange(size_t index, const Array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(size_t index, const std::vector<T>& vector);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(Iterator iterator, const T* data, size_t count);

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
        template <size_t Size>
        void InsertRange(Iterator iterator, const std::array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        /// @tparam Size The @p array size
        template <size_t Size>
        void InsertRange(Iterator iterator, const Array<T, Size>& array);

        /// @brief Inserts a range of elements at the given position.
        void InsertRange(Iterator iterator, const std::vector<T>& vector);

        void Resize(size_t newSize);

        void Resize(size_t newSize, const T& newElementsValue);

        void Reserve(size_t newMinimumCapacity);

        [[nodiscard]]
        size_t GetCapacity() const;

        void Shrink();

        void Clear();

        [[nodiscard]]
        bool_t IsEmpty() const;

        void Remove(const T& value);

        void RemoveAt(size_t index);

        void RemoveAt(Iterator iterator);

        void RemoveFirst();

        void RemoveLast();

        /// @brief Get the element at the given index with bounds checking.
        [[nodiscard]]
        T& At(size_t index) const;

        /// @brief Get the element at the given iterator with bounds checking.
        [[nodiscard]]
        T& At(Iterator iterator) const;

        /// @brief Get the size of the list.
        [[nodiscard]]
        size_t GetSize() const noexcept;

        [[nodiscard]]
        T* GetData() const noexcept;

        /// @brief Get the element at the given index without bounds checking.
        [[nodiscard]]
        T& operator[](size_t index) const noexcept;

        [[nodiscard]]
        Iterator begin() noexcept;

        [[nodiscard]]
        Iterator end() noexcept;

        [[nodiscard]]
        ConstIterator begin() const noexcept;

        [[nodiscard]]
        ConstIterator end() const noexcept;

        [[nodiscard]]
        ConstIterator cbegin() const noexcept;

        [[nodiscard]]
        ConstIterator cend() const noexcept;

        ENUMERABLE_EXTENSIONS_IMPLEMENTATION

        template <typename U, typename = Meta::EnableIf<Meta::IsConvertibleTo<EnumeratedType, U>>>
        [[nodiscard]]
        List<U> Cast() const
        {
            List<U> result;
            result.Reserve(m_Size);

            for (const EnumeratedType& element : *this)
                result.Add(static_cast<U>(element));

            return result;
        }

        template <Concepts::Invocable<EnumeratedType> ProjectionFunctionT, typename U = decltype(ProjectionFunctionT{}(EnumeratedType{}))>
        [[nodiscard]]
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
        size_t m_Size = 0;
        size_t m_Capacity = 0;

        void Reallocate(size_t targetCapacity);
        void IncreaseCapacity();
        void IncreaseCapacityIfFull();
        void DestroyElements(size_t first, size_t last);
        /// @brief Shift all elements in the range [@p first, @p last) by @p amount elements.
        void ShiftElements(ptrdiff_t amount, size_t first, size_t last);
        void CheckIteratorThrow(Iterator iterator);
    };

    CHECK_REQUIREMENT(Requirements::MountainEnumerableContainer, List<Requirements::DefaultType>);
}

// Start of List.inl

#include "Mountain/Containers/Array.hpp"

namespace Mountain
{
    template <Concepts::DynamicContainerType T>
    template <Concepts::ConvertibleTo<T> ... U>
    List<T>::List(U&&... values) noexcept : List{{std::forward<U>(values)...}} {}

    template <Concepts::DynamicContainerType T>
    List<T>::List(std::initializer_list<T> initializer) noexcept
    {
        Reserve(initializer.size());

        for (int i = 0; i < initializer.size(); i++)
            m_Data[i] = initializer.begin()[i];

        m_Size = initializer.size();
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(const size_t initialSize) noexcept
    {
        Resize(initialSize);
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(const size_t initialSize, const T& defaultValue)
    {
        Resize(initialSize, defaultValue);
    }

    template <Concepts::DynamicContainerType T>
    List<T>::List(const size_t initialSize, const T* values)
    {
        Reserve(initialSize);
        m_Size = initialSize;
        for (size_t i = 0; i < initialSize; i++)
            m_Data[i] = values[i];
    }

    template <Concepts::DynamicContainerType T>
    template <size_t Size>
    List<T>::List(const std::array<T, Size>& array) : List(array.begin(), array.end()) {}

    template <Concepts::DynamicContainerType T>
    template <size_t Size>
    List<T>::List(const Array<T, Size>& array) : List(array.GetBeginIterator(), array.GetEndIterator()) {}

    template <Concepts::DynamicContainerType T>
    List<T>::List(const std::vector<T>& vector) : List(vector.begin(), vector.end()) {}

    template <Concepts::DynamicContainerType T>
    template <Concepts::Iterator InputIterator>
    List<T>::List(InputIterator first, InputIterator last)
    {
        const size_t newSize = last - first;
        Reserve(newSize);
        m_Size = newSize;
        for (InputIterator it = first; it != last; it++)
        {
            const size_t index = it - first;
            m_Data[index] = *it;
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
        for (size_t i = 0; i < m_Size; i++)
            m_Data[i] = other.m_Data[i];

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
    bool_t List<T>::CheckIterator(Iterator iterator) const
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
    template <typename>
    void List<T>::AddRange(const T* data, const size_t count)
    {
        Reserve(m_Size + count);

        if constexpr (Meta::IsTriviallyCopyConstructible<T>)
        {
            std::memcpy(static_cast<void*>(m_Data + m_Size), static_cast<void*>(data), count * sizeof(T));  // NOLINT(bugprone-sizeof-expression)
        }
        else
        {
            for (size_t i = 0; i < count; i++)
                new (m_Size + i) T{data[i]};
        }

        m_Size += count;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Iterator InputIterator>
    void List<T>::AddRange(InputIterator first, InputIterator last)
    {
        static_assert(Meta::IsSame<Meta::IteratorType<InputIterator>, T>, "List::AddRange() needs the type of the iterator to be the same as the List");

        const size_t additionalSize = last - first;

        Reserve(m_Size + additionalSize);

        for (InputIterator it = first; it != last; it++)
        {
            const size_t index = it - first;
            new (static_cast<void*>(m_Data + m_Size + index)) T{*it};
        }

        m_Size += additionalSize;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Enumerable EnumerableT>
    void List<T>::AddRange(const EnumerableT& enumerable)
    {
        static_assert(Meta::IsSame<Meta::EnumerableType<EnumerableT>, T>, "List::AddRange() needs the type of the enumerable to be the same as the List");

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
    template <size_t Size>
    void List<T>::AddRange(const std::array<T, Size>& array)
    {
        AddRange(array.data(), Size);
    }

    template <Concepts::DynamicContainerType T>
    template <size_t Size>
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
        AddRange(enumerable.GetBeginIterator(), enumerable.GetEndIterator());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::Fill(const T& value)
    {
        for (size_t i = 0; i < m_Size; i++)
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
    T& List<T>::Emplace(size_t index, Args&&... args)
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
    T& List<T>::Insert(const size_t index, T&& element)
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
    T& List<T>::Insert(const size_t index, const T& element)
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
    void List<T>::InsertRange(const size_t index, const T* data, const size_t count)
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
            std::memcpy(static_cast<void*>(m_Data + index), static_cast<void*>(data), count * sizeof(T));  // NOLINT(bugprone-sizeof-expression)
        }
        else
        {
            for (size_t i = 0; i < count; i++)
                new (index + i) T{data[i]};
        }

        m_Size += count;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Iterator InputIterator>
    void List<T>::InsertRange(const size_t index, InputIterator first, InputIterator last)
    {
        static_assert(Meta::IsSame<Meta::IteratorType<InputIterator>, T>, "List::InsertRange() needs the type of the iterator to be the same as the List");

        const size_t additionalSize = last - first;

        Reserve(m_Size + additionalSize);
        ShiftElements(additionalSize, index, m_Size);

        for (InputIterator it = first; it != last; it++)
        {
            const size_t i = it - first;
            new (static_cast<void*>(m_Data + index + i)) T{*it};
        }

        m_Size += additionalSize;
    }

    template <Concepts::DynamicContainerType T>
    template <Concepts::Enumerable EnumerableT>
    void List<T>::InsertRange(const size_t index, EnumerableT enumerable)
    {
        static_assert(Meta::IsSame<Meta::EnumerableType<EnumerableT>, T>, "List::InsertRange() needs the type of the enumerable to be the same as the List");

        return InsertRange(index, enumerable.begin(), enumerable.end());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const size_t index, const std::initializer_list<T>& values)
    {
        return InsertRange(index, values.begin(), values.size());
    }

    template <Concepts::DynamicContainerType T>
    template <size_t Size>
    void List<T>::InsertRange(const size_t index, const std::array<T, Size>& array)
    {
        return InsertRange(index, array.data(), Size);
    }

    template <Concepts::DynamicContainerType T>
    template <size_t Size>
    void List<T>::InsertRange(const size_t index, const Array<T, Size>& array)
    {
        return InsertRange(index, array.GetData(), Size);
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const size_t index, const std::vector<T>& vector)
    {
        return InsertRange(index, vector.data(), vector.size());
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::InsertRange(const Iterator iterator, const T* data, size_t count)
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
    template <size_t Size>
    void List<T>::InsertRange(const Iterator iterator, const std::array<T, Size>& array)
    {
        return InsertRange(iterator, array.data(), Size);
    }

    template <Concepts::DynamicContainerType T>
    template <size_t Size>
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
    void List<T>::Resize(const size_t newSize) { Resize(newSize, {}); }

    template <Concepts::DynamicContainerType T>
    void List<T>::Resize(const size_t newSize, const T& newElementsValue)
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
            const size_t difference = newSize - m_Size;
            for (size_t i = 0; i < difference; i++)
                new (static_cast<void*>(m_Data + m_Size + i)) T{newElementsValue};
        }

        m_Size = newSize;
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::Reserve(const size_t newMinimumCapacity)
    {
        if (m_Capacity >= newMinimumCapacity)
            return;

        Reallocate(std::bit_ceil(newMinimumCapacity));
    }

    template <Concepts::DynamicContainerType T>
    size_t List<T>::GetCapacity() const { return m_Capacity; }

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
    bool_t List<T>::IsEmpty() const { return m_Size == 0; }

    template <Concepts::DynamicContainerType T>
    void List<T>::Remove(const T& value)
    {
        for (size_t i = 0; i < m_Size; i++)
        {
            if (m_Data[i] != value)
                continue;

            RemoveAt(i);
            break;
        }
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::RemoveAt(size_t index)
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
    T& List<T>::At(const size_t index) const
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
    size_t List<T>::GetSize() const noexcept { return m_Size; }

    template <Concepts::DynamicContainerType T>
    T* List<T>::GetData() const noexcept { return m_Data; }

    template <Concepts::DynamicContainerType T>
    T& List<T>::operator[](const size_t index) const noexcept { return m_Data[index]; }

    template <Concepts::DynamicContainerType T>
    typename List<T>::Iterator List<T>::begin() noexcept { return Iterator{m_Data, 0}; }

    template <Concepts::DynamicContainerType T>
    typename List<T>::Iterator List<T>::end() noexcept { return Iterator{m_Data, m_Size}; }

    template <Concepts::DynamicContainerType T>
    typename List<T>::ConstIterator List<T>::begin() const noexcept { return cbegin(); }

    template <Concepts::DynamicContainerType T>
    typename List<T>::ConstIterator List<T>::end() const noexcept { return cend(); }

    template <Concepts::DynamicContainerType T>
    typename List<T>::ConstIterator List<T>::cbegin() const noexcept { return ConstIterator{m_Data, 0}; }

    template <Concepts::DynamicContainerType T>
    typename List<T>::ConstIterator List<T>::cend() const noexcept { return ConstIterator{m_Data, m_Size}; }

    template <Concepts::DynamicContainerType T>
    void List<T>::Reallocate(const size_t targetCapacity)
    {
        const size_t targetCapacityBytes = targetCapacity * sizeof(T);  // NOLINT(bugprone-sizeof-expression)

        if constexpr (Meta::IsTriviallyMoveConstructible<T>)
        {
            m_Data = static_cast<T*>(std::realloc(static_cast<void*>(m_Data), targetCapacityBytes));
        }
        else
        {
            T* newData = static_cast<T*>(std::malloc(targetCapacityBytes));
            for (size_t i = 0; i < m_Size; i++)
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
    void List<T>::DestroyElements(const size_t first, const size_t last)
    {
        const size_t difference = last - first;
        for (size_t i = 0; i < difference; i++)
            m_Data[first + i].~T();
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::ShiftElements(const ptrdiff_t amount, const size_t first, const size_t last)
    {
        T* source = m_Data + first;
        T* destination = source + amount;
        const size_t amountToShift = last - first;

        if constexpr (Meta::IsTriviallyMoveConstructible<T>)
        {
            std::memmove(static_cast<void*>(destination), static_cast<void*>(source), amountToShift * sizeof(T));  // NOLINT(bugprone-sizeof-expression)
        }
        else
        {
            for (size_t i = 0; i < amountToShift; i++)
                new (destination + i) T{std::move(source[i])};
        }
    }

    template <Concepts::DynamicContainerType T>
    void List<T>::CheckIteratorThrow(Iterator iterator)
    {
        if (CheckIterator(iterator))
            THROW(ThrowHelper::InvalidIteratorException());
    }
}
