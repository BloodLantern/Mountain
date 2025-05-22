module;

#include <glad/glad.h>

module Mountain:Rendering_GpuBuffer;
import :Rendering_GpuBuffer;

using namespace Mountain::Graphics;

void GpuBuffer::Create() { glCreateBuffers(1, &m_Id); }

void GpuBuffer::Delete() { glDeleteBuffers(1, &m_Id); m_Id = 0; }

void GpuBuffer::Recreate() { Delete(); Create(); }

void GpuBuffer::SetStorage(
    const int64_t size,
    const void* data,
    const Meta::Flags<BufferStorageFlags> flags
) const
{
    glNamedBufferStorage(m_Id, size, data, static_cast<GLbitfield>(flags));
}

void GpuBuffer::SetSubData(const int64_t offset, const int64_t size, const void* data) const
{
    glNamedBufferSubData(m_Id, offset, size, data);
}

void GpuBuffer::SetData(const int64_t size, const void* data, const BufferUsage usage) const
{
    glNamedBufferData(m_Id, size, data, ToOpenGl(usage));
}

void GpuBuffer::SetDebugName([[maybe_unused]] const std::string_view name) const
{
#ifdef _DEBUG
    glObjectLabel(GL_BUFFER, m_Id, static_cast<GLsizei>(name.length()), name.data());
#endif
}

GpuBuffer::operator unsigned int() const { return m_Id; }
