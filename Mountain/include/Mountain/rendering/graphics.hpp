#pragma once

#include "Mountain/core.hpp"

#include <magic_enum/magic_enum.hpp>

namespace Mountain::Graphics
{
    enum class ImageShaderAccess : uint8_t
    {
        ReadOnly,
        WriteOnly,
        ReadWrite
    };

    enum class GpuDataSynchronizationType : uint16_t
    {
        None               = 0,

        VertexAttribArray  = 1 << 0,
        ElementArray       = 1 << 1,
        Uniform            = 1 << 2,
        TextureFetch       = 1 << 3,
        // For some reason, the OpenGL bit values skip the 1 << 4 or 0x10 value
        ShaderImageAccess  = 1 << 5,
        Command            = 1 << 6,
        PixelBuffer        = 1 << 7,
        TextureUpdate      = 1 << 8,
        BufferUpdate       = 1 << 9,
        ClientMappedBuffer = 1 << 10,
        Framebuffer        = 1 << 11,
        TransformFeedback  = 1 << 12,
        AtomicCounter      = 1 << 13,
        ShaderStorage      = 1 << 14,
        QueryBuffer        = 1 << 15
    };

    enum class MagnificationFilter : uint8_t
    {
        Linear,
        Nearest
    };

    enum class ShaderType : uint8_t
    {
        Vertex,
        Fragment,
        Count
    };

    ENUM_COUNT(ShaderType);

    MOUNTAIN_API void BindImage(uint32_t textureId, uint32_t shaderBinding, ImageShaderAccess access);

    MOUNTAIN_API void SynchronizeGpuData(GpuDataSynchronizationType dataType);

    MOUNTAIN_API int32_t ToOpenGl(MagnificationFilter filter);

	MOUNTAIN_API uint32_t ShaderTypeToOpenGl(ShaderType shaderType);
}

ENUM_FLAGS(Mountain::Graphics::GpuDataSynchronizationType);
