#pragma once

#include "Mountain/core.hpp"

#include <array>

#include <magic_enum/magic_enum.hpp>

#include <Maths/vector2.hpp>

#include "Mountain/rendering/render_target.hpp"
#include "Mountain/resource/font.hpp"
#include "Mountain/resource/shader.hpp"
#include "Mountain/resource/texture.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/rectangle.hpp"

BEGIN_MOUNTAIN

enum class DrawTextureFlipping
{
    None,
    Horizontal      = 1 << 0,
    Vertical        = 1 << 1,
    Diagonal        = 1 << 2,
    AntiDiagonal    = 1 << 3
};

/// @brief The Draw class is a helper class that contains static functions to draw shapes.
class Draw
{
    STATIC_CLASS(Draw)

public:
    MOUNTAIN_API static inline Matrix cameraMatrix = Matrix::Identity();

    /// @brief Clear the current RenderTarget
    /// @param color The new color of all the pixels
    MOUNTAIN_API static void Clear(const Color& color);

    /// @brief Draw points (pixels)
    /// @param positions An array of points
    /// @param count The length of the @p positions array
    /// @param color The color of the points
    MOUNTAIN_API static void Points(const Vector2* positions, uint32_t count, const Color& color = Color::White());
    /// @brief Draw points (pixels)
    /// @tparam Size The size of the @p positions array
    /// @param positions An array of points
    /// @param color The color of the points
    template <size_t Size>
    static void Points(const std::array<Vector2, Size>& positions, const Color& color = Color::White());
    /// @brief Draw points (pixels) with the given @p colors
    /// @param positions An array of points
    /// @param colors An array of colors, one for each point
    /// @param count The length of the @p positions and @p colors arrays
    MOUNTAIN_API static void Points(const Vector2* positions, const Color* colors, uint32_t count);
    /// @brief Draw points (pixels) with the given @p colors
    /// @tparam Size The size of the @p positions array
    /// @param positions An array of points
    /// @param colors An array of colors, one for each point
    template <size_t Size>
    static void Points(const std::array<Vector2, Size>& positions, const std::array<Color, Size>& colors);

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
    /// @brief Draw a hollow rectangle
    /// @param point1 The position of the first point
    /// @param point2 The position of the second point
    /// @param point3 The position of the third point
    /// @param point4 The position of the fourth point
    /// @param color The color of the rectangle
    MOUNTAIN_API static void Rectangle(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4, const Color& color = Color::White());
    /// @brief Draw a hollow rectangle
    /// @param position The top-left position of the rectangle
    /// @param size The size of the rectangle
    /// @param color1 The color of the first point
    /// @param color2 The color of the second point
    /// @param color3 The color of the third point
    /// @param color4 The color of the fourth point
    MOUNTAIN_API static void Rectangle(Vector2 position, Vector2 size, const Color& color1, const Color& color2, const Color& color3, const Color& color4);
    /// @brief Draw a hollow rectangle
    /// @param rectangle The rectangle position and size
    /// @param color1 The color of the first point
    /// @param color2 The color of the second point
    /// @param color3 The color of the third point
    /// @param color4 The color of the fourth point
    MOUNTAIN_API static void Rectangle(
        const Mountain::Rectangle& rectangle,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4
    );
    /// @brief Draw a hollow rectangle
    /// @param point1 The position of the first point
    /// @param point2 The position of the second point
    /// @param point3 The position of the third point
    /// @param point4 The position of the fourth point
    /// @param color1 The color of the first point
    /// @param color2 The color of the second point
    /// @param color3 The color of the third point
    /// @param color4 The color of the fourth point
    MOUNTAIN_API static void Rectangle(
        Vector2 point1,
        Vector2 point2,
        Vector2 point3,
        Vector2 point4,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4
    );
    /// @brief Draw a filled rectangle
    /// @param position The top-left position of the rectangle
    /// @param size The size of the rectangle
    /// @param color The color of the rectangle
    MOUNTAIN_API static void RectangleFilled(Vector2 position, Vector2 size, const Color& color = Color::White());
    /// @brief Draw a filled rectangle
    /// @param rectangle The rectangle position and size
    /// @param color The color of the rectangle
    MOUNTAIN_API static void RectangleFilled(const Mountain::Rectangle& rectangle, const Color& color = Color::White());
    /// @brief Draw a filled rectangle
    /// @param point1 The position of the first point
    /// @param point2 The position of the second point
    /// @param point3 The position of the third point
    /// @param point4 The position of the fourth point
    /// @param color The color of the rectangle
    MOUNTAIN_API static void RectangleFilled(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4, const Color& color = Color::White());
    /// @brief Draw a filled rectangle
    /// @param position The top-left position of the rectangle
    /// @param size The size of the rectangle
    /// @param color1 The color of the first point
    /// @param color2 The color of the second point
    /// @param color3 The color of the third point
    /// @param color4 The color of the fourth point
    MOUNTAIN_API static void RectangleFilled(
        Vector2 position,
        Vector2 size,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4
    );
    /// @brief Draw a filled rectangle
    /// @param rectangle The rectangle position and size
    /// @param color1 The color of the first point
    /// @param color2 The color of the second point
    /// @param color3 The color of the third point
    /// @param color4 The color of the fourth point
    MOUNTAIN_API static void RectangleFilled(
        const Mountain::Rectangle& rectangle,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4
    );
    /// @brief Draw a filled rectangle
    /// @param point1 The position of the first point
    /// @param point2 The position of the second point
    /// @param point3 The position of the third point
    /// @param point4 The position of the fourth point
    /// @param color1 The color of the first point
    /// @param color2 The color of the second point
    /// @param color3 The color of the third point
    /// @param color4 The color of the fourth point
    MOUNTAIN_API static void RectangleFilled(
        Vector2 point1,
        Vector2 point2,
        Vector2 point3,
        Vector2 point4,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4
    );

