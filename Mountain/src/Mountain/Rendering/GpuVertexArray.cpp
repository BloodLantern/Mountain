#include "Mountain/Rendering/GpuVertexArray.hpp"

#include <glad/glad.h>

using namespace Mountain::Graphics;

void GpuVertexArray::Create() { glCreateVertexArrays(1, &m_Id); }

void GpuVertexArray::Delete() { glDeleteVertexArrays(1, &m_Id); m_Id = 0; }

void GpuVertexArray::Recreate() { Delete(); Create(); }

void GpuVertexArray::SetDebugName(ATTRIBUTE_MAYBE_UNUSED const std::string_view name) const
{
#ifdef _DEBUG
    glObjectLabel(GL_VERTEX_ARRAY, m_Id, static_cast<GLsizei>(name.length()), name.data());
#endif
}

uint32_t GpuVertexArray::GetId() const { return m_Id; }

GpuVertexArray::operator unsigned int() const { return m_Id; }
