#include "Mountain/rendering/gpu_buffer.hpp"

#include <glad/glad.h>

using namespace Mountain::Graphics;

void GpuBuffer::Create() { glCreateBuffers(1, &m_Id); }

void GpuBuffer::Delete() { glDeleteBuffers(1, &m_Id); m_Id = 0; }

void GpuBuffer::Recreate() { Delete(); Create(); }

void GpuBuffer::SetStorage(
    const int64_t size,
    const void* data,
    BufferStorageFlags flags
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

void GpuBuffer::SetDebugName(const std::string_view name) const
{
#ifdef _DEBUG
    glObjectLabel(GL_BUFFER, m_Id, static_cast<GLsizei>(name.length()), name.data());
#endif
}

uint32_t GpuBuffer::GetId() const { return m_Id; }