    /// @brief Draw a hollow circle
    /// @param position The center position of the circle
    /// @param radius The radius of the circle
    /// @param color The color of the circle
    /// @param segments The circle is drawn using multiple segment lines. The higher this number is, the more accurate the circle
    ///        will be but the more computations it will take
    MOUNTAIN_API static void Circle(Vector2 position, float_t radius, const Color& color = Color::White(), uint32_t segments = 20);
    /// @brief Draw a dotted hollow circle
    /// @param position The center position of the circle
    /// @param radius The radius of the circle
    /// @param color The color of the circle
    /// @param segments The circle is drawn using multiple segment lines. The higher this number is, the more accurate the circle
    ///        will be but the more computations it will take. This value represents how many dotted lines will be drawn
    MOUNTAIN_API static void CircleDotted(Vector2 position, float_t radius, const Color& color = Color::White(), uint32_t segments = 10);
    /// @brief Draw a filled circle
    /// @param position The center position of the circle
    /// @param radius The radius of the circle
    /// @param color The color of the circle
    MOUNTAIN_API static void CircleFilled(Vector2 position, float_t radius, const Color& color = Color::White());

    /// @brief Draw a texture
    /// @param texture The texture to draw
    /// @param position The position of the texture
    /// @param scale The scale to apply to the texture
    /// @param rotation The rotation in radians to apply to the texture
    /// @param uv0 The first texture UV position
    /// @param uv1 The second texture UV position
    /// @param color The tint color of the texture. Use white for default colors
    /// @param flipFlags Flip flags from the @c DrawTextureFlipping enum.
    MOUNTAIN_API static void Texture(
        const Texture& texture,
        Vector2 position,
        Vector2 scale = Vector2::One(),
        float_t rotation = 0.f,
        Vector2 uv0 = Vector2::Zero(),
        Vector2 uv1 = Vector2::One(),
        const Color& color = Color::White(),
        uint8_t flipFlags = static_cast<uint8_t>(DrawTextureFlipping::None)
    );

    /// @brief Draw text
    /// @param font The font of the text
    /// @param text The text to draw
    /// @param position The top-left position of the text
    /// @param scale The scale to apply to the text
    /// @param color The color of the text
    MOUNTAIN_API static void Text(const Font& font, std::string_view text, Vector2 position, float_t scale = 1.f, const Color& color = Color::White());

    /// @brief Draw a RenderTarget
    /// @param renderTarget The RenderTarget to draw
    /// @param position The top-left position of the RenderTarget
    /// @param scale The scale to apply to the RenderTarget
    /// @param rotation The rotation in radians to apply to the RenderTarget
    /// @param uv0 The first texture UV position
    /// @param uv1 The second texture UV position
    /// @param color The color of the RenderTarget
    /// @param flipFlags Whether to flip the texture anti-diagonally (using the top-left to bottom-right diagonal)
    MOUNTAIN_API static void RenderTarget(
        const RenderTarget& renderTarget,
        Vector2 position = Vector2::Zero(),
        Vector2 scale = Vector2::One(),
        float_t rotation = 0,
        Vector2 uv0 = Vector2::Zero(),
        Vector2 uv1 = Vector2::One(),
        const Color& color = Color::White(),
        uint8_t flipFlags = static_cast<uint8_t>(DrawTextureFlipping::None)
    );

private:
    MOUNTAIN_API static inline Pointer<Shader> m_PrimitiveShader, m_PrimitiveColoredShader, m_CircleShader, m_TextureShader, m_TextShader, m_PostProcessingShader;

    MOUNTAIN_API static inline uint32_t m_RectangleEbo, m_Vbo, m_ImageVbo, m_TextVbo, m_Vao, m_ImageVao, m_TextVao;

    MOUNTAIN_API static inline Matrix m_Projection;

    static void Initialize();
    static void Shutdown();

    static void SetProjectionMatrix(const Matrix& projection);

    static void TriangleInternal(Vector2 point1, Vector2 point2, Vector2 point3, const Color& color, bool_t filled);
    static void TriangleInternal(Vector2 point1, Vector2 point2, Vector2 point3, const Color& color1, const Color& color2, const Color& color3, bool_t filled);
    
    static void RectangleInternal(const Mountain::Rectangle& rectangle, const Color& color, bool_t filled);
    static void RectangleInternal(
        const Mountain::Rectangle& rectangle,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4,
        bool_t filled
    );
    static void RectangleInternal(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4, const Color& color, bool_t filled);
    static void RectangleInternal(
        Vector2 point1,
        Vector2 point2,
        Vector2 point3,
        Vector2 point4,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4,
        bool_t filled
    );

    static void CircleInternal(Vector2 position, float_t radius, const Color& color, uint32_t segments, bool_t dotted);
    
    static void TextureInternal(
        uint32_t textureId,
        Vector2i textureSize,
        const Shader& shader,
        Vector2 position,
        Vector2 scale,
        float_t rotation,
        Vector2 uv0,
        Vector2 uv1,
        const Color& color,
        uint8_t flipFlags = static_cast<uint8_t>(DrawTextureFlipping::None)
    );
    
    friend class Renderer;
    friend class RenderTarget;
};

END_MOUNTAIN

ENUM_FLAGS(Mountain::DrawTextureFlipping, uint8_t)

#include "Mountain/rendering/draw.inl"
