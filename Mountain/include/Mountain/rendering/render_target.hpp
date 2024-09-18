#pragma once

#include "Mountain/core.hpp"

#include <Maths/matrix.hpp>
#include <Maths/vector2i.hpp>

#include "Mountain/scene/component/light_source.hpp"
#include "Mountain/utils/color.hpp"

BEGIN_MOUNTAIN

enum class MagnificationFilter : uint8_t
{
    Linear,
    Nearest,
    Count
};

ENUM_COUNT(MagnificationFilter)

class RenderTarget
{
public:
    /// @brief The ambient light color applied to the entirety of the RenderTarget
    Color ambientLight = Color::White();
    
    /// @brief Create an uninitialized RenderTarget
    MOUNTAIN_API RenderTarget() = default;
    /// @brief Create a RenderTarget and initialize it with the given values
    /// @param size The pixel size of the RenderTarget
    /// @param filter The MagnificationFilter to apply when rescaling the RenderTarget
    MOUNTAIN_API RenderTarget(Vector2i size, MagnificationFilter filter);
    MOUNTAIN_API ~RenderTarget();

    DELETE_COPY_MOVE_OPERATIONS(RenderTarget)

    /// @brief Initialize the RenderTarget with the given values
    MOUNTAIN_API void Initialize(Vector2i size, MagnificationFilter filter);
    /// @brief Reset the RenderTarget to an uninitialized state
    MOUNTAIN_API void Reset();
    /// @brief Reset the RenderTarget and initialize it again with the given values
    MOUNTAIN_API void Reset(Vector2i newSize, MagnificationFilter newFilter);

    MOUNTAIN_API void AddLightSource(const LightSource* lightSource);
    MOUNTAIN_API void RemoveLightSource(const LightSource* lightSource);
    MOUNTAIN_API const std::vector<const LightSource*>& GetLightSources() const;
    
    [[nodiscard]]
    MOUNTAIN_API uint32_t GetTextureId() const;

    [[nodiscard]]
    MOUNTAIN_API bool_t GetInitialized() const;
    
    [[nodiscard]]
    MOUNTAIN_API Vector2i GetSize() const;
    MOUNTAIN_API void SetSize(Vector2i newSize);
    
    [[nodiscard]]
    MOUNTAIN_API MagnificationFilter GetFilter() const;
    MOUNTAIN_API void SetFilter(MagnificationFilter newFilter);
    
    [[nodiscard]]
    MOUNTAIN_API const Matrix& GetCameraMatrix() const;
    MOUNTAIN_API void SetCameraMatrix(const Matrix& newCameraMatrix);
    
    [[nodiscard]]
    MOUNTAIN_API const Vector2& GetCameraScale() const;

private:
    uint32_t m_Texture;
    uint32_t m_Framebuffer;
    uint32_t m_Vbo, m_Vao;

    bool_t m_Initialized = false;

    Vector2i m_Size;
    MagnificationFilter m_Filter;

    Matrix m_Projection;

    std::vector<const LightSource*> m_LightSources;

    Matrix m_CameraMatrix = Matrix::Identity();
    Vector2 m_CameraScale = Vector2::One();

    void Use() const;

    void UpdateDrawCamera() const;

    static int32_t ToOpenGl(MagnificationFilter filter);

    static Matrix ComputeProjection(Vector2i size);

    friend class Renderer;
};

END_MOUNTAIN
