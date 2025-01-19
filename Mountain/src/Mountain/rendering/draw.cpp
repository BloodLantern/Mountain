#include "Mountain/rendering/draw.hpp"

#include <glad/glad.h>

#include <ImGui/imgui_stdlib.h>

#include "Mountain/globals.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/resource/shader.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

void Draw::Clear(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw::Point(Vector2 position, const Color& color)
{
    m_DrawList.point.Emplace(position, color);
    m_DrawList.AddCommand(DrawDataType::Point);
}

void Draw::Line(const Vector2 point1, const Vector2 point2, const Color& color)
{
    m_DrawList.line.Emplace(point1, point2, color);
    m_DrawList.AddCommand(DrawDataType::Line);
}

void Draw::Line(const Vector2 point1, const Vector2 point2, const Color& color1, const Color& color2)
{
    m_DrawList.lineColored.Emplace(point1, point2, color1, color2);
    m_DrawList.AddCommand(DrawDataType::LineColored);
}

void Draw::Triangle(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Color& color)
{
    m_DrawList.triangle.Emplace(point1, point2, point3, color);
    m_DrawList.AddCommand(DrawDataType::Triangle);
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
    m_DrawList.triangleColored.Emplace(point1, point2, point3, color1, color2, color3);
    m_DrawList.AddCommand(DrawDataType::TriangleColored);
}

void Draw::TriangleFilled(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Color& color)
{
    m_DrawList.triangleFilled.Emplace(point1, point2, point3, color);
    m_DrawList.AddCommand(DrawDataType::TriangleFilled);
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
    m_DrawList.triangleColoredFilled.Emplace(point1, point2, point3, color1, color2, color3);
    m_DrawList.AddCommand(DrawDataType::TriangleColoredFilled);
}

void Draw::Rectangle(const Vector2 position, const Vector2 size, const Color& color) { Rectangle({ position, size }, color); }

void Draw::Rectangle(const Mountain::Rectangle& rectangle, const Color& color)
{
    m_DrawList.rectangle.Emplace(
        Matrix::Translation(static_cast<Vector3>(rectangle.position)) * Matrix::Scaling({ rectangle.size.x, rectangle.size.y, 1.f }),
        color
    );
    m_DrawList.AddCommand(DrawDataType::Rectangle);
}

void Draw::RectangleFilled(const Vector2 position, const Vector2 size, const Color& color) { RectangleFilled({ position, size }, color); }

void Draw::RectangleFilled(const Mountain::Rectangle& rectangle, const Color& color)
{
    m_DrawList.rectangleFilled.Emplace(
        Matrix::Translation(static_cast<Vector3>(rectangle.position)) * Matrix::Scaling(
            { rectangle.size.x, rectangle.size.y, 1.f }
        ),
        color
    );
    m_DrawList.AddCommand(DrawDataType::RectangleFilled);
}

void Draw::Circle(const Vector2 center, const float_t radius, const Vector2 scale, const Color& color) { CircleInternal(center, radius, false, scale, color); }

void Draw::CircleFilled(const Vector2 center, const float_t radius, const Vector2 scale, const Color& color) { CircleInternal(center, radius, true, scale, color); }

void Draw::Arc(
    const Vector2 center,
    const float_t radius,
    const float_t startingAngle,
    const float_t deltaAngle,
    const Vector2 scale,
    const Color& color
)
{
    ArcInternal(center, radius, startingAngle, deltaAngle, false, scale, color);
}

void Draw::ArcFilled(
    const Vector2 center,
    const float_t radius,
    const float_t startingAngle,
    const float_t deltaAngle,
    const Vector2 scale,
    const Color& color
)
{
    ArcInternal(center, radius, startingAngle, deltaAngle, true, scale, color);
}

void Draw::Texture(
    const Mountain::Texture& texture,
    const Vector2 position,
    Vector2 scale,
    const float_t rotation,
    const Vector2 origin,
    const Vector2 uv0,
    const Vector2 uv1,
    const Color& color,
    const Meta::UnderlyingEnumType<DrawTextureFlipping> flipFlags
)
{
    if (uv0.x > uv1.x || uv0.y > uv1.y)
        throw std::invalid_argument{ "UV0 cannot be greater than UV1" };

    if (origin.x < 0.f || origin.x > 1.f || origin.y < 0.f || origin.y > 1.f)
        throw std::invalid_argument{ "Origin must be in the range [{ 0, 0 }, { 1, 1 }]" };

    Vector2 uvDiff = uv1 - uv0;
    Vector2 lowerUv = uv0;

    if (flipFlags & DrawTextureFlipping::Horizontal)
        scale.x *= -1.f;

    if (flipFlags & DrawTextureFlipping::Vertical)
        scale.y *= -1.f;

    Matrix2 diagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::Diagonal)
    {
        static constexpr Matrix2 M(1.f, 1.f, -1.f, 1.f);
        diagonalFlip = M * Matrix2::Scaling({ 1.f, -1.f }) * M.Inverted();
    }

    Matrix2 antiDiagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::AntiDiagonal)
    {
        static constexpr Matrix2 M(-1.f, 1.f, 1.f, 1.f);
        antiDiagonalFlip = M * Matrix2::Scaling({ 1.f, -1.f }) * M.Inverted();
    }

    const Vector2i textureSize = texture.GetSize();
    Matrix transformation = Matrix::Translation(static_cast<Vector3>(position))
        * Matrix::RotationZ(rotation)
        * Matrix::Translation(static_cast<Vector3>(-textureSize * origin * scale))
        * static_cast<Matrix>(antiDiagonalFlip)
        * static_cast<Matrix>(diagonalFlip)
        * Matrix::Scaling({ static_cast<float_t>(textureSize.x) * Calc::Abs(uvDiff.x) * scale.x, static_cast<float_t>(textureSize.y) * Calc::Abs(uvDiff.y) * scale.y, 1.f });

    Matrix uvProjection = Matrix::Translation(static_cast<Vector3>(lowerUv)) * Matrix::Scaling(static_cast<Vector3>(uvDiff));

    m_DrawList.texture.Emplace(transformation, uvProjection, color);

    if (!m_DrawList.textureId.Empty() && m_DrawList.textureId.Back() == texture.GetId())
    {
        auto& lastCommand = m_DrawList.commands.Back();
        if (lastCommand.type == DrawDataType::Texture)
        {
            lastCommand.count++;
            return;
        }
    }
    
    m_DrawList.textureId.Add(texture.GetId());
    m_DrawList.commands.Emplace(DrawDataType::Texture, 1ull);
}

