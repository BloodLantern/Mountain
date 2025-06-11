#pragma once

#include <array>
#include <cstdint>
#include <format>
#include <sstream>
#include <string>

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"
#include "Mountain/Utils/IHashable.hpp"
#include "Mountain/Utils/IStringConvertible.hpp"

/// @file guid.hpp
/// @brief Defines the Mountain::Guid class.

namespace Mountain
{
    /// @brief Stands for Global Unique Identifier, it represents a unique ID.
    class MOUNTAIN_API Guid final : IStringConvertible, IHashable
    {
        static constexpr size_t Data4Size = 8;

    public:
        constexpr Guid() = default;
        DEFAULT_VIRTUAL_DESTRUCTOR(Guid)
        DEFAULT_COPY_MOVE_OPERATIONS(Guid)

        /// @brief Empty guid
        static constexpr Guid Empty() { return Guid(); }

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
        const std::array<uint8_t, Data4Size>& GetData4() const;

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

        // IStringConvertible implementation

        [[nodiscard]]
        std::string ToString() const override;

        // IHashable implementation

        [[nodiscard]]
        size_t GetHashCode() const override;

    private:
        uint32_t m_Data1 = 0;
        uint16_t m_Data2 = 0;
        uint16_t m_Data3 = 0;
        std::array<uint8_t, Data4Size> m_Data4 = {};
    };
}
