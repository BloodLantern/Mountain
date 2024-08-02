#include "Mountain/rendering/draw.hpp"

#include <glad/glad.h>

#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/resource/shader.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

void Draw::Clear(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Draw::Points(const Vector2* positions, const uint32_t count, const Color& color)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    
    const size_t dataSize = count * sizeof(Vector2);
    Vector2* data = static_cast<Vector2*>(_malloca(dataSize));
    std::memcpy(data, positions, dataSize);

    for (uint32_t i = 0; i < count; i++)
        *data = cameraMatrix * *data;
    
    glBufferData(GL_ARRAY_BUFFER, static_cast<int64_t>(sizeof(Vector2)) * count, data, GL_STREAM_DRAW);

    _freea(data);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);

    m_PrimitiveShader->Use();
    m_PrimitiveShader->SetUniform("color", color);

    glDrawArrays(GL_POINTS, 0, static_cast<int32_t>(count));

    m_PrimitiveShader->Unuse();

    glBindVertexArray(0);
}

void Draw::Points(const Vector2* positions, const Color* colors, const uint32_t count)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

    float_t* data = static_cast<float_t*>(_malloca(count * sizeof(Vector2) / sizeof(float_t) + count * sizeof(Color) / sizeof(float_t) * sizeof(float_t)));
    for (uint32_t i = 0; i < count; i++)
    {
        const Vector2 position = cameraMatrix * positions[i];
        data[i * 6 + 0] = position.x;
        data[i * 6 + 1] = position.y;

        data[i * 6 + 2] = colors[i].r;
        data[i * 6 + 3] = colors[i].g;
        data[i * 6 + 4] = colors[i].b;
        data[i * 6 + 5] = colors[i].a;
    }

    glBufferData(GL_ARRAY_BUFFER, static_cast<int64_t>(sizeof(Vector2)) * count + static_cast<int64_t>(sizeof(Color)) * count, data, GL_STREAM_DRAW);

    _freea(data);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), Utils::IntToPointer<void>(sizeof(Vector2)));
    glEnableVertexAttribArray(1);

    m_PrimitiveColoredShader->Use();

    glDrawArrays(GL_POINTS, 0, static_cast<int32_t>(count));

    m_PrimitiveColoredShader->Unuse();

    glBindVertexArray(0);
}

void Draw::Line(const Vector2 point1, const Vector2 point2, const Color& color)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    
    std::array p = { point1, point2 };
    
    for (Vector2& v : p)
        v = cameraMatrix * v;
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);

    m_PrimitiveShader->Use();
    m_PrimitiveShader->SetUniform("color", color);

    glDrawArrays(GL_LINES, 0, 2);

    m_PrimitiveShader->Unuse();

    glBindVertexArray(0);
}

void Draw::Line(const Vector2 point1, const Vector2 point2, const Color& color1, const Color& color2)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    
    const Vector2 p1 = cameraMatrix * point1;
    const Vector2 p2 = cameraMatrix * point2;
    
    const std::array p = {
        p1.x, p1.y,
        color1.r, color1.g, color1.b, color1.a,
        p2.x, p2.y,
        color2.r, color2.g, color2.b, color2.a
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), Utils::IntToPointer<void>(sizeof(Vector2)));
    glEnableVertexAttribArray(1);
    
    m_PrimitiveColoredShader->Use();

    glDrawArrays(GL_LINES, 0, 2);

    m_PrimitiveColoredShader->Unuse();

    glBindVertexArray(0);
}

void Draw::Triangle(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Color& color)
{
    TriangleInternal(point1, point2, point3, color, false);
}

void Draw::Triangle(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Color& color1,
    const Color& color2,
    const Color& color3
)
{
    TriangleInternal(point1, point2, point3, color1, color2, color3, false);
}

void Draw::TriangleFilled(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Color& color)
{
    TriangleInternal(point1, point2, point3, color, true);
}

