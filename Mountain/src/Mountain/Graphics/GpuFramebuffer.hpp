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

        void SetTexture(u32 textureId, FramebufferAttachment attachment, s32 mipmapLevel = 0) const;
        void SetTexture(GpuTexture gpuTexture, FramebufferAttachment attachment, s32 mipmapLevel = 0) const;

        ATTRIBUTE_NODISCARD
        FramebufferStatus CheckStatus(FramebufferType type) const;

        void SetDebugName(std::string_view name) const;

        GETTER(u32, Id, m_Id)

        ATTRIBUTE_NODISCARD
        explicit operator u32() const;

    private:
        u32 m_Id = 0;
    };
}
