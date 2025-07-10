#pragma once

#include <magic_enum/magic_enum.hpp>

#include <Math/vector2.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Rendering/GpuBuffer.hpp"
#include "Mountain/Rendering/GpuVertexArray.hpp"
#include "Mountain/Rendering/RenderTarget.hpp"
#include "Mountain/Resource/Shader.hpp"
#include "Mountain/Resource/Texture.hpp"
#include "Mountain/Utils/Color.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"
#include "Mountain/Utils/Rectangle.hpp"

namespace Mountain
{
    enum class DrawTextureFlipping : uint8_t
    {
        None = 0,

        Horizontal      = 1 << 0,
        Vertical        = 1 << 1,
        Diagonal        = 1 << 2,
        AntiDiagonal    = 1 << 3
    };

    /// @brief The Draw class contains static functions to draw various things on screen.
    class Draw
    {
        STATIC_CLASS(Draw)

    public:
        /// @brief Clear the current RenderTarget
        /// @param color The new color of all the pixels
        MOUNTAIN_API static void Clear(const Color& color);

        MOUNTAIN_API static void Point(Vector2 position, const Color& color = Color::White());

        /// @brief Draw a line
        /// @param point1 The first point of the line
        /// @param point2 The second point of the line
        /// @param color The color of the line
        MOUNTAIN_API static void Line(Vector2 point1, Vector2 point2, const Color& color = Color::White());
        /// @brief Draw a line
        /// @param point1 The first point of the line
        /// @param point2 The second point of the line
        /// @param color1 The color of the first point
        /// @param color2 The color of the second point
        MOUNTAIN_API static void Line(Vector2 point1, Vector2 point2, const Color& color1, const Color& color2);

        /// @brief Draw a hollow triangle
        /// @param point1 The first point
        /// @param point2 The second point
        /// @param point3 The third point
        /// @param color The color of the triangle
        MOUNTAIN_API static void Triangle(Vector2 point1, Vector2 point2, Vector2 point3, const Color& color = Color::White());
        /// @brief Draw a hollow triangle
        /// @param point1 The first point
        /// @param point2 The second point
        /// @param point3 The third point
        /// @param color1 The color of the first point
        /// @param color2 The color of the second point
        /// @param color3 The color of the third point
        MOUNTAIN_API static void Triangle(Vector2 point1, Vector2 point2, Vector2 point3, const Color& color1, const Color& color2, const Color& color3);
        /// @brief Draw a filled triangle
        /// @param point1 The first point
        /// @param point2 The second point
        /// @param point3 The third point
        /// @param color The color of the triangle
        MOUNTAIN_API static void TriangleFilled(Vector2 point1, Vector2 point2, Vector2 point3, const Color& color = Color::White());
        /// @brief Draw a filled triangle
        /// @param point1 The first point
        /// @param point2 The second point
        /// @param point3 The third point
        /// @param color1 The color of the first point
        /// @param color2 The color of the second point
        /// @param color3 The color of the third point
        MOUNTAIN_API static void TriangleFilled(Vector2 point1, Vector2 point2, Vector2 point3, const Color& color1, const Color& color2, const Color& color3);

        /// @brief Draw a hollow rectangle
        /// @param position The top-left position of the rectangle
        /// @param size The size of the rectangle
        /// @param color The color of the rectangle
        MOUNTAIN_API static void Rectangle(Vector2 position, Vector2 size, const Color& color = Color::White());
        /// @brief Draw a hollow rectangle
        /// @param rectangle The rectangle position and size
        /// @param color The color of the rectangle
        MOUNTAIN_API static void Rectangle(const Mountain::Rectangle& rectangle, const Color& color = Color::White());
        /// @brief Draw a filled rectangle
        /// @param position The top-left position of the rectangle
        /// @param size The size of the rectangle
        /// @param color The color of the rectangle
        MOUNTAIN_API static void RectangleFilled(Vector2 position, Vector2 size, const Color& color = Color::White());
        /// @brief Draw a filled rectangle
        /// @param rectangle The rectangle position and size
        /// @param color The color of the rectangle
        MOUNTAIN_API static void RectangleFilled(const Mountain::Rectangle& rectangle, const Color& color = Color::White());

        /// @brief Draw a hollow circle
        /// @param center The center position of the circle
        /// @param radius The radius of the circle
        /// @param thickness The thickness of the circle
        /// @param scale The scale of the circle
        /// @param color The color of the circle
        MOUNTAIN_API static void Circle(Vector2 center, float_t radius, float_t thickness = 1.f, Vector2 scale = Vector2::One(), const Color& color = Color::White());

        /// @brief Draw a filled circle
        /// @param center The center position of the circle
        /// @param radius The radius of the circle
        /// @param scale The scale of the circle
        /// @param color The color of the circle
        MOUNTAIN_API static void CircleFilled(Vector2 center, float_t radius, Vector2 scale = Vector2::One(), const Color& color = Color::White());

