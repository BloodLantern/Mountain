#include "Mountain/PrecompiledHeader.hpp"

#include "GpuFramebuffer.hpp"

using namespace Mountain::Graphics;

void GpuFramebuffer::Create() { glCreateFramebuffers(1, &m_Id); }

void GpuFramebuffer::Delete() { glDeleteFramebuffers(1, &m_Id); m_Id = 0; }

void GpuFramebuffer::Recreate() { Delete(); Create(); }

void GpuFramebuffer::SetTexture(const uint32_t textureId, const int32_t mipmapLevel) const
{
    glNamedFramebufferTexture(m_Id, GL_COLOR_ATTACHMENT0, textureId, mipmapLevel);
}

void GpuFramebuffer::SetTexture(const GpuTexture gpuTexture, const int32_t mipmapLevel) const
{
    SetTexture(gpuTexture.GetId(), mipmapLevel);
}

FramebufferStatus GpuFramebuffer::CheckStatus(const FramebufferType type) const
{
    return FromOpenGl<FramebufferStatus>(glCheckNamedFramebufferStatus(m_Id, ToOpenGl(type)));
}

void GpuFramebuffer::SetDebugName(ATTRIBUTE_MAYBE_UNUSED const std::string_view name) const
{
#ifdef _DEBUG
    glObjectLabel(GL_FRAMEBUFFER, m_Id, static_cast<GLsizei>(name.length()), name.data());
#endif
}

GpuFramebuffer::operator uint32_t() const { return m_Id; }