void Draw::Text(const Font& font, const std::string& text, const Vector2 position, const float_t scale, const Color& color)
{
    m_DrawList.text.Emplace(&font, text, position, scale, color);
    m_DrawList.AddCommand(DrawDataType::Text);
}

void Draw::RenderTarget(
    const Mountain::RenderTarget& renderTarget,
    const Vector2 position,
    const Vector2 scale,
    const float_t rotation,
    const Vector2 uv0,
    const Vector2 uv1,
    const Color& color,
    const Meta::UnderlyingEnumType<DrawTextureFlipping> flipFlags
)
{
    if (uv0.x > uv1.x || uv0.y > uv1.y)
        throw std::invalid_argument("UV0 cannot be greater than UV1");

    Vector2 uvDiff = uv1 - uv0;
    Vector2 lowerUv = uv0;

    if (flipFlags & DrawTextureFlipping::Horizontal)
    {
        lowerUv.x += uvDiff.x;
        uvDiff.x = -uvDiff.x;
    }

    if (flipFlags & DrawTextureFlipping::Vertical)
    {
        lowerUv.y += uvDiff.y;
        uvDiff.y = -uvDiff.y;
    }

    Matrix2 diagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::Diagonal)
    {
        static constexpr Matrix2 M(1.f, 1.f, -1.f, 1.f);
        diagonalFlip = M * Matrix2::Scaling({ 1.f, -1.f }) * M.Inverted();
    }

    Matrix2 antiDiagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::AntiDiagonal)
    {
        static constexpr Matrix2 M(-1.f, 1.f, 1.f, 1.f);
        antiDiagonalFlip = M * Matrix2::Scaling({ 1.f, -1.f }) * M.Inverted();
    }

    const Vector2i textureSize = renderTarget.GetSize();
    Matrix transformation = Matrix::Translation(static_cast<Vector3>(position))
        * Matrix::RotationZ(rotation)
        * static_cast<Matrix>(antiDiagonalFlip)
        * static_cast<Matrix>(diagonalFlip)
        * Matrix::Scaling({ static_cast<float_t>(textureSize.x) * uvDiff.x * scale.x, static_cast<float_t>(textureSize.y) * uvDiff.y * scale.y, 1.f });

    Matrix uvProjection = Matrix::Translation(static_cast<Vector3>(lowerUv)) * Matrix::Scaling(static_cast<Vector3>(uvDiff));

    m_DrawList.renderTarget.Emplace(&renderTarget, transformation, uvProjection, scale, color);
    m_DrawList.AddCommand(DrawDataType::RenderTarget);
}