        /// @brief Draw a hollow arc
        /// @param center The center position of the arc
        /// @param radius The radius of the arc
        /// @param startingAngle The starting angle of the arc
        /// @param deltaAngle The delta angle of the arc, e.g. the ending angle is @code startingAngle + deltaAngle@endcode
        /// @param thickness The thickness of the circle
        /// @param scale The scale of the arc
        /// @param color The color of the arc
        MOUNTAIN_API static void Arc(Vector2 center, float_t radius, float_t startingAngle, float_t deltaAngle, float_t thickness = 1.f, Vector2 scale = Vector2::One(), const Color& color = Color::White());

        /// @brief Draw a filled arc
        /// @param center The center position of the arc
        /// @param radius The radius of the arc
        /// @param startingAngle The starting angle of the arc
        /// @param deltaAngle The delta angle of the arc, e.g. the ending angle is @code startingAngle + deltaAngle@endcode
        /// @param scale The scale of the arc
        /// @param color The color of the arc
        MOUNTAIN_API static void ArcFilled(Vector2 center, float_t radius, float_t startingAngle, float_t deltaAngle, Vector2 scale = Vector2::One(), const Color& color = Color::White());

        /// @brief Draw a texture
        /// @param texture The texture to draw
        /// @param position The position of the texture
        /// @param scale The scale to apply to the texture
        /// @param rotation The rotation in radians to apply to the texture
        /// @param origin The rotation origin. Value in the range @code [{ 0, 0 }, { 1, 1 }] @endcode
        /// @param uv0 The first texture UV position
        /// @param uv1 The second texture UV position
        /// @param color The tint color of the texture. Use white for default colors
        /// @param flipFlags Flip flags from the @c DrawTextureFlipping enum
        /// @throws ArgumentException If @p uv0 is greater than @p uv1
        MOUNTAIN_API static void Texture(
            const Texture& texture,
            Vector2 position,
            Vector2 scale = Vector2::One(),
            float_t rotation = 0.f,
            Vector2 origin = Vector2::Zero(),
            Vector2 uv0 = Vector2::Zero(),
            Vector2 uv1 = Vector2::One(),
            const Color& color = Color::White(),
            Meta::UnderlyingEnumType<DrawTextureFlipping> flipFlags = static_cast<Meta::UnderlyingEnumType<DrawTextureFlipping>>(DrawTextureFlipping::None)
        );

        /// @brief Draw text
        /// @param font The font of the text
        /// @param text The text to draw
        /// @param position The top-left position of the text
        /// @param scale The scale to apply to the text
        /// @param color The color of the text
        MOUNTAIN_API static void Text(const Font& font, const std::string& text, Vector2 position, float_t scale = 1.f, const Color& color = Color::White());

        /// @brief Draw a RenderTarget
        /// @param renderTarget The RenderTarget to draw
        /// @param position The top-left position of the RenderTarget
        /// @param scale The scale to apply to the RenderTarget
        /// @param rotation The rotation in radians to apply to the RenderTarget
        /// @param uv0 The first texture UV position
        /// @param uv1 The second texture UV position
        /// @param color The color of the RenderTarget
        /// @param flipFlags Flip flags from the @c DrawTextureFlipping enum
        /// @throws ArgumentException If @p uv0 is greater than @p uv1
        MOUNTAIN_API static void RenderTarget(
            const RenderTarget& renderTarget,
            Vector2 position = Vector2::Zero(),
            Vector2 scale = Vector2::One(),
            float_t rotation = 0,
            Vector2 uv0 = Vector2::Zero(),
            Vector2 uv1 = Vector2::One(),
            const Color& color = Color::White(),
            Meta::UnderlyingEnumType<DrawTextureFlipping> flipFlags = static_cast<Meta::UnderlyingEnumType<DrawTextureFlipping>>(DrawTextureFlipping::None)
        );

        /// @brief Flushes the cached draw data onto the current RenderTarget
        ///
        /// This effectively renders everything that was scheduled since the last RenderTarget push/pop or @c Flush()
        MOUNTAIN_API static void Flush();

    private:
        struct PointData
        {
            Vector2 position;
            Color color;
        };

        struct LineData
        {
            Vector2 p1, p2;
            Color color;
        };

        struct LineColoredData
        {
            Vector2 p1, p2;
            Color c1, c2;
        };

        struct TriangleData
        {
            Vector2 p1, p2, p3;
            Color color;
        };

        struct TriangleColoredData
        {
            Vector2 p1, p2, p3;
            Color c1, c2, c3;
        };

        struct RectangleData
        {
            Matrix transformation;
            Color color;
        };

        struct CircleData
        {
            Matrix transformation;
            Vector2 center;
            float_t radius;
            float_t thickness;
            Vector2 scale;
            Color color;
            int32_t filled; // 32-bit boolean for GLSL
        };

        struct ArcData
        {
            Matrix transformation;
            Vector2 center;
            float_t radius;
            float_t startingAngle;
            float_t deltaAngle;
            float_t thickness;
            Vector2 scale;
            Color color;
            int32_t filled; // 32-bit boolean for GLSL
        };

