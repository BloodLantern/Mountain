#pragma once

#include <functional>
#include <vector>

#include "Mountain/core.hpp"

/// @file list.hpp
/// @brief Defines the Mountain::List class.

namespace Mountain
{
    /// @brief A dynamic array implementation. Wrapper around the @c std::vector class.
    ///
    /// ### Reasons
    /// A more user-friendly list than @c std::vector, based on how @c %List is done in C#
    /// The internal structure and workings are similar to how std::vector works, it uses a capacity that grows exponentially based on powers of 2
    ///
    /// @tparam T Type stored
    ///
    /// @see <a href="https://en.cppreference.com/w/cpp/container/vector">std::vector</a>
    /// @see <a href="https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0">C# List</a>
    template <typename T>
    class List
    {
    public:
        using Iterator = typename std::vector<T>::iterator;
        using ConstIterator = typename std::vector<T>::const_iterator;
        using ReverseIterator = typename std::vector<T>::reverse_iterator;
        using ConstReverseIterator = typename std::vector<T>::const_reverse_iterator;

        /// @brief The type of the List<T>, refers to T
        using Type = T;

        /// @brief Creates an empty list with a capacity of 0
        List() = default;

        /// @brief Creates a list with the specified size, and fills it with the default value of T
        ///
        /// @param size List size
        explicit List(size_t size);

        /// @brief Creates a list with the specified size, and fills it with the provided value
        ///
        /// @param size List size
        /// @param defaultValue Default value
        explicit List(size_t size, const T& defaultValue);

        /// @brief Creates a list with the specified size, and fills it with the provided values
        ///
        /// @param size List size
        /// @param values Provided values
        explicit List(size_t size, const T* values);

        /// @brief Creates a list with the specified array
        ///
        /// @tparam Size The @p array size
        /// @param array Array
        template <size_t Size>
        explicit List(const std::array<T, Size>& array);

        /// @brief Creates a list with the specified vector. This creates a copy of the given vector.
        ///
        /// @param vector Vector
        explicit List(const std::vector<T>& vector);

        /// @brief Creates a list with the specified vector.
        ///
        /// @param vector Vector
        explicit List(std::vector<T>&& vector);

        /// @brief Creates a list with the specified vector.
        explicit List(Iterator b, Iterator e);

        /// @brief Creates a list with the specified values
        ///
        /// @param values Values
        List(const std::initializer_list<T>& values);

        /// @brief Destroys the list
        ~List() = default;

        DEFAULT_COPY_MOVE_OPERATIONS(List)

        /// @brief Resizes a specified amount of elements in the list
        ///
        /// @param size New size
        void Resize(size_t size);

        /// @brief Clears the list
        void Clear();

        /// @brief Returns whether the list is empty. This is equivalent to doing @c GetSize() == @c 0
        [[nodiscard]]
        bool_t Empty() const;

        /// @brief Adds a default element to the end of the list (calls the default constructor of T)
        T& Add();

        /// @brief Adds a specified element to the end of the list
        ///
        /// @param element Element
        void Add(const T& element);

        /// @brief Adds a specified element to the end of the list
        ///
        /// @param element Element
        void Add(T&& element);

        /// @brief Adds a range of elements to the end of the list
        ///
        /// @param data Data
        /// @param count Number of elements (array size of data)
        void AddRange(const T* data, size_t count);

        /// @brief Adds a range of elements to the end of the list
        ///
        /// @param values Values
        void AddRange(const std::initializer_list<T>& values);

        /// @brief Fills the list with a specified value
        ///
        /// @param value Value
        void Fill(const T& value);

        /// @brief Fills the list with a specified value
        ///
        /// @param value Value
        void Fill(T&& value);

        /// @brief Constructs a new element and adds it to the end of the list
        ///
        /// @tparam Args Constructor element types
        /// @param args Arguments
        template <class... Args>
        void Emplace(Args&&... args);

        /// @brief Removes the last element of the list
        void Pop();

        /**
         * @brief Inserts an element at the given position using the default constructor
         *
         * @param index Index
         */
        void Insert(size_t index);

        /// @brief Inserts an element in the list at the given position
        ///
        /// @param element Element
        /// @param index Index
        void Insert(const T& element, size_t index);

        /// @brief Inserts an element in the list at the given position
        ///
        /// @param element Element
        /// @param index Index
        void Insert(T&& element, size_t index);

        /// @brief Removes an element from the list (only removes the first occurence it finds)
        ///
        /// @param element Element
        void Remove(const T& element);

        /// @brief Removes an element from the list at a given index
        ///
        /// @param index Index
        void RemoveAt(size_t index);

        /// @brief Removes an element from the list at a given iterator
        ///
        /// @param iterator Iterator
        void RemoveAt(ConstIterator iterator);

        /// @brief Removes a range of elements from the list
        ///
        /// @param start Starting index
        /// @param end End index
        void RemoveRange(size_t start, size_t end);

        /// @brief Checks if the list contains a specified element
        ///
        /// @param element Element
        /// @return Element exists
        [[nodiscard]]
        bool_t Contains(const T& element) const;