void Draw::Flush()
{
    size_t pointIndex = 0;
    size_t lineIndex = 0, lineColoredIndex = 0;
    size_t triangleIndex = 0, triangleColoredIndex = 0, triangleFilledIndex = 0, triangleColoredFilledIndex = 0;
    size_t rectangleIndex = 0, rectangleFilledIndex = 0;
    size_t circleIndex = 0;
    size_t arcIndex = 0;
    size_t textureIndex = 0, textureIdIndex = 0;
    size_t textIndex = 0;
    size_t renderTargetIndex = 0;

    const List<CommandData>& commands = m_DrawList.commands;
    for (size_t i = 0; i < commands.GetSize(); i++)
    {
        const CommandData& command = commands[i];
        const size_t count = command.count;

        switch (command.type)
        {
            case DrawDataType::Point:
                RenderPointData(m_DrawList.point, pointIndex, count);
                pointIndex += count;
                break;

            case DrawDataType::Line:
                RenderLineData(m_DrawList.line, lineIndex, count);
                lineIndex += count;
                break;

            case DrawDataType::LineColored:
                RenderLineColoredData(m_DrawList.lineColored, lineColoredIndex, count);
                lineColoredIndex += count;
                break;

            case DrawDataType::Triangle:
                RenderTriangleData(m_DrawList.triangle, false, triangleIndex, count);
                triangleIndex += count;
                break;

            case DrawDataType::TriangleColored:
                RenderTriangleColoredData(m_DrawList.triangleColored, false, triangleColoredIndex, count);
                triangleColoredIndex += count;
                break;

            case DrawDataType::TriangleFilled:
                RenderTriangleData(m_DrawList.triangleFilled, true, triangleFilledIndex, count);
                triangleFilledIndex += count;
                break;

            case DrawDataType::TriangleColoredFilled:
                RenderTriangleColoredData(m_DrawList.triangleColoredFilled, true, triangleColoredFilledIndex, count);
                triangleColoredFilledIndex += count;
                break;

            case DrawDataType::Rectangle:
                RenderRectangleData(m_DrawList.rectangle, false, rectangleIndex, count);
                rectangleIndex += count;
                break;

            case DrawDataType::RectangleFilled:
                RenderRectangleData(m_DrawList.rectangleFilled, true, rectangleFilledIndex, count);
                rectangleFilledIndex += count;
                break;

            case DrawDataType::Circle:
                RenderCircleData(m_DrawList.circle, circleIndex, count);
                circleIndex += count;
                break;

            case DrawDataType::Arc:
                RenderArcData(m_DrawList.arc, arcIndex, count);
                arcIndex += count;
                break;

            case DrawDataType::Texture:
                RenderTextureData(m_DrawList.texture, m_DrawList.textureId[textureIdIndex], textureIndex, count);
                textureIndex += count;
                textureIdIndex++;
                break;

            case DrawDataType::Text:
                RenderTextData(m_DrawList.text, textIndex, count);
                textIndex += count;
                break;

            case DrawDataType::RenderTarget:
                RenderRenderTargetData(m_DrawList.renderTarget, renderTargetIndex, count);
                renderTargetIndex += count;
                break;
        }
    }

    m_DrawList.Clear();
}