void Draw::TriangleFilled(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Color& color1,
    const Color& color2,
    const Color& color3
)
{
    TriangleInternal(point1, point2, point3, color1, color2, color3, true);
}

void Draw::Rectangle(const Vector2 position, const Vector2 size, const Color& color)
{
    RectangleInternal({ position, size }, color, false);
}

void Draw::Rectangle(const Mountain::Rectangle& rectangle, const Color& color)
{
    RectangleInternal(rectangle, color, false);
}

void Draw::Rectangle(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4, const Color& color)
{
    RectangleInternal(point1, point2, point3, point4, color, false);
}

void Draw::Rectangle(
    const Vector2 position,
    const Vector2 size,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4
)
{
    RectangleInternal({ position, size }, color1, color2, color3, color4, false);
}

void Draw::Rectangle(
    const Mountain::Rectangle& rectangle,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4
)
{
    RectangleInternal(rectangle, color1, color2, color3, color4, false);
}

void Draw::Rectangle(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Vector2 point4,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4
)
{
    RectangleInternal(point1, point2, point3, point4, color1, color2, color3, color4, false);
}

void Draw::RectangleFilled(const Vector2 position, const Vector2 size, const Color& color)
{
    RectangleInternal({ position, size }, color, true);
}

void Draw::RectangleFilled(const Mountain::Rectangle& rectangle, const Color& color)
{
    RectangleInternal(rectangle, color, true);
}

void Draw::RectangleFilled(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4, const Color& color)
{
    RectangleInternal(point1, point2, point3, point4, color, false);
}

void Draw::RectangleFilled(
    const Vector2 position,
    const Vector2 size,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4
)
{
    RectangleInternal({ position, size }, color1, color2, color3, color4, true);
}

void Draw::RectangleFilled(
    const Mountain::Rectangle& rectangle,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4
)
{
    RectangleInternal(rectangle, color1, color2, color3, color4, true);
}

void Draw::RectangleFilled(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Vector2 point4,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4
)
{
    RectangleInternal(point1, point2, point3, point4, color1, color2, color3, color4, false);
}

void Draw::Circle(const Vector2 position, const float_t radius, const Color& color, const uint32_t segments)
{
    CircleInternal(position, radius, color, segments, false);
}

void Draw::CircleDotted(const Vector2 position, const float_t radius, const Color& color, const uint32_t segments)
{
    CircleInternal(position, radius, color, segments, true);
}

void Draw::CircleFilled(const Vector2 position, const float_t radius, const Color& color)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    
    std::array p = {
        position - Vector2::One() * radius,
        position + Vector2(1.f, -1.f) * radius,
        position + Vector2::One() * radius,
        position + Vector2(-1.f, 1.f) * radius
    };
    
    for (Vector2& v : p)
        v = cameraMatrix * v;
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p.data(), GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);
    
    m_CircleShader->Use();
    m_CircleShader->SetUniform("position", position);
    m_CircleShader->SetUniform("radius", radius);
    m_CircleShader->SetUniform("color", color);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    m_CircleShader->Unuse();

    glBindVertexArray(0);
}

void Draw::Texture(
    const Mountain::Texture& texture,
    const Vector2 position,
    const Vector2 scale,
    const float_t rotation,
    const Vector2 uv0,
    const Vector2 uv1,
    const Color& color,
    const uint8_t flipFlags
)
{
    TextureInternal(texture.GetId(), texture.GetSize(), *m_TextureShader, position, scale, rotation, uv0, uv1, color, flipFlags);
}