        struct TextureData
        {
            Matrix transformation, uvProjection;
            Color color;
        };

        struct TextData
        {
            const Font* font;
            std::string text;
            Vector2 position;
            float_t scale;
            Color color;
        };

        struct RenderTargetData
        {
            const Mountain::RenderTarget* renderTarget;
            Matrix transformation, uvProjection;
            Vector2 scale;
            Color color;
        };

        enum class DrawDataType : uint8_t
        {
            Point,
            Line,
            LineColored,
            Triangle,
            TriangleColored,
            TriangleFilled,
            TriangleColoredFilled,
            Rectangle,
            RectangleFilled,
            Circle,
            Arc,
            Texture,
            Text,
            RenderTarget
        };

        struct CommandData
        {
            DrawDataType type;
            size_t count;
        };

        class DrawList
        {
        public:
            List<PointData> point;
            List<LineData> line;
            List<LineColoredData> lineColored;
            List<TriangleData> triangle;
            List<TriangleColoredData> triangleColored;
            List<TriangleData> triangleFilled;
            List<TriangleColoredData> triangleColoredFilled;
            List<RectangleData> rectangle;
            List<RectangleData> rectangleFilled;
            List<CircleData> circle;
            List<ArcData> arc;
            List<TextureData> texture;
            List<uint32_t> textureId;
            List<TextData> text;
            List<RenderTargetData> renderTarget;

            List<CommandData> commands;

            void AddCommand(DrawDataType type);
            void Clear();
        };

        static inline Pointer<Shader> m_PointShader;
        static inline Pointer<Shader> m_LineShader;
        static inline Pointer<Shader> m_LineColoredShader;
        static inline Pointer<Shader> m_TriangleShader;
        static inline Pointer<Shader> m_TriangleColoredShader;
        static inline Pointer<Shader> m_RectangleShader;
        static inline Pointer<Shader> m_CircleShader;
        static inline Pointer<Shader> m_ArcShader;

        static inline Pointer<Shader> m_TextureShader, m_TextShader, m_RenderTargetShader;

        static inline Graphics::GpuBuffer m_RectangleEbo, m_Vbo, m_RectangleVbo, m_TextureVbo, m_TextVbo, m_RenderTargetVbo, m_RenderTargetSsbo;
        static inline Graphics::GpuVertexArray m_PointVao, m_LineVao, m_LineColoredVao, m_TriangleVao, m_TriangleColoredVao, m_RectangleVao, m_CircleVao, m_ArcVao, m_TextureVao, m_TextVao, m_RenderTargetVao;

        static inline Matrix m_ProjectionMatrix;

        static inline Matrix m_CameraMatrix = Matrix::Identity();
        static inline Vector2 m_CameraScale = Vector2::One();

        static inline DrawList m_DrawList;

        static void Initialize();
        static void LoadResources();
        static void Shutdown();

        static void InitializePointBuffers();
        static void InitializeLineBuffers();
        static void InitializeLineColoredBuffers();
        static void InitializeTriangleBuffers();
        static void InitializeTriangleColoredBuffers();
        static void InitializeRectangleBuffers();
        static void InitializeCircleBuffers();
        static void InitializeArcBuffers();
        static void InitializeTextureBuffers();
        static void InitializeTextBuffers();
        static void InitializeRenderTargetBuffers();

        static void SetProjectionMatrix(const Matrix& newProjectionMatrix);
        static void SetCamera(const Matrix& newCameraMatrix, Vector2 newCameraScale);
        static void UpdateShaderMatrices();

        static void CircleInternal(Vector2 center, float_t radius, float_t thickness, bool_t filled, Vector2 scale, const Color& color);
        static void ArcInternal(Vector2 center, float_t radius, float_t startingAngle, float_t deltaAngle, float_t thickness, bool_t filled, Vector2 scale, const Color& color);

        static void RenderPointData(const List<PointData>& points, size_t index, size_t count);
        static void RenderLineData(const List<LineData>& lines, size_t index, size_t count);
        static void RenderLineColoredData(const List<LineColoredData>& linesColored, size_t index, size_t count);
        static void RenderTriangleData(const List<TriangleData>& triangles, bool_t filled, size_t index, size_t count);
        static void RenderTriangleColoredData(const List<TriangleColoredData>& trianglesColored, bool_t filled, size_t index, size_t count);
        static void RenderRectangleData(const List<RectangleData>& rectangles, bool_t filled, size_t index, size_t count);
        static void RenderCircleData(const List<CircleData>& circles, size_t index, size_t count);
        static void RenderArcData(const List<ArcData>& arcs, size_t index, size_t count);
        static void RenderTextureData(const List<TextureData>& textures, uint32_t textureId, size_t index, size_t count);
        static void RenderTextData(const List<TextData>& texts, size_t index, size_t count);
        static void RenderRenderTargetData(const List<RenderTargetData>& renderTargets, size_t index, size_t count);

        friend class Renderer;
        friend class RenderTarget;
        friend class ParticleSystem;
    };
}

ENUM_FLAGS(Mountain::DrawTextureFlipping)