void Draw::DrawList::AddCommand(DrawDataType type)
{
    if (!commands.Empty())
    {
        CommandData& lastCommand = commands.Back();
        if (lastCommand.type == type)
        {
            lastCommand.count++;
            return;
        }
    }

    commands.Emplace(type, 1ull);
}

void Draw::DrawList::Clear()
{
    point.Clear();
    line.Clear();
    lineColored.Clear();
    triangle.Clear();
    triangleColoredFilled.Clear();
    triangleFilled.Clear();
    triangleColored.Clear();
    rectangle.Clear();
    rectangleFilled.Clear();
    circle.Clear();
    arc.Clear();
    texture.Clear();
    textureId.Clear();
    text.Clear();
    renderTarget.Clear();

    commands.Clear();
}

void Draw::Initialize()
{
    glCreateBuffers(7, &m_RectangleEbo);
    glCreateVertexArrays(11, &m_PointVao);

#ifdef _DEBUG
    glObjectLabel(GL_BUFFER, m_RectangleEbo, -1, "Rectangle EBO");
    glObjectLabel(GL_BUFFER, m_Vbo, -1, "Global VBO");
    glObjectLabel(GL_BUFFER, m_RectangleVbo, -1, "Rectangle VBO");
    glObjectLabel(GL_BUFFER, m_TextureVbo, -1, "Texture VBO");
    glObjectLabel(GL_BUFFER, m_TextVbo, -1, "Text VBO");
    glObjectLabel(GL_BUFFER, m_RenderTargetVbo, -1, "RenderTarget VBO");
    glObjectLabel(GL_BUFFER, m_RenderTargetSsbo, -1, "RenderTarget SSBO");

    glObjectLabel(GL_VERTEX_ARRAY, m_LineVao, -1, "Line VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_LineColoredVao, -1, "Line Colored VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_TriangleVao, -1, "Triangle VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_TriangleColoredVao, -1, "Triangle Colored VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_RectangleVao, -1, "Rectangle VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_CircleVao, -1, "Circle VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_ArcVao, -1, "Arc VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_TextureVao, -1, "Texture VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_TextVao, -1, "Text VAO");
    glObjectLabel(GL_VERTEX_ARRAY, m_RenderTargetVao, -1, "RenderTarget VAO");
#endif

    InitializePointBuffers();
    InitializeLineBuffers();
    InitializeLineColoredBuffers();
    InitializeTriangleBuffers();
    InitializeTriangleColoredBuffers();
    InitializeRectangleBuffers();
    InitializeCircleBuffers();
    InitializeArcBuffers();
    InitializeTextureBuffers();
    InitializeTextBuffers();
    InitializeRenderTargetBuffers();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Draw::LoadResources()
{
    const std::string basePath = Utils::GetBuiltinShadersPath();

    m_PointShader = ResourceManager::Get<Shader>(basePath + "point");
    m_LineShader = ResourceManager::Get<Shader>(basePath + "line");
    m_LineColoredShader = ResourceManager::Get<Shader>(basePath + "line_colored");
    m_TriangleShader = ResourceManager::Get<Shader>(basePath + "triangle");
    m_TriangleColoredShader = ResourceManager::Get<Shader>(basePath + "triangle_colored");
    m_RectangleShader = ResourceManager::Get<Shader>(basePath + "rectangle");
    m_CircleShader = ResourceManager::Get<Shader>(basePath + "circle");
    m_ArcShader = ResourceManager::Get<Shader>(basePath + "arc");
    
    m_TextureShader = ResourceManager::Get<Shader>(basePath + "texture");
    m_TextShader = ResourceManager::Get<Shader>(basePath + "text");

    m_RenderTargetShader = ResourceManager::Get<Shader>(basePath + "render_target");
}

void Draw::Shutdown()
{
    glDeleteBuffers(7, &m_RectangleEbo);
    glDeleteVertexArrays(11, &m_PointVao);
}

void Draw::InitializePointBuffers()
{
    glBindVertexArray(m_PointVao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Position
    SetVertexAttribute(index, 2, sizeof(PointData), offset, 1);
    // Color
    SetVertexAttribute(++index, 4, sizeof(PointData), offset += sizeof(Vector2), 1);
}

void Draw::InitializeLineBuffers()
{
    glBindVertexArray(m_LineVao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    SetVertexAttribute(index, 2, sizeof(LineData), offset, 1);
    SetVertexAttribute(++index, 2, sizeof(LineData), offset += sizeof(Vector2), 1);
    // Color
    SetVertexAttribute(++index, 4, sizeof(LineData), offset += sizeof(Vector2), 1);
}

void Draw::InitializeLineColoredBuffers()
{
    glBindVertexArray(m_LineColoredVao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    SetVertexAttribute(index, 2, sizeof(LineColoredData), offset, 1);
    SetVertexAttribute(++index, 2, sizeof(LineColoredData), offset += sizeof(Vector2), 1);
    // Colors
    SetVertexAttribute(++index, 4, sizeof(LineColoredData), offset += sizeof(Vector2), 1);
    SetVertexAttribute(++index, 4, sizeof(LineColoredData), offset += sizeof(Color), 1);
}

void Draw::InitializeTriangleBuffers()
{
    glBindVertexArray(m_TriangleVao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    SetVertexAttribute(index, 2, sizeof(TriangleData), offset, 1);
    SetVertexAttribute(++index, 2, sizeof(TriangleData), offset += sizeof(Vector2), 1);
    SetVertexAttribute(++index, 2, sizeof(TriangleData), offset += sizeof(Vector2), 1);
    // Color
    SetVertexAttribute(++index, 4, sizeof(TriangleData), offset += sizeof(Vector2), 1);
}

void Draw::InitializeTriangleColoredBuffers()
{
    glBindVertexArray(m_TriangleColoredVao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    SetVertexAttribute(index, 2, sizeof(TriangleColoredData), offset, 1);
    SetVertexAttribute(++index, 2, sizeof(TriangleColoredData), offset += sizeof(Vector2), 1);
    SetVertexAttribute(++index, 2, sizeof(TriangleColoredData), offset += sizeof(Vector2), 1);
    // Colors
    SetVertexAttribute(++index, 4, sizeof(TriangleColoredData), offset += sizeof(Vector2), 1);
    SetVertexAttribute(++index, 4, sizeof(TriangleColoredData), offset += sizeof(Color), 1);
    SetVertexAttribute(++index, 4, sizeof(TriangleColoredData), offset += sizeof(Color), 1);
}

void Draw::InitializeRectangleBuffers()
{
    constexpr std::array vertexData = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };
    
    constexpr std::array<uint32_t, 6> indexData = {
        0, 1, 2,
        2, 3, 0
    };
    
    glBindVertexArray(m_RectangleVao);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_RectangleVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData.data(), GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData.data(), GL_STATIC_DRAW);

    // VAO
    uint32_t index = 0;
    // Vertex position
    SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    SetVertexAttribute(++index, 4, sizeof(RectangleData), offset, 1);
    SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
    // Color
    SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
}

void Draw::InitializeCircleBuffers()
{
    glBindVertexArray(m_CircleVao);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_RectangleVbo);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);

    // VAO
    uint32_t index = 0;
    // Vertex position
    SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    SetVertexAttribute(++index, 4, sizeof(CircleData), offset, 1);
    SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector4), 1);
    // Center
    SetVertexAttribute(++index, 2, sizeof(CircleData), offset += sizeof(Vector4), 1);
    // Radius
    SetVertexAttribute(++index, 1, sizeof(CircleData), offset += sizeof(Vector2), 1);
    // Scale
    SetVertexAttribute(++index, 2, sizeof(CircleData), offset += sizeof(float_t), 1);
    // Color
    SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector2), 1);
    // Filled
    SetVertexAttributeInt(++index, 1, sizeof(CircleData), offset += sizeof(Color), 1);
}

