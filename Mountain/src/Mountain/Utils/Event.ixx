export module Mountain:Utils_Event;

import std;
import :Utils;
export import :Utils_List;

/// @file Event.ixx
/// @brief Defines the Event class.

export namespace Mountain
{
    /// @brief Encapsulates a delegate system similar to its C# implementation
    ///
    /// It works by having an underlying list of functions that always return @c void and have the provided types as arguments
    /// The @c += and @c -= operators can be used to respectively add and remove events to the list
    ///
    /// Event variable names should always start with 'on', for example: onUpdate, onReload, onCollision, etc...
    ///
    /// @tparam Args Event function arguments
    ///
    /// @see <a href="https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/keywords/event">C# events</a>
    template <typename... Args>
    class Event
    {
    public:
        /// @brief Signature of the event function
        using FunctionT = void(Args...);
        using StdFunctionT = std::function<FunctionT>;

        /// @brief Invokes the currently registered events with the provided parameters
        /// @param args Parameters
        void Invoke(Args... args) const;

        /// @brief Clears the event list
        void Clear();

        /// @brief Invokes the currently registered events with the provided parameters. Effectively the same as calling @c Invoke.
        void operator()(Args... args) const;

        /// @brief Adds a function to the event list
        /// @param func Function
        /// @return This
        Event& operator+=(StdFunctionT func);

        /// @brief Removes a function from the event list
        /// @param func Function
        /// @return This
        Event& operator-=(const StdFunctionT& func);

    private:
        List<StdFunctionT> m_Functions;
    };
}

// Start of Event.inl

namespace Mountain
{
    template <typename... Args>
    void Event<Args...>::Invoke(Args... args) const
    {
        m_Functions.Iterate([&args...](const StdFunctionT* f) -> void
        {
            (*f)(std::forward<Args>(args)...);
        });
    }

    template <typename... Args>
    void Event<Args...>::operator()(Args... args) const { Invoke(args...); }

    template <typename... Args>
    void Event<Args...>::Clear()
    {
        m_Functions.Clear();
    }

    template <typename... Args>
    Event<Args...>& Event<Args...>::operator+=(StdFunctionT func)
    {
        m_Functions.Add(std::forward<StdFunctionT>(func));

        return *this;
    }

    template <typename ... Args>
    Event<Args...>& Event<Args...>::operator-=(const StdFunctionT& func)
    {
        for (size_t i = 0; i < m_Functions.GetSize(); i++)
        {
            if (Utils::FunctionAddress(m_Functions[i]) == Utils::FunctionAddress(func))
            {
                m_Functions.RemoveAt(i);
                break;
            }
        }

        return *this;
    }
}
