#pragma once

#include "Mountain/Core.hpp"

#include <Math/matrix.hpp>
#include <Math/vector2i.hpp>

#include "Mountain/Graphics/GpuTexture.hpp"
#include "Mountain/Graphics/Graphics.hpp"
#include "Mountain/Graphics/LightSource.hpp"
#include "Mountain/Utils/Color.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Graphics/GpuFramebuffer.hpp"

namespace Mountain
{
    /// @brief A RenderTarget is a texture that can be drawn onto.
    /// @details This class is made to be used with @c Renderer::PushRenderTarget(), @c Renderer::PopRenderTarget and @c Draw::RenderTarget().
    class RenderTarget
    {
    public:
        /// @brief The ambient light color applied to the entirety of the RenderTarget
        Color ambientLight = Color::White();

        /// @brief Custom projection matrix.
        /// @details If left without a value, an orthographic projection with the size of the RenderTarget will be used instead.
        Optional<Matrix> projectionMatrix;

        /// @brief Create an uninitialized RenderTarget
        MOUNTAIN_API RenderTarget() = default;
        /// @brief Create a RenderTarget and initialize it with the given values
        /// @param size The pixel size of the RenderTarget
        /// @param filter The MagnificationFilter to apply when rescaling the RenderTarget
        MOUNTAIN_API RenderTarget(Vector2i size, Graphics::MagnificationFilter filter);
        MOUNTAIN_API ~RenderTarget();

        DEFAULT_COPY_MOVE_OPERATIONS(RenderTarget)

        /// @brief Initialize the RenderTarget with the given values
        MOUNTAIN_API void Initialize(Vector2i size, Graphics::MagnificationFilter filter);
        /// @brief Reset the RenderTarget to an uninitialized state
        MOUNTAIN_API void Reset();
        /// @brief Reset the RenderTarget and initialize it again with the given values
        MOUNTAIN_API void Reset(Vector2i newSize, Graphics::MagnificationFilter newFilter);

        MOUNTAIN_API LightSource& NewLightSource();
        MOUNTAIN_API void DeleteLightSource(const LightSource& lightSource);
        MOUNTAIN_API void ClearLightSources();

        /// @brief Adds a friendly debug name for this RenderTarget.
        /// This is used when debugging graphics in external applications such as Nsight or RenderDoc.
        /// This function does nothing if the application isn't compiled in Debug.
        /// @param name The name of this RenderTarget
        MOUNTAIN_API void SetDebugName(std::string_view name) const;

        GETTER(const List<LightSource>&, LightSources, m_LightSources)
        GETTER(Graphics::GpuFramebuffer, GpuFramebuffer, m_Framebuffer)
        GETTER(uint32_t, FramebufferId, m_Framebuffer.GetId())
        GETTER(Graphics::GpuTexture, GpuTexture, m_Texture)
        GETTER(uint32_t, TextureId, m_Texture.GetId())
        GETTER(bool_t, Initialized, m_Initialized)
        GETTER(Vector2i, Size, m_Size)
        GETTER(Graphics::MagnificationFilter, Filter, m_Filter)
        GETTER(const Matrix&, CameraMatrix, m_CameraMatrix)
        GETTER(Vector2, CameraScale, m_CameraScale)

        MOUNTAIN_API void SetSize(Vector2i newSize);
        MOUNTAIN_API void SetFilter(Graphics::MagnificationFilter newFilter);
        MOUNTAIN_API void SetCameraMatrix(const Matrix& newCameraMatrix);

    private:
        Graphics::GpuTexture m_Texture;
        Graphics::GpuFramebuffer m_Framebuffer;

        bool_t m_Initialized = false;

        Vector2i m_Size;
        Graphics::MagnificationFilter m_Filter;

        Matrix m_Projection;

        List<LightSource> m_LightSources;

        Matrix m_CameraMatrix = Matrix::Identity();
        Vector2 m_CameraScale = Vector2::One();

        void Use() const;

        void UpdateDrawCamera() const;

        Matrix ComputeProjection() const;

        friend class Renderer;
    };
}
