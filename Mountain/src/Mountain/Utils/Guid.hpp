#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Utils/Requirements.hpp"

/// @file Guid.hpp
/// @brief Defines the Mountain::Guid class.

namespace Mountain
{
    /// @brief Stands for Global Unique Identifier, it represents a unique ID.
    struct MOUNTAIN_API Guid final
    {
        // ReSharper disable once CppInconsistentNaming
        static constexpr u8 Variant10xxMask = 0xC0;
        // ReSharper disable once CppInconsistentNaming
        static constexpr u8 Variant10xxValue = 0x80;

        static constexpr u16 VersionMask = 0xF000;
        static constexpr u16 Version4Value = 0x4000;
        static constexpr u16 Version7Value = 0x7000;

        /// @brief Empty guid
        static constexpr Guid Empty();

        /// @brief Creates a new @ref Guid
        /// @return New guid
        static Guid New();

        /// @brief Parses a Guid from a string
        /// @param str String
        /// @returns Guid
        static Guid FromString(const c8* str);

        ATTRIBUTE_NODISCARD
        u32 GetData1() const;

        ATTRIBUTE_NODISCARD
        u16 GetData2() const;

        ATTRIBUTE_NODISCARD
        u16 GetData3() const;

        ATTRIBUTE_NODISCARD
        const Array<u8, 8>& GetData4() const;

        /// @brief Compares 2 @ref Guid
        /// @param other Other guid
        /// @return Whether the @ref Guid are equal
        ATTRIBUTE_NODISCARD
        bool operator==(const Guid& other) const;

        /// @brief Compares 2 @ref Guid
        /// @param other Other guid
        /// @return Whether the @ref Guid are different
        ATTRIBUTE_NODISCARD
        bool operator!=(const Guid& other) const;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

        ATTRIBUTE_NODISCARD
        usize GetHashCode() const;

    private:
        u32 m_Data1 = 0;
        u16 m_Data2 = 0;
        u16 m_Data3 = 0;
        Array<u8, 8> m_Data4{};
    };

    CHECK_REQUIREMENT(Requirements::Equatable, Guid);
    CHECK_REQUIREMENT(Requirements::Hashable, Guid);
    CHECK_REQUIREMENT(Requirements::StringConvertible, Guid);
}

// Start of Guid.inl

namespace Mountain
{
    constexpr Guid Guid::Empty() { return {}; }
}