void Draw::InitializeArcBuffers()
{
    glBindVertexArray(m_ArcVao);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_RectangleVbo);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);

    // VAO
    uint32_t index = 0;
    // Vertex position
    SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    SetVertexAttribute(++index, 4, sizeof(ArcData), offset, 1);
    SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector4), 1);
    // Center
    SetVertexAttribute(++index, 2, sizeof(ArcData), offset += sizeof(Vector4), 1);
    // Radius
    SetVertexAttribute(++index, 1, sizeof(ArcData), offset += sizeof(Vector2), 1);
    // Starting angle
    SetVertexAttribute(++index, 1, sizeof(ArcData), offset += sizeof(float_t), 1);
    // Delta angle
    SetVertexAttribute(++index, 1, sizeof(ArcData), offset += sizeof(float_t), 1);
    // Scale
    SetVertexAttribute(++index, 2, sizeof(ArcData), offset += sizeof(float_t), 1);
    // Color
    SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector2), 1);
    // Filled
    SetVertexAttributeInt(++index, 1, sizeof(ArcData), offset += sizeof(Color), 1);
}

void Draw::InitializeTextureBuffers()
{
    constexpr std::array vertexData = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };
    
    glBindVertexArray(m_TextureVao);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_TextureVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData.data(), GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);

    // VAO
    uint32_t index = 0;
    // Vertex position
    SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset, 1);
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    // UV projection Matrix
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    // Color
    SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
}

