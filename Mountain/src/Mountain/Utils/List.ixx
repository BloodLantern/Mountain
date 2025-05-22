export module Mountain:Utils_List;

import "Mountain/Core.hpp";

import std;
export import :Core;

/// @file List.ixx
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
        void PopBack();

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

        /// @brief Allows iteration over the list with a lambda.
        ///
        /// The lambda returns @c void and has a pointer to the current element as a parameter.
        ///
        /// @param lambda Function lambda
        void Iterate(const std::function<void(T*)>& lambda);

        /// @brief Allows iteration over the list with a lambda.
        ///
        /// The lambda returns @c void and has a pointer to the current element as a parameter.
        ///
        /// @param lambda Function lambda
        void Iterate(const std::function<void(const T*)>& lambda) const;

        /// @brief Allows iteration over the list with a lambda.
        ///
        /// The lambda returns @c void and has a reference to the current element as a parameter.
        ///
        /// @param lambda Function lambda
        void ForEach(const std::function<void(T&)>& lambda);

        /// @brief Allows iteration over the list with a lambda.
        ///
        /// The lambda returns @c void and has a reference to the current element as a parameter.
        ///
        /// @param lambda Function lambda
        void ForEach(const std::function<void(const T&)>& lambda) const;

        /// @brief Checks if an element exists that fulfills the requirements provided in a lam.bda
        ///
        /// The lambda returns bool_t, and has a pointer to the current element as a parameter.
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

// Start of List.inl

// ReSharper disable CppClangTidyCppcoreguidelinesRvalueReferenceParamNotMoved
// ReSharper disable CppClangTidyCppcoreguidelinesMissingStdForward

namespace Mountain
{
    template <typename T>
    List<T>::List(const size_t size)
        : m_Vector(size)
    {
    }

    template <typename T>
    List<T>::List(const size_t size, const T& defaultValue)
        : m_Vector(size, defaultValue)
    {
    }

    template <typename T>
    List<T>::List(const size_t size, const T* const values)
        : m_Vector(size)
    {
        for (size_t i = 0; i < size; i++)
            m_Vector[i] = values[i];
    }

    template <typename T>
    template <size_t Size>
    List<T>::List(const std::array<T, Size>& array)
        : m_Vector(Size)
    {
        for (size_t i = 0; i < Size; i++)
            m_Vector[i] = array[i];
    }

    template <typename T>
    List<T>::List(const std::vector<T>& vector)
        : m_Vector(vector.size())
    {
        for (size_t i = 0; i < vector.size(); i++)
            m_Vector[i] = vector[i];
    }

    template <typename T>
    List<T>::List(std::vector<T>&& vector)
        : m_Vector(std::move(vector))
    {
    }

    template <typename T>
    List<T>::List(Iterator b, Iterator e)
        : m_Vector(b, e)
    {
    }

    template <typename T>
    List<T>::List(const std::initializer_list<T>& values)
        : m_Vector(values)
    {
    }

    template <typename T>
    void List<T>::Resize(const size_t size)
    {
        m_Vector.resize(size);
    }

    template <typename T>
    void List<T>::Clear()
    {
        m_Vector.clear();
    }

    template <typename T>
    bool_t List<T>::Empty() const
    {
        return GetSize() == 0;
    }

    template <typename T>
    T& List<T>::Add()
    {
        return m_Vector.emplace_back();
    }

    template <typename T>
    void List<T>::Add(const T& element)
    {
        m_Vector.emplace_back(element);
    }

    template <typename T>
    void List<T>::Add(T&& element)
    {
        m_Vector.emplace_back(std::forward<T>(element));
    }

    template <typename T>
    void List<T>::AddRange(const T* const data, const size_t count)
    {
        for (size_t i = 0; i < count; i++)
            m_Vector.emplace_back(data[i]);
    }

    template <typename T>
    void List<T>::AddRange(const std::initializer_list<T>& values)
    {
        const size_t size = values.size();
        const T* const begin = values.begin();

        for (size_t i = 0; i < size; i++)
            m_Vector.emplace_back(begin[i]);
    }