void Draw::Text(const Font& font, const std::string_view text, Vector2 position, const float_t scale, const Color& color)
{
    glBindVertexArray(m_TextVao);

    m_TextShader->Use();
    m_TextShader->SetUniform("color", color);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    for (const char_t c : text)
    {
        const Font::Character& character = font.m_Characters.at(c);

        const Vector2 pos = cameraMatrix * Vector2(
            position.x + static_cast<float_t>(character.bearing.x) * scale,
            position.y - static_cast<float_t>(character.bearing.y) * scale
        );
        const Vector2 size = cameraMatrix * (character.size * scale);

        const std::array vertices = {
            pos.x,          pos.y,           0.f, 0.f,
            pos.x + size.x, pos.y,           1.f, 0.f,
            pos.x + size.x, pos.y + size.y,  1.f, 1.f,
            pos.x,          pos.y + size.y,  0.f, 1.f
        };

        glBindTexture(GL_TEXTURE_2D, character.textureId);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_TextVbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        position.x += static_cast<float_t>(character.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_TextShader->Unuse();
    
    glBindVertexArray(0);
}

void Draw::RenderTarget(
    const Mountain::RenderTarget& renderTarget,
    const Vector2 position,
    const Vector2 scale,
    const float_t rotation,
    const Vector2 uv0,
    const Vector2 uv1,
    const Color& color,
    const uint8_t flipFlags
)
{
    TextureInternal(
        renderTarget.GetTextureId(),
        renderTarget.GetSize(),
        *m_PostProcessingShader,
        position,
        scale,
        rotation,
        uv0,
        uv1,
        color,
        flipFlags
    );
}

void Draw::Initialize()
{
    glGenBuffers(4, &m_RectangleEbo);
    glGenVertexArrays(3, &m_Vao);

    // Rectangle EBO
    constexpr std::array<uint32_t, 6> indexData = {
        0, 1, 2,
        2, 3, 0
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData.data(), GL_STATIC_DRAW);

    // Text VBO/VAO
    glBindVertexArray(m_TextVao);
    glBindBuffer(GL_ARRAY_BUFFER, m_TextVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * 6, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), nullptr);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    

    m_PrimitiveShader = ResourceManager::Get<Shader>("primitive");
    m_PrimitiveColoredShader = ResourceManager::Get<Shader>("primitive_colored");
    m_CircleShader = ResourceManager::Get<Shader>("circle");
    m_TextureShader = ResourceManager::Get<Shader>("texture");
    m_TextShader = ResourceManager::Get<Shader>("text");

    m_PostProcessingShader = ResourceManager::Get<Shader>("post_processing");
}

void Draw::Shutdown()
{
    glDeleteBuffers(4, &m_RectangleEbo);
    glDeleteVertexArrays(3, &m_Vao);
}

void Draw::SetProjectionMatrix(const Matrix& projection)
{
    m_PrimitiveShader->Use();
    m_PrimitiveShader->SetUniform("projection", projection);
    m_PrimitiveColoredShader->Use();
    m_PrimitiveColoredShader->SetUniform("projection", projection);
    m_CircleShader->Use();
    m_CircleShader->SetUniform("projection", projection);
    m_TextShader->Use();
    m_TextShader->SetUniform("projection", projection);
    m_TextShader->Unuse();
    
    m_Projection = projection;
}

void Draw::TriangleInternal(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Color& color,
    const bool_t filled
)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    
    std::array p = { point1, point2, point3 };
    
    for (Vector2& v : p)
        v = cameraMatrix * v;
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);

    m_PrimitiveShader->Use();
    m_PrimitiveShader->SetUniform("color", color);

    glDrawArrays(filled ? GL_TRIANGLES : GL_LINE_LOOP, 0, 3);

    m_PrimitiveShader->Unuse();

    glBindVertexArray(0);
}

void Draw::TriangleInternal(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const bool_t filled
)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    
    const Vector2 p1 = cameraMatrix * point1;
    const Vector2 p2 = cameraMatrix * point2;
    const Vector2 p3 = cameraMatrix * point3;
    
    const std::array p = {
        p1.x, p1.y,
        color1.r, color1.g, color1.b, color1.a,
        p2.x, p2.y,
        color2.r, color2.g, color2.b, color2.a,
        p3.x, p3.y,
        color3.r, color3.g, color3.b, color3.a
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), Utils::IntToPointer<void>(sizeof(Vector2)));
    glEnableVertexAttribArray(1);
    
    m_PrimitiveColoredShader->Use();

    glDrawArrays(filled ? GL_TRIANGLES : GL_LINE_LOOP, 0, 3);

    m_PrimitiveColoredShader->Unuse();

    glBindVertexArray(0);
}