void Draw::InitializeTextBuffers()
{
    glBindVertexArray(m_TextVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_TextVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * 4, nullptr, GL_DYNAMIC_DRAW);

    SetVertexAttribute(0, 4, sizeof(Vector4), 0);
}

void Draw::InitializeRenderTargetBuffers()
{
    constexpr std::array vertexData = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };
    
    glBindVertexArray(m_RenderTargetVao);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderTargetVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData.data(), GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);

    // VAO
    // Vertex position
    SetVertexAttribute(0, 2, sizeof(Vector2), 0, 0);
}

void Draw::SetProjectionMatrix(const Matrix& newProjectionMatrix)
{
    m_ProjectionMatrix = newProjectionMatrix;
    
    UpdateShaderMatrices();
}

void Draw::SetCamera(const Matrix& newCameraMatrix, const Vector2 newCameraScale)
{
    m_CameraMatrix = newCameraMatrix;
    m_CameraScale = newCameraScale;
    
    UpdateShaderMatrices();
}

void Draw::UpdateShaderMatrices()
{
    const Matrix proj = m_ProjectionMatrix * m_CameraMatrix;
    
    m_PointShader->SetUniform("projection", proj);
    m_LineShader->SetUniform("projection", proj);
    m_LineColoredShader->SetUniform("projection", proj);
    m_TriangleShader->SetUniform("projection", proj);
    m_TriangleColoredShader->SetUniform("projection", proj);
    m_RectangleShader->SetUniform("projection", proj);
    m_CircleShader->SetUniform("projection", proj);
    m_ArcShader->SetUniform("projection", proj);
    m_TextureShader->SetUniform("projection", proj);
    
    m_TextShader->SetUniform("projection", proj);
    
    m_CircleShader->SetUniform("camera", m_CameraMatrix);
    m_CircleShader->SetUniform("cameraScale", m_CameraScale);
    m_ArcShader->SetUniform("camera", m_CameraMatrix);
    m_ArcShader->SetUniform("cameraScale", m_CameraScale);
}

void Draw::CircleInternal(const Vector2 center, const float_t radius, const bool_t filled, const Vector2 scale, const Color& color)
{
    m_DrawList.circle.Emplace(
        Matrix::Translation(static_cast<Vector3>(center - scale * radius * m_CameraScale))
            * Matrix::Scaling({ radius * scale.x * 2.f * m_CameraScale.x, radius * scale.y * 2.f * m_CameraScale.y, 1.f }),
        center,
        radius,
        scale,
        color,
        filled
    );
    m_DrawList.AddCommand(DrawDataType::Circle);
}

