#include "Mountain/rendering/graphics.hpp"

#include <stdexcept>

#include <glad/glad.h>

using namespace Mountain;

void Graphics::BindImage(const uint32_t textureId, const uint32_t shaderBinding, const ImageShaderAccess access)
{
    glBindImageTexture(shaderBinding, textureId, 0, GL_FALSE, 0, GL_READ_ONLY + static_cast<int32_t>(access), GL_RGBA32F);
}

void Graphics::SynchronizeGpuData(const GpuDataSynchronizationType dataType)
{
    if (dataType == GpuDataSynchronizationType::None)
        return;

    glMemoryBarrier(static_cast<GLbitfield>(dataType));
}

int32_t Graphics::ToOpenGl(const MagnificationFilter filter)
{
    switch (filter)
    {
        case MagnificationFilter::Linear:
            return GL_LINEAR;

        case MagnificationFilter::Nearest:
            return GL_NEAREST;
    }

    throw std::invalid_argument("Invalid magnification filter");
}

uint32_t Graphics::ShaderTypeToOpenGl(const ShaderType shaderType)
{
    switch (shaderType)
    {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;

        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;

        case ShaderType::Count:
            throw std::invalid_argument("Invalid shader type");
    }

    throw std::invalid_argument("Invalid shader type");
}
