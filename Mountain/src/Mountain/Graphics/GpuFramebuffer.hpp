#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Graphics/GpuTexture.hpp"

namespace Mountain::Graphics
{
    /// @brief Low-level interface for OpenGL framebuffers
    struct MOUNTAIN_API GpuFramebuffer
    {
        void Create();

        void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        void Recreate();

        void SetTexture(uint32_t textureId, FramebufferAttachment attachment, int32_t mipmapLevel = 0) const;
        void SetTexture(GpuTexture gpuTexture, FramebufferAttachment attachment, int32_t mipmapLevel = 0) const;

        ATTRIBUTE_NODISCARD
        FramebufferStatus CheckStatus(FramebufferType type) const;

        void SetDebugName(std::string_view name) const;

        GETTER(uint32_t, Id, m_Id)

        ATTRIBUTE_NODISCARD
        explicit operator uint32_t() const;

    private:
        uint32_t m_Id = 0;
    };
}