        /// @brief Allows iteration over the list with a lambda
        ///
        /// <p>The lambda returns void, and has a pointer to the current element as a parameters</p>
        ///
        /// @param lambda Function lambda
        void Iterate(const std::function<void(T*)>& lambda);

        /// @brief Allows iteration over the list with a lambda
        ///
        /// <p>The lambda returns void, and has a pointer to the current element as a parameters</p>
        ///
        /// @param lambda Function lambda
        void Iterate(const std::function<void(const T*)>& lambda) const;

        /// @brief Checks if an element exists that fulfills the requirements provided in a lambda
        ///
        /// <p>The lambda returns bool_t, and has a pointer to the current element as a parameters</p>
        ///
        /// @param lambda Function lambda
        /// @return Element exists
        [[nodiscard]]
        bool_t Exists(const std::function<bool_t(const T*)>& lambda) const;

        /// @brief Tries to find an element that fulfills the requirements provided in a lambda
        ///
        /// <p>The lambda returns bool_t, and has a pointer to the current element as a parameter</p>
        ///
        /// @param lambda Function lambda
        /// @return Pointer to element
        [[nodiscard]]
        T* Find(const std::function<bool_t(const T*)>& lambda);

        /// @brief Tries to find an element that fulfills the requirements provided in a lambda
        ///
        /// <p>The lambda returns bool_t, and has a pointer to the current element as a parameter</p>
        ///
        /// @param lambda Function lambda
        /// @return Pointer to element
        [[nodiscard]]
        const T* Find(const std::function<bool_t(const T*)>& lambda) const;

        /// @brief Tries to find all elements that fulfill the requirements provided in a lambda
        ///
        /// <p>The lambda returns bool_t, and has a pointer to the current element as a parameter</p>
        ///
        /// @param lambda Function lambda
        /// @return Pointers to elements
        [[nodiscard]]
        List<T*> FindAll(const std::function<bool_t(const T*)>& lambda);

        /// @brief Tries to find all elements that fulfill the requirements provided in a lambda
        ///
        /// <p>The lambda returns bool_t, and has a pointer to the current element as a parameter</p>
        ///
        /// @param lambda Function lambda
        /// @return Pointers to elements
        [[nodiscard]]
        List<const T*> FindAll(const std::function<bool_t(const T*)>& lambda) const;

        /// @brief Tries to find an element that fulfills the requirements provided in a lambda
        ///
        /// @param lambda Function lambda
        /// @return Index of the element in the list (size_t max if not found)
        [[nodiscard]]
        size_t FindPosition(const std::function<bool_t(const T*)>& lambda) const;

        /// <p>The lambda returns bool_t, and has a pointer to the current element and its index as parameters</p>
        ///
        /// @param lambda Function lambda
        /// @return Pointer to element
        [[nodiscard]]
        T* Find(const std::function<bool_t(const T*, size_t)>& lambda);

        void Sort(std::function<bool_t(const T& left, const T& right)> predicate = std::less());

        /// @brief Gets the underlying pointer to the list
        ///
        /// @return Pointer
        [[nodiscard]]
        T* GetData();

        /// @brief Gets the underlying pointer to the list
        ///
        /// @return Pointer
        [[nodiscard]]
        const T* GetData() const;

        /// @brief Gets the size of the list
        ///
        /// @return Size
        [[nodiscard]]
        size_t GetSize() const;

        /// @brief Gets the capacity of the list
        ///
        /// @return Capacity
        [[nodiscard]]
        size_t GetCapacity() const;

        /// @brief Gets an element of the list at a specified index
        ///
        /// @param index Index
        /// @return Element
        ///
        /// @throw std::out_of_range If index >= list size
        [[nodiscard]]
        typename std::vector<T>::reference operator[](size_t index);

        /// @brief Gets an element of the list at a specified index
        ///
        /// @param index Index
        /// @return Element
        ///
        /// @throw std::out_of_range If index >= list size
        [[nodiscard]]
        typename std::vector<T>::const_reference operator[](size_t index) const;

        [[nodiscard]]
        const T& Front() const;

        [[nodiscard]]
        T& Front();

        [[nodiscard]]
        const T& Back() const;

        [[nodiscard]]
        T& Back();

        [[nodiscard]]
        Iterator Begin();

        [[nodiscard]]
        Iterator End();

        [[nodiscard]]
        ConstIterator CBegin() const;

        [[nodiscard]]
        ConstIterator CEnd() const;

        [[nodiscard]]
        ReverseIterator RBegin();

        [[nodiscard]]
        ReverseIterator REnd();

        [[nodiscard]]
        ConstReverseIterator CrBegin() const;

        [[nodiscard]]
        ConstReverseIterator CrEnd() const;

        /// @private
        /// Necessary when using range-for loops
        [[nodiscard]]
        Iterator begin();

        /// @private
        /// Necessary when using range-for loops with a @c const list
        [[nodiscard]]
        ConstIterator begin() const;

        /// @private
        /// Necessary when using range-for loops
        [[nodiscard]]
        Iterator end();

        /// @private
        /// Necessary when using range-for loops with a @c const list
        [[nodiscard]]
        ConstIterator end() const;

    private:
        std::vector<T> m_Vector;
    };
}

#include "Mountain/utils/list.inl"
