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
    /// @brief Create an uninitialized RenderTarget
    RenderTarget() = default;
    /// @brief Create a RenderTarget and initialize it with the given values
    /// @param size The pixel size of the RenderTarget
    /// @param filter The MagnificationFilter to apply when rescaling the RenderTarget
    RenderTarget(Vector2i size, MagnificationFilter filter);
    ~RenderTarget();

    DELETE_COPY_MOVE_OPERATIONS(RenderTarget)

    /// @brief Initialize the RenderTarget with the given values
    void Initialize(Vector2i size, MagnificationFilter filter);
    /// @brief Reset the RenderTarget to an uninitialized state
    void Reset();
    /// @brief Reset the RenderTarget and initialize it again with the given values
    void Reset(Vector2i size, MagnificationFilter filter);
    
    [[nodiscard]]
    uint32_t GetTextureId() const;

    [[nodiscard]]
    bool_t GetInitialized() const;
    
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

    bool_t m_Initialized = false;

    Vector2i m_Size;
    MagnificationFilter m_Filter;

    Matrix m_Projection;

    void Use() const;

    static int32_t ToOpenGl(MagnificationFilter filter);

    static Matrix ComputeProjection(Vector2i size);

    friend class Renderer;
};

END_MOUNTAIN
