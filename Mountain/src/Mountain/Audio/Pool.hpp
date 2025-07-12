#pragma once

#include "Buffer.hpp"
#include "Source.hpp"
#include "Mountain/Core.hpp"

namespace Mountain::Audio
{
    class Pool
    {
    public:
        /// @brief Recommended amount of sources to have, if this isn't enough, 32 might also work, but going above isn't generally recommended
        static constexpr size_t MaxSourceAmount = 16;
        /// @brief There isn't really a hard limit for the amount of buffers, but this should be good enough
        static constexpr size_t MaxBufferAmount = 256;

        MOUNTAIN_API Pool();
        MOUNTAIN_API ~Pool();

        DELETE_COPY_MOVE_OPERATIONS(Pool)

        ATTRIBUTE_NODISCARD
        Source* FindFreeSource();

        ATTRIBUTE_NODISCARD
        Buffer* FindFreeBuffer();

    private:
        Array<Source*, MaxSourceAmount> m_Sources;
        Array<Buffer*, MaxBufferAmount> m_Buffers;
    };
}