void Draw::RectangleInternal(const Mountain::Rectangle& rectangle, const Color& color, const bool_t filled)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    if (filled)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    
    std::array p = {
        rectangle.position,
        rectangle.position + Vector2::UnitX() * rectangle.Width(),
        rectangle.position + rectangle.size,
        rectangle.position + Vector2::UnitY() * rectangle.Height()
    };
    
    for (Vector2& v : p)
        v = cameraMatrix * v;
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);

    m_PrimitiveShader->Use();
    m_PrimitiveShader->SetUniform("color", color);

    if (filled)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_LINE_LOOP, 0, 4);

    m_PrimitiveShader->Unuse();

    glBindVertexArray(0);
}

void Draw::RectangleInternal(
    const Mountain::Rectangle& rectangle,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4,
    const bool_t filled
)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    if (filled)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    
    const Vector2 p1 = cameraMatrix * Vector2(rectangle.Left(), rectangle.Bottom());
    const Vector2 p2 = cameraMatrix * Vector2(rectangle.Right(), rectangle.Bottom());
    const Vector2 p3 = cameraMatrix * Vector2(rectangle.Right(), rectangle.Top());
    const Vector2 p4 = cameraMatrix * Vector2(rectangle.Left(), rectangle.Top());
    
    const std::array p = {
        p1.x, p1.y,
        color1.r, color1.g, color1.b, color1.a,
        p2.x, p2.y,
        color2.r, color2.g, color2.b, color2.a,
        p3.x, p3.y,
        color3.r, color3.g, color3.b, color3.a,
        p4.x, p4.y,
        color4.r, color4.g, color4.b, color4.a
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), Utils::IntToPointer<void>(sizeof(Vector2)));
    glEnableVertexAttribArray(1);
    
    m_PrimitiveColoredShader->Use();

    if (filled)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_LINE_LOOP, 0, 4);

    m_PrimitiveColoredShader->Unuse();

    glBindVertexArray(0);
}

void Draw::RectangleInternal(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Vector2 point4,
    const Color& color,
    const bool_t filled
)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    if (filled)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    
    std::array p = { point1, point2, point3, point4 };
    
    for (Vector2& v : p)
        v = cameraMatrix * v;
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);

    m_PrimitiveShader->Use();
    m_PrimitiveShader->SetUniform("color", color);

    if (filled)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_LINE_LOOP, 0, 4);

    m_PrimitiveShader->Unuse();

    glBindVertexArray(0);
}

void Draw::RectangleInternal(
    const Vector2 point1,
    const Vector2 point2,
    const Vector2 point3,
    const Vector2 point4,
    const Color& color1,
    const Color& color2,
    const Color& color3,
    const Color& color4,
    const bool_t filled
)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    if (filled)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    
    const Vector2 p1 = cameraMatrix * point1;
    const Vector2 p2 = cameraMatrix * point2;
    const Vector2 p3 = cameraMatrix * point3;
    const Vector2 p4 = cameraMatrix * point4;
    
    const std::array p = {
        p1.x, p1.y,
        color1.r, color1.g, color1.b, color1.a,
        p2.x, p2.y,
        color2.r, color2.g, color2.b, color2.a,
        p3.x, p3.y,
        color3.r, color3.g, color3.b, color3.a,
        p4.x, p4.y,
        color4.r, color4.g, color4.b, color4.a
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vector2) + sizeof(Color), Utils::IntToPointer<void>(sizeof(Vector2)));
    glEnableVertexAttribArray(1);

    m_PrimitiveColoredShader->Use();

    if (filled)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_LINE_LOOP, 0, 4);

    m_PrimitiveColoredShader->Unuse();

    glBindVertexArray(0);
}

