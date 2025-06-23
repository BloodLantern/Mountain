#pragma once


#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Utils/Requirements.hpp"

/// @file guid.hpp
/// @brief Defines the Mountain::Guid class.

namespace Mountain
{
    /// @brief Stands for Global Unique Identifier, it represents a unique ID.
    struct MOUNTAIN_API Guid final
    {
    private:
        static constexpr size_t Data4Size = 8;

    public:
        /// @brief Empty guid
        static constexpr Guid Empty();

        /// @brief Creates a new @ref Guid
        /// @return New guid
        static Guid New();

        /// @brief Parses a Guid from a string
        /// @param str String
        /// @returns Guid
        static Guid FromString(const char_t* str);

        [[nodiscard]]
        uint32_t GetData1() const;

        [[nodiscard]]
        uint16_t GetData2() const;

        [[nodiscard]]
        uint16_t GetData3() const;

        [[nodiscard]]
        const Array<uint8_t, Data4Size>& GetData4() const;

        /// @brief Compares 2 @ref Guid
        /// @param other Other guid
        /// @return Whether the @ref Guid are equal
        [[nodiscard]]
        bool_t operator==(const Guid& other) const;

        /// @brief Compares 2 @ref Guid
        /// @param other Other guid
        /// @return Whether the @ref Guid are different
        [[nodiscard]]
        bool_t operator!=(const Guid& other) const;

        [[nodiscard]]
        std::string ToString() const;

        [[nodiscard]]
        size_t GetHashCode() const;

    private:
        uint32_t m_Data1 = 0;
        uint16_t m_Data2 = 0;
        uint16_t m_Data3 = 0;
        Array<uint8_t, Data4Size> m_Data4{};
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, Guid);
    CHECK_REQUIREMENT(Requirements::Hashable, Guid);
}

// Start of Guid.inl

namespace Mountain
{
    constexpr Guid Guid::Empty() { return {}; }
}
