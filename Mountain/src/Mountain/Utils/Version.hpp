#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"

namespace Mountain
{
    class MOUNTAIN_API Version
    {
    public:
        /// @brief Parses a Version from a string
        static Version FromString(const c8* str);

        constexpr Version() = default;
        constexpr Version(s32 major, s32 minor);
        constexpr Version(s32 major, s32 minor, s32 patch);

        CONSTEXPR_GETTER_M(s32, Major)
        CONSTEXPR_GETTER_M(s32, Minor)
        CONSTEXPR_GETTER_M(s32, Patch)

        ATTRIBUTE_NODISCARD
        constexpr std::strong_ordering operator<=>(const Version& other) const;
        ATTRIBUTE_NODISCARD
        constexpr bool operator==(const Version& other) const;

        ATTRIBUTE_NODISCARD
        constexpr usize GetHashCode() const;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

    private:
        s32 m_Major = 0, m_Minor = 0, m_Patch = -1;
    };

    CHECK_REQUIREMENT(Requirements::Comparable, Version);
    CHECK_REQUIREMENT(Requirements::Equatable, Version);
    CHECK_REQUIREMENT(Requirements::Hashable, Version);
    CHECK_REQUIREMENT(Requirements::StringConvertible, Version);

    const Version FrameworkVersion = Version::FromString(MOUNTAIN_VERSION_STRING);
}

// Start of Version.inl

namespace Mountain
{
    constexpr Version::Version(const s32 major, const s32 minor)
        : m_Major{major}
        , m_Minor{minor}
    {
        ThrowHelper::VersionThrowIfComponentNegative(major, "major");
        ThrowHelper::VersionThrowIfComponentNegative(minor, "minor");
    }

    constexpr Version::Version(const s32 major, const s32 minor, const s32 patch)
        : m_Major{major}
        , m_Minor{minor}
        , m_Patch{patch}
    {
        ThrowHelper::VersionThrowIfComponentNegative(major, "major");
        ThrowHelper::VersionThrowIfComponentNegative(minor, "minor");
        ThrowHelper::VersionThrowIfComponentNegative(patch, "patch");
    }

    constexpr std::strong_ordering Version::operator<=>(const Version& other) const
    {
        std::strong_ordering ordering = m_Major <=> other.m_Major;
        if (ordering != std::strong_ordering::equal)
            return ordering;

        ordering = m_Minor <=> other.m_Minor;
        if (ordering != std::strong_ordering::equal)
            return ordering;

        return m_Patch <=> other.m_Patch;
    }

    constexpr bool Version::operator==(const Version& other) const
    {
        return *this <=> other == std::strong_ordering::equal;
    }

    constexpr usize Version::GetHashCode() const
    {
        usize accumulator = 0;

        accumulator |= (m_Major & 0x000000FF) << 20;
        accumulator |= (m_Minor & 0x000000FF) << 12;
        accumulator |= (m_Patch & 0x00000FFF);

        return accumulator;
    }
}
