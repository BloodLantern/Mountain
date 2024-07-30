#pragma once

#include "Mountain/core.hpp"

#include <Maths/matrix.hpp>
#include <Maths/vector2i.hpp>

BEGIN_MOUNTAIN

enum class MagnificationFilter
{
    Linear,
    Nearest,
    Count
};

ENUM_COUNT(MagnificationFilter)

class MOUNTAIN_API RenderTarget
{
public:
    RenderTarget(Vector2i size, MagnificationFilter filter);
    ~RenderTarget();

    DEFAULT_COPY_MOVE_OPERATIONS(RenderTarget)
    
    [[nodiscard]]
    uint32_t GetTextureId() const;
    
    [[nodiscard]]
    Vector2i GetSize() const;
    void SetSize(Vector2i size);
    
    [[nodiscard]]
    MagnificationFilter GetFilter() const;
    void SetFilter(MagnificationFilter filter);

private:
    uint32_t m_Texture;
    uint32_t m_Framebuffer;
    uint32_t m_Vbo, m_Vao;

    Vector2i m_Size;
    MagnificationFilter m_Filter;

    Matrix m_Projection;

    void Use() const;

    static int32_t MagnificationFilterToOpenGl(MagnificationFilter filter);

    static Matrix ComputeProjection(Vector2i size);

    friend class Renderer;
};

END_MOUNTAIN
