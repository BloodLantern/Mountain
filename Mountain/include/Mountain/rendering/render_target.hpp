#pragma once

#include "Mountain/core.hpp"

#include <Maths/matrix.hpp>
#include <Maths/vector2i.hpp>

#include "Mountain/rendering/gpu_texture.hpp"
#include "Mountain/rendering/graphics.hpp"
#include "Mountain/rendering/light_source.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/containers/list.hpp"

namespace Mountain
{
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
        MOUNTAIN_API RenderTarget(Vector2i size, Graphics::MagnificationFilter filter);
        MOUNTAIN_API ~RenderTarget();

        DELETE_COPY_MOVE_OPERATIONS(RenderTarget)

        /// @brief Initialize the RenderTarget with the given values
        MOUNTAIN_API void Initialize(Vector2i size, Graphics::MagnificationFilter filter);
        /// @brief Reset the RenderTarget to an uninitialized state
        MOUNTAIN_API void Reset();
        /// @brief Reset the RenderTarget and initialize it again with the given values
        MOUNTAIN_API void Reset(Vector2i newSize, Graphics::MagnificationFilter newFilter);

        MOUNTAIN_API LightSource& NewLightSource();
        MOUNTAIN_API void DeleteLightSource(const LightSource& lightSource);
        MOUNTAIN_API void ClearLightSources();
        MOUNTAIN_API const List<LightSource>& GetLightSources() const;

        /// @brief Adds a friendly debug name for this RenderTarget.
        /// This is used when debugging graphics in external applications such as Nsight or RenderDoc.
        /// This function does nothing if the application isn't compiled in Debug.
        /// @param name The name of this RenderTarget
        MOUNTAIN_API void SetDebugName(std::string_view name) const;

        [[nodiscard]]
        MOUNTAIN_API uint32_t GetTextureId() const;

        [[nodiscard]]
        MOUNTAIN_API Graphics::GpuTexture GetGpuTexture() const;

        [[nodiscard]]
        MOUNTAIN_API bool_t GetInitialized() const;

        [[nodiscard]]
        MOUNTAIN_API Vector2i GetSize() const;
        MOUNTAIN_API void SetSize(Vector2i newSize);

        [[nodiscard]]
        MOUNTAIN_API Graphics::MagnificationFilter GetFilter() const;
        MOUNTAIN_API void SetFilter(Graphics::MagnificationFilter newFilter);

        [[nodiscard]]
        MOUNTAIN_API const Matrix& GetCameraMatrix() const;
        MOUNTAIN_API void SetCameraMatrix(const Matrix& newCameraMatrix);

        [[nodiscard]]
        MOUNTAIN_API const Vector2& GetCameraScale() const;

    private:
        Graphics::GpuTexture m_Texture;
        uint32_t m_Framebuffer;
        uint32_t m_Vbo, m_Vao;

        bool_t m_Initialized = false;

        Vector2i m_Size;
        Graphics::MagnificationFilter m_Filter;

        Matrix m_Projection;

        List<LightSource> m_LightSources;

        Matrix m_CameraMatrix = Matrix::Identity();
        Vector2 m_CameraScale = Vector2::One();

        void Use() const;

        void UpdateDrawCamera() const;

        static Matrix ComputeProjection(Vector2i size);

        friend class Renderer;
    };
}