void Draw::ArcInternal(
    Vector2 center,
    float_t radius,
    float_t startingAngle,
    float_t deltaAngle,
    bool_t filled,
    Vector2 scale,
    const Color& color
)
{
    m_DrawList.arc.Emplace(
        Matrix::Translation(static_cast<Vector3>(center - scale * radius * m_CameraScale))
            * Matrix::Scaling({ radius * scale.x * 2.f * m_CameraScale.x, radius * scale.y * 2.f * m_CameraScale.y, 1.f }),
        center,
        radius,
        startingAngle,
        deltaAngle,
        scale,
        color,
        filled
    );
    m_DrawList.AddCommand(DrawDataType::Arc);
}

void Draw::RenderPointData(const List<PointData>& points, const size_t index, const size_t count)
{
    if (points.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(PointData) * count), &points[index], GL_STREAM_DRAW);

    glBindVertexArray(m_PointVao);
    m_PointShader->Use();

    glDrawArraysInstanced(GL_POINTS, 0, 1, static_cast<GLsizei>(count));

    m_PointShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderLineData(const List<LineData>& lines, const size_t index, const size_t count)
{
    if (lines.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(LineData) * count), &lines[index], GL_STREAM_DRAW);
    
    glBindVertexArray(m_LineVao);
    m_LineShader->Use();

    glDrawArraysInstanced(GL_LINES, 0, 2, static_cast<GLsizei>(count));

    m_LineShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderLineColoredData(const List<LineColoredData>& linesColored, const size_t index, const size_t count)
{
    if (linesColored.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(LineColoredData) * count), &linesColored[index], GL_STREAM_DRAW);
    
    glBindVertexArray(m_LineColoredVao);
    m_LineColoredShader->Use();

    glDrawArraysInstanced(GL_LINES, 0, 2, static_cast<GLsizei>(count));

    m_LineColoredShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderTriangleData(const List<TriangleData>& triangles, const bool_t filled, const size_t index, const size_t count)
{
    if (triangles.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(TriangleData) * count), &triangles[index], GL_STREAM_DRAW);
    
    glBindVertexArray(m_TriangleVao);
    m_TriangleShader->Use();

    glDrawArraysInstanced(filled ? GL_TRIANGLES : GL_LINE_LOOP, 0, 3, static_cast<GLsizei>(count));

    m_TriangleShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderTriangleColoredData(const List<TriangleColoredData>& trianglesColored, const bool_t filled, const size_t index, const size_t count)
{
    if (trianglesColored.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(TriangleColoredData) * count), &trianglesColored[index], GL_STREAM_DRAW);
    
    glBindVertexArray(m_TriangleColoredVao);
    m_TriangleColoredShader->Use();

    glDrawArraysInstanced(filled ? GL_TRIANGLES : GL_LINE_LOOP, 0, 3, static_cast<GLsizei>(count));

    m_TriangleColoredShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderRectangleData(const List<RectangleData>& rectangles, const bool_t filled, const size_t index, const size_t count)
{
    if (rectangles.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(RectangleData) * count), &rectangles[index], GL_STREAM_DRAW);
    
    glBindVertexArray(m_RectangleVao);
    m_RectangleShader->Use();

    if (filled)
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(count));
    else
        glDrawArraysInstanced(GL_LINE_LOOP, 0, 4, static_cast<GLsizei>(count));

    m_RectangleShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderCircleData(const List<CircleData>& circles, const size_t index, const size_t count)
{
    if (circles.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(CircleData) * count), &circles[index], GL_STREAM_DRAW);
    
    glBindVertexArray(m_CircleVao);
    m_CircleShader->Use();

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(count));

    m_CircleShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderArcData(const List<ArcData>& arcs, const size_t index, const size_t count)
{
    if (arcs.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(ArcData) * count), &arcs[index], GL_STREAM_DRAW);

    glBindVertexArray(m_ArcVao);
    m_ArcShader->Use();

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(count));

    m_ArcShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderTextureData(const List<TextureData>& textures, const uint32_t textureId, const size_t index, const size_t count)
{
    if (textures.Empty())
        return;

    glNamedBufferData(m_Vbo, static_cast<GLsizeiptr>(sizeof(TextureData) * count), &textures[index], GL_STREAM_DRAW);
    
    glBindVertexArray(m_TextureVao);
    glBindTexture(GL_TEXTURE_2D, textureId);
    m_TextureShader->Use();

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(count));

    m_TextureShader->Unuse();
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Draw::RenderTextData(const List<TextData>& texts, const size_t index, const size_t count)
{
    glBindVertexArray(m_TextVao);
    m_TextShader->Use();

    for (size_t i = 0; i < count; i++)
    {
        const TextData& data = texts[index + i];
        
        m_TextShader->SetUniform("color", data.color);

        Vector2 offset = data.position + Vector2::UnitY() * data.font->CalcTextSize(data.text).y * data.scale;

        for (const char_t c : data.text)
        {
            const Font::Character& character = data.font->m_Characters.at(c);
            
            if (c != ' ') // Do not draw spaces
            {
                const Vector2 pos = Calc::Round(
                    {
                        offset.x + static_cast<float_t>(character.bearing.x) * data.scale,
                        offset.y - static_cast<float_t>(character.bearing.y) * data.scale
                    }
                );

                const Vector2 size = Calc::Round(character.size * data.scale);

                const std::array vertices = {
                    pos.x,          pos.y,           0.f, 0.f,
                    pos.x + size.x, pos.y,           1.f, 0.f,
                    pos.x + size.x, pos.y + size.y,  1.f, 1.f,
                    pos.x,          pos.y + size.y,  0.f, 1.f
                };

                    
                Graphics::BindTexture(character.texture);
                
                glNamedBufferSubData(m_TextVbo, 0, sizeof(vertices), vertices.data());
                
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            }
            
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            offset.x += static_cast<float_t>(character.advance >> 6) * data.scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    m_TextShader->Unuse();
    glBindVertexArray(0);
}

void Draw::RenderRenderTargetData(const List<RenderTargetData>& renderTargets, const size_t index, const size_t count)
{
    glBindVertexArray(m_RenderTargetVao);
    m_RenderTargetShader->Use();

    m_RenderTargetShader->SetUniform("projection", m_ProjectionMatrix * m_CameraMatrix);

    for (size_t i = 0; i < count; i++)
    {
        const RenderTargetData& data = renderTargets[index + i];

        m_RenderTargetShader->SetUniform("transformation", data.transformation);
        m_RenderTargetShader->SetUniform("uvProjection", data.uvProjection);
        
        m_RenderTargetShader->SetUniform("camera", m_CameraMatrix);
        m_RenderTargetShader->SetUniform("scale", data.scale);
        m_RenderTargetShader->SetUniform("actualScale", data.scale * data.renderTarget->GetCameraScale());
        m_RenderTargetShader->SetUniform("color", data.color);
        m_RenderTargetShader->SetUniform("ambientColor", data.renderTarget->ambientLight);

        auto lightSources = data.renderTarget->GetLightSources();
        m_RenderTargetShader->SetUniform("lightSourceCount", static_cast<int32_t>(lightSources.GetSize()));

        for (auto& lightSource : lightSources)
            lightSource.position = m_CameraMatrix * lightSource.position;

        glNamedBufferData(
            m_RenderTargetSsbo,
            static_cast<GLsizeiptr>(sizeof(LightSource) * lightSources.GetSize()),
            static_cast<const void*>(lightSources.GetData()),
            GL_STREAM_DRAW
        );
        
        glBindTexture(GL_TEXTURE_2D, data.renderTarget->GetTextureId());

        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_RenderTargetSsbo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_RenderTargetShader->Unuse();
    glBindVertexArray(0);
}

void Draw::SetVertexAttribute(const uint32_t index, const int32_t size, const int32_t stride, const size_t offset, const uint32_t divisor)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, Utils::IntToPointer<void>(offset));
    glEnableVertexAttribArray(index);
    if (divisor != 0)
        glVertexBindingDivisor(index, divisor);
}

void Draw::SetVertexAttributeInt(const uint32_t index, const int32_t size, const int32_t stride, const size_t offset, const uint32_t divisor)
{
    glVertexAttribIPointer(index, size, GL_INT, stride, Utils::IntToPointer<void>(offset));
    glEnableVertexAttribArray(index);
    if (divisor != 0)
        glVertexBindingDivisor(index, divisor);
}