void Draw::CircleInternal(const Vector2 position, const float_t radius, const Color& color, uint32_t segments, const bool_t dotted)
{
    if (segments <= 2)
        throw std::invalid_argument("Cannot draw a circle with less than 3 segments");

    if (dotted)
        segments *= 2;
    
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    
    std::vector<Vector2> p(segments);
    const float_t angle = Calc::TwoPi / static_cast<float_t>(segments);

    for (uint32_t i = 0; i < segments; i++)
    {
        const float_t fi = static_cast<float_t>(i);
        p[i] = Vector2(position.x + std::cos(angle * fi) * radius, position.y + std::sin(angle * fi) * radius);
    }
    
    for (Vector2& v : p)
        v = cameraMatrix * v;

    glBufferData(GL_ARRAY_BUFFER, static_cast<int64_t>(p.size() * sizeof(decltype(p)::value_type)), p.data(), GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);
    
    m_PrimitiveShader->Use();
    m_PrimitiveShader->SetUniform("color", color);

    glDrawArrays(dotted ? GL_LINES : GL_LINE_LOOP, 0, static_cast<int32_t>(segments));

    m_PrimitiveShader->Unuse();

    glBindVertexArray(0);
}

void Draw::TextureInternal(
    const uint32_t textureId,
    const Vector2i textureSize,
    const Shader& shader,
    const Vector2 position,
    const Vector2 scale,
    const float_t rotation,
    const Vector2 uv0,
    const Vector2 uv1,
    const Color& color,
    const uint8_t flipFlags
)
{
    if (uv0.x > uv1.x || uv0.y > uv1.y)
        throw std::invalid_argument("UV0 cannot be greater than UV1");
    
    glBindVertexArray(m_ImageVao);
    glBindBuffer(GL_ARRAY_BUFFER, m_ImageVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);

    const Vector2 uvDiff = uv1 - uv0;
    Vector2 lowerUv = uv0, higherUv = uv1;

    if (flipFlags & DrawTextureFlipping::Horizontal)
    {
        higherUv.x = lowerUv.x;
        lowerUv.x += uvDiff.x;
    }

    if (flipFlags & DrawTextureFlipping::Vertical)
    {
        higherUv.y = lowerUv.y;
        lowerUv.y += uvDiff.y;
    }

    const std::array vertices = {
        // pos          // UVs
        -1.f, -1.f,     lowerUv.x,  lowerUv.y,
         1.f, -1.f,     higherUv.x, lowerUv.y,
         1.f,  1.f,     higherUv.x, higherUv.y,
        -1.f,  1.f,     lowerUv.x,  higherUv.y
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), nullptr);
    glEnableVertexAttribArray(0);
    
    shader.Use();
    
    shader.SetUniform("projection", m_Projection * cameraMatrix);
    
    shader.SetUniform("halfImagePixelSize", textureSize * uvDiff * 0.5f);
    shader.SetUniform("position", position);
    shader.SetUniform("scale", scale);
    shader.SetUniform("rotation", rotation);

    shader.SetUniform("horizontalFlip", flipFlags & DrawTextureFlipping::Horizontal);
    shader.SetUniform("verticalFlip", flipFlags & DrawTextureFlipping::Vertical);

    Matrix2 diagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::Diagonal)
    {
        constexpr Matrix2 m(1.f, 1.f, -1.f, 1.f);
        diagonalFlip = m * Matrix2::Scaling({ 1.f, -1.f }) * m.Inverted();
    }
    shader.SetUniform("diagonalFlip", diagonalFlip);

    Matrix2 antiDiagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::AntiDiagonal)
    {
        constexpr Matrix2 m(-1.f, 1.f, 1.f, 1.f);
        antiDiagonalFlip = m * Matrix2::Scaling({ 1.f, -1.f }) * m.Inverted();
    }
    shader.SetUniform("antiDiagonalFlip", antiDiagonalFlip);
    
    shader.SetUniform("color", color);
    
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    
    shader.Unuse();

    glBindVertexArray(0);
}