    template <typename T>
    void List<T>::Fill(const T& value)
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
            m_Vector[i] = value;
    }

    template <typename T>
    void List<T>::Fill(T&& value)
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
            m_Vector[i] = value;
    }

    template <typename T>
    template <class... Args>
    void List<T>::Emplace(Args&&... args)
    {
        m_Vector.emplace_back(std::forward<Args>(args)...);
    }

    template <typename T>
    void List<T>::PopBack()
    {
        m_Vector.pop_back();
    }

    template <typename T>
    void List<T>::Insert(size_t index)
    {
        m_Vector.insert(m_Vector.begin() + index, T());
    }

    template <typename T>
    void List<T>::Insert(const T& element, const size_t index)
    {
        m_Vector.insert(m_Vector.begin() + index, element);
    }

    template <typename T>
    void List<T>::Insert(T&& element, const size_t index)
    {
        m_Vector.insert(m_Vector.begin() + index, std::forward<T>(element));
    }

    template <typename T>
    void List<T>::Remove(const T& element)
    {
        Iterator position = std::find(m_Vector.begin(), m_Vector.end(), element);

        if (position != m_Vector.end())
            m_Vector.erase(position);
    }

    template <typename T>
    void List<T>::RemoveAt(const size_t index)
    {
        m_Vector.erase(m_Vector.begin() + index);
    }

    template <typename T>
    void List<T>::RemoveAt(const ConstIterator iterator)
    {
        m_Vector.erase(iterator);
    }

    template <typename T>
    void List<T>::RemoveRange(const size_t start, const size_t end)
    {
        m_Vector.erase(m_Vector.begin() + start, m_Vector.begin() + end);
    }

    template <typename T>
    bool_t List<T>::Contains(const T& element) const
    {
        return std::ranges::find(m_Vector, element) != m_Vector.end();
    }

    template <typename T>
    void List<T>::Iterate(const std::function<void(T*)>& lambda)
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
            lambda(&m_Vector[i]);
    }

    template <typename T>
    void List<T>::Iterate(const std::function<void(const T*)>& lambda) const
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
            lambda(&m_Vector[i]);
    }

    template <typename T>
    void List<T>::ForEach(const std::function<void(T&)>& lambda)
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
            lambda(m_Vector[i]);
    }

    template <typename T>
    void List<T>::ForEach(const std::function<void(const T&)>& lambda) const
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
            lambda(m_Vector[i]);
    }

    template <typename T>
    bool_t List<T>::Exists(const std::function<bool_t(const T*)>& lambda) const
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            if (lambda(&m_Vector[i]))
                return true;
        }

        return false;
    }

    template <typename T>
    T* List<T>::Find(const std::function<bool_t(const T*)>& lambda)
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            if (lambda(&m_Vector[i]))
                return &m_Vector[i];
        }

        return nullptr;
    }

    template <typename T>
    const T* List<T>::Find(const std::function<bool_t(const T*)>& lambda) const
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            if (lambda(&m_Vector[i]))
                return &m_Vector[i];
        }

        return nullptr;
    }

    template <typename T>
    List<T*> List<T>::FindAll(const std::function<bool_t(const T*)>& lambda)
    {
        List<T*> result;

        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            if (lambda(&m_Vector[i]))
                result.Add(&m_Vector[i]);
        }

        return result;
    }

    template <typename T>
    List<const T*> List<T>::FindAll(const std::function<bool_t(const T*)>& lambda) const
    {
        List<const T*> result;

        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            if (lambda(&m_Vector[i]))
                result.Add(&m_Vector[i]);
        }

        return result;
    }

    template <typename T>
    size_t List<T>::FindPosition(const std::function<bool_t(const T*)>& lambda) const
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            if (lambda(&m_Vector[i]))
                return i;
        }

        return std::numeric_limits<size_t>::max();
    }

    template <typename T>
    T* List<T>::Find(const std::function<bool_t(const T*, size_t)>& lambda)
    {
        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            if (lambda(&m_Vector[i], i))
                return &m_Vector[i];
        }

        return nullptr;
    }

    template <typename T>
    void List<T>::Sort(std::function<bool_t(const T& left, const T& right)> predicate) { std::ranges::sort(m_Vector, predicate); }

    template <typename T>
    T* List<T>::GetData() { return m_Vector.data(); }

    template <typename T>
    const T* List<T>::GetData() const { return m_Vector.data(); }

    template <typename T>
    size_t List<T>::GetSize() const { return m_Vector.size(); }

    template <typename T>
    size_t List<T>::GetCapacity() const { return m_Vector.capacity(); }

    template <typename T>
    typename std::vector<T>::reference List<T>::operator[](const size_t index) { return m_Vector.at(index); }

    template <typename T>
    typename std::vector<T>::const_reference List<T>::operator[](const size_t index) const { return m_Vector.at(index); }

    template <typename T>
    const T& List<T>::Front() const { return m_Vector.front(); }

    template <typename T>
    T& List<T>::Front() { return m_Vector.front(); }

    template <typename T>
    const T& List<T>::Back() const { return m_Vector.back(); }

    template <typename T>
    T& List<T>::Back() { return m_Vector.back(); }

    template <typename T>
    typename List<T>::Iterator List<T>::Begin() { return m_Vector.begin(); }

    template <typename T>
    typename List<T>::Iterator List<T>::End() { return m_Vector.end(); }

    template <typename T>
    typename List<T>::ConstIterator List<T>::CBegin() const { return m_Vector.cbegin(); }

    template <typename T>
    typename List<T>::ConstIterator List<T>::CEnd() const { return m_Vector.cend(); }

    template <typename T>
    typename List<T>::ReverseIterator List<T>::RBegin() { return m_Vector.rbegin(); }

    template <typename T>
    typename List<T>::ReverseIterator List<T>::REnd() { return m_Vector.rend(); }

    template <typename T>
    typename List<T>::ConstReverseIterator List<T>::CrBegin() const { return m_Vector.crbegin(); }

    template <typename T>
    typename List<T>::ConstReverseIterator List<T>::CrEnd() const { return m_Vector.crend(); }

    template <typename T>
    typename List<T>::Iterator List<T>::begin() { return Begin(); }

    template <typename T>
    typename List<T>::ConstIterator List<T>::begin() const { return CBegin(); }

    template <typename T>
    typename List<T>::Iterator List<T>::end() { return End(); }

    template <typename T>
    typename List<T>::ConstIterator List<T>::end() const { return CEnd(); }
}
