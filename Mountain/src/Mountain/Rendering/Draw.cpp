#include "Mountain/Rendering/Draw.hpp"

#include "Mountain/Globals.hpp"
#include "Mountain/Resource/Font.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Resource/Shader.hpp"

using namespace Mountain;

void Draw::Clear(const Color& color)
{
    Graphics::SetClearColor(color);
    Graphics::Clear(Graphics::ClearFlags::ColorBuffer);
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

void Draw::Circle(
    const Vector2 center,
    const float_t radius,
    const float_t thickness,
    const Vector2 scale,
    const Color& color
)
{
    CircleInternal(center, radius, thickness, false, scale, color);
}

void Draw::CircleFilled(
    const Vector2 center,
    const float_t radius,
    const Vector2 scale,
    const Color& color
)
{
    CircleInternal(center, radius, 1.f, true, scale, color);
}

void Draw::Arc(
    const Vector2 center,
    const float_t radius,
    const float_t startingAngle,
    const float_t deltaAngle,
    const float_t thickness,
    const Vector2 scale,
    const Color& color
)
{
    ArcInternal(center, radius, startingAngle, deltaAngle, thickness, false, scale, color);
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
    ArcInternal(center, radius, startingAngle, deltaAngle, 1.f, true, scale, color);
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
    {
        THROW ArgumentException{"UV0 cannot be greater than UV1", "uv0"};
    }

    if (origin.x < 0.f || origin.x > 1.f || origin.y < 0.f || origin.y > 1.f)
    {
        THROW ArgumentException{"Origin must be in the range [{ 0, 0 }, { 1, 1 }]", "origin"};
    }

    const Vector2 uvDiff = uv1 - uv0;
    const Vector2 lowerUv = uv0;

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
    {
        THROW ArgumentException{"UV0 cannot be greater than UV1", "uv0"};
    }

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
    m_RectangleEbo.Create();
    m_Vbo.Create();
    m_RectangleVbo.Create();
    m_TextureVbo.Create();
    m_TextVbo.Create();
    m_RenderTargetVbo.Create();
    m_RenderTargetSsbo.Create();

    m_PointVao.Create();
    m_LineVao.Create();
    m_LineColoredVao.Create();
    m_TriangleVao.Create();
    m_TriangleColoredVao.Create();
    m_RectangleVao.Create();
    m_CircleVao.Create();
    m_ArcVao.Create();
    m_TextureVao.Create();
    m_TextVao.Create();
    m_RenderTargetVao.Create();

    m_RectangleEbo.SetDebugName("Rectangle EBO");
    m_Vbo.SetDebugName("Global VBO");
    m_RectangleVbo.SetDebugName("Rectangle VBO");
    m_TextureVbo.SetDebugName("Texture VBO");
    m_TextVbo.SetDebugName("Text VBO");
    m_RenderTargetVbo.SetDebugName("RenderTarget VBO");
    m_RenderTargetSsbo.SetDebugName("RenderTarget SSBO");

    m_PointVao.SetDebugName("Point VAO");
    m_LineVao.SetDebugName("Line VAO");
    m_LineColoredVao.SetDebugName("Line Colored VAO");
    m_TriangleVao.SetDebugName("Triangle VAO");
    m_TriangleColoredVao.SetDebugName("Triangle Colored VAO");
    m_RectangleVao.SetDebugName("Rectangle VAO");
    m_CircleVao.SetDebugName("Circle VAO");
    m_ArcVao.SetDebugName("Arc VAO");
    m_TextureVao.SetDebugName("Texture VAO");
    m_TextVao.SetDebugName("Text VAO");
    m_RenderTargetVao.SetDebugName("RenderTarget VAO");

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

    Graphics::BindVertexArray(0);
    BindBuffer(Graphics::BufferType::ArrayBuffer, 0);
    BindBuffer(Graphics::BufferType::ElementArrayBuffer, 0);
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
    m_RectangleEbo.Delete();
    m_Vbo.Delete();
    m_RectangleVbo.Delete();
    m_TextureVbo.Delete();
    m_TextVbo.Delete();
    m_RenderTargetVbo.Delete();
    m_RenderTargetSsbo.Delete();

    m_PointVao.Delete();
    m_LineVao.Delete();
    m_LineColoredVao.Delete();
    m_TriangleVao.Delete();
    m_TriangleColoredVao.Delete();
    m_RectangleVao.Delete();
    m_CircleVao.Delete();
    m_ArcVao.Delete();
    m_TextureVao.Delete();
    m_TextVao.Delete();
    m_RenderTargetVao.Delete();
}

void Draw::InitializePointBuffers()
{
    BindVertexArray(m_PointVao);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Position
    Graphics::SetVertexAttribute(index, 2, sizeof(PointData), offset, 1);
    // Color
    Graphics::SetVertexAttribute(++index, 4, sizeof(PointData), offset += sizeof(Vector2), 1);
}

void Draw::InitializeLineBuffers()
{
    BindVertexArray(m_LineVao);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    Graphics::SetVertexAttribute(index, 2, sizeof(LineData), offset, 1);
    Graphics::SetVertexAttribute(++index, 2, sizeof(LineData), offset += sizeof(Vector2), 1);
    // Color
    Graphics::SetVertexAttribute(++index, 4, sizeof(LineData), offset += sizeof(Vector2), 1);
}

void Draw::InitializeLineColoredBuffers()
{
    BindVertexArray(m_LineColoredVao);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    Graphics::SetVertexAttribute(index, 2, sizeof(LineColoredData), offset, 1);
    Graphics::SetVertexAttribute(++index, 2, sizeof(LineColoredData), offset += sizeof(Vector2), 1);
    // Colors
    Graphics::SetVertexAttribute(++index, 4, sizeof(LineColoredData), offset += sizeof(Vector2), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(LineColoredData), offset += sizeof(Color), 1);
}

void Draw::InitializeTriangleBuffers()
{
    BindVertexArray(m_TriangleVao);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    Graphics::SetVertexAttribute(index, 2, sizeof(TriangleData), offset, 1);
    Graphics::SetVertexAttribute(++index, 2, sizeof(TriangleData), offset += sizeof(Vector2), 1);
    Graphics::SetVertexAttribute(++index, 2, sizeof(TriangleData), offset += sizeof(Vector2), 1);
    // Color
    Graphics::SetVertexAttribute(++index, 4, sizeof(TriangleData), offset += sizeof(Vector2), 1);
}

void Draw::InitializeTriangleColoredBuffers()
{
    BindVertexArray(m_TriangleColoredVao);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    uint32_t index = 0;
    size_t offset = 0;
    // Points
    Graphics::SetVertexAttribute(index, 2, sizeof(TriangleColoredData), offset, 1);
    Graphics::SetVertexAttribute(++index, 2, sizeof(TriangleColoredData), offset += sizeof(Vector2), 1);
    Graphics::SetVertexAttribute(++index, 2, sizeof(TriangleColoredData), offset += sizeof(Vector2), 1);
    // Colors
    Graphics::SetVertexAttribute(++index, 4, sizeof(TriangleColoredData), offset += sizeof(Vector2), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TriangleColoredData), offset += sizeof(Color), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TriangleColoredData), offset += sizeof(Color), 1);
}

void Draw::InitializeRectangleBuffers()
{
    constexpr std::array vertexData{
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    constexpr std::array<uint32_t, 6> indexData{
        0, 1, 2,
        2, 3, 0
    };

    BindVertexArray(m_RectangleVao);

    // VBO
    BindBuffer(Graphics::BufferType::ArrayBuffer, m_RectangleVbo);
    m_RectangleVbo.SetData(sizeof(vertexData), vertexData.data(), Graphics::BufferUsage::StaticDraw);

    // EBO
    BindBuffer(Graphics::BufferType::ElementArrayBuffer, m_RectangleEbo);
    m_RectangleEbo.SetData(sizeof(indexData), indexData.data(), Graphics::BufferUsage::StaticDraw);

    // VAO
    uint32_t index = 0;
    // Vertex position
    Graphics::SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    Graphics::SetVertexAttribute(++index, 4, sizeof(RectangleData), offset, 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
    // Color
    Graphics::SetVertexAttribute(++index, 4, sizeof(RectangleData), offset += sizeof(Vector4), 1);
}

void Draw::InitializeCircleBuffers()
{
    BindVertexArray(m_CircleVao);

    // VBO
    BindBuffer(Graphics::BufferType::ArrayBuffer, m_RectangleVbo);
    // EBO
    BindBuffer(Graphics::BufferType::ElementArrayBuffer, m_RectangleEbo);

    // VAO
    uint32_t index = 0;
    // Vertex position
    Graphics::SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    Graphics::SetVertexAttribute(++index, 4, sizeof(CircleData), offset, 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector4), 1);
    // Center
    Graphics::SetVertexAttribute(++index, 2, sizeof(CircleData), offset += sizeof(Vector4), 1);
    // Radius
    Graphics::SetVertexAttribute(++index, 1, sizeof(CircleData), offset += sizeof(Vector2), 1);
    // Thickness
    Graphics::SetVertexAttribute(++index, 1, sizeof(CircleData), offset += sizeof(float_t), 1);
    // Scale
    Graphics::SetVertexAttribute(++index, 2, sizeof(CircleData), offset += sizeof(float_t), 1);
    // Color
    Graphics::SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(Vector2), 1);
    // Filled
    Graphics::SetVertexAttributeInt(++index, 1, sizeof(CircleData), offset += sizeof(Color), 1);
}

void Draw::InitializeArcBuffers()
{
    BindVertexArray(m_ArcVao);

    // VBO
    BindBuffer(Graphics::BufferType::ArrayBuffer, m_RectangleVbo);
    // EBO
    BindBuffer(Graphics::BufferType::ElementArrayBuffer, m_RectangleEbo);

    // VAO
    uint32_t index = 0;
    // Vertex position
    Graphics::SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    Graphics::SetVertexAttribute(++index, 4, sizeof(ArcData), offset, 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector4), 1);
    // Center
    Graphics::SetVertexAttribute(++index, 2, sizeof(ArcData), offset += sizeof(Vector4), 1);
    // Radius
    Graphics::SetVertexAttribute(++index, 1, sizeof(ArcData), offset += sizeof(Vector2), 1);
    // Starting angle
    Graphics::SetVertexAttribute(++index, 1, sizeof(ArcData), offset += sizeof(float_t), 1);
    // Delta angle
    Graphics::SetVertexAttribute(++index, 1, sizeof(ArcData), offset += sizeof(float_t), 1);
    // Thickness
    Graphics::SetVertexAttribute(++index, 1, sizeof(ArcData), offset += sizeof(float_t), 1);
    // Scale
    Graphics::SetVertexAttribute(++index, 2, sizeof(ArcData), offset += sizeof(float_t), 1);
    // Color
    Graphics::SetVertexAttribute(++index, 4, sizeof(ArcData), offset += sizeof(Vector2), 1);
    // Filled
    Graphics::SetVertexAttributeInt(++index, 1, sizeof(ArcData), offset += sizeof(Color), 1);
}

void Draw::InitializeTextureBuffers()
{
    constexpr std::array vertexData = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    BindVertexArray(m_TextureVao);

    // VBO
    BindBuffer(Graphics::BufferType::ArrayBuffer, m_TextureVbo);
    m_TextureVbo.SetData(sizeof(vertexData), vertexData.data(), Graphics::BufferUsage::StaticDraw);

    // EBO
    BindBuffer(Graphics::BufferType::ElementArrayBuffer, m_RectangleEbo);

    // VAO
    uint32_t index = 0;
    // Vertex position
    Graphics::SetVertexAttribute(index, 2, sizeof(Vector2), 0, 0);

    BindBuffer(Graphics::BufferType::ArrayBuffer, m_Vbo);
    size_t offset = 0;
    // Transformation Matrix
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset, 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    // UV projection Matrix
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
    // Color
    Graphics::SetVertexAttribute(++index, 4, sizeof(TextureData), offset += sizeof(Vector4), 1);
}

void Draw::InitializeTextBuffers()
{
    BindVertexArray(m_TextVao);
    BindBuffer(Graphics::BufferType::ElementArrayBuffer, m_RectangleEbo);
    BindBuffer(Graphics::BufferType::ArrayBuffer, m_TextVbo);
    m_TextVbo.SetStorage(sizeof(Vector4) * 4, nullptr, Utils::ToFlags(Graphics::BufferStorageFlags::DynamicStorage));

    Graphics::SetVertexAttribute(0, 4, sizeof(Vector4), 0);
}

void Draw::InitializeRenderTargetBuffers()
{
    constexpr std::array vertexData = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    BindVertexArray(m_RenderTargetVao);

    // VBO
    BindBuffer(Graphics::BufferType::ArrayBuffer, m_RenderTargetVbo);
    m_RenderTargetVbo.SetData(sizeof(vertexData), vertexData.data(), Graphics::BufferUsage::StaticDraw);

    // EBO
    BindBuffer(Graphics::BufferType::ElementArrayBuffer, m_RectangleEbo);

    // VAO
    // Vertex position
    Graphics::SetVertexAttribute(0, 2, sizeof(Vector2), 0, 0);
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

void Draw::CircleInternal(const Vector2 center, const float_t radius, const float_t thickness, const bool_t filled, const Vector2 scale, const Color& color)
{
    const float_t actualThickness = thickness - 1.f; // When thickness == 0, the circle line is 1 pixel wide

    m_DrawList.circle.Emplace(
        Matrix::Translation(
            static_cast<Vector3>(
                center - scale * radius * m_CameraScale - Vector2::One() * actualThickness
            )
        )
        * Matrix::Scaling(
            {
                radius * 2.f * scale.x * m_CameraScale.x + actualThickness * 2.f,
                radius * 2.f * scale.y * m_CameraScale.y + actualThickness * 2.f,
                1.f
            }
        ),
        center,
        radius,
        actualThickness,
        scale / m_CameraScale,
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
    const float_t thickness,
    bool_t filled,
    const Vector2 scale,
    const Color& color
)
{
    const float_t actualThickness = thickness - 1.f; // When thickness == 0, the circle line is 1 pixel wide

    m_DrawList.arc.Emplace(
        Matrix::Translation(
            static_cast<Vector3>(
                center - scale * radius * m_CameraScale - Vector2::One() * actualThickness
            )
        )
        * Matrix::Scaling(
            {
                radius * 2.f * scale.x * m_CameraScale.x + actualThickness * 2.f,
                radius * 2.f * scale.y * m_CameraScale.y + actualThickness * 2.f,
                1.f
            }
        ),
        center,
        radius,
        startingAngle,
        deltaAngle,
        thickness,
        scale / m_CameraScale,
        color,
        filled
    );
    m_DrawList.AddCommand(DrawDataType::Arc);
}

void Draw::RenderPointData(const List<PointData>& points, const size_t index, const size_t count)
{
    if (points.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(PointData) * count), &points[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_PointVao);
    m_PointShader->Use();

    DrawArraysInstanced(Graphics::DrawMode::Points, 0, 1, static_cast<int32_t>(count));

    m_PointShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderLineData(const List<LineData>& lines, const size_t index, const size_t count)
{
    if (lines.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(LineData) * count), &lines[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_LineVao);
    m_LineShader->Use();

    DrawArraysInstanced(Graphics::DrawMode::Lines, 0, 2, static_cast<int32_t>(count));

    m_LineShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderLineColoredData(const List<LineColoredData>& linesColored, const size_t index, const size_t count)
{
    if (linesColored.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(LineColoredData) * count), &linesColored[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_LineColoredVao);
    m_LineColoredShader->Use();

    DrawArraysInstanced(Graphics::DrawMode::Lines, 0, 2, static_cast<int32_t>(count));

    m_LineColoredShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderTriangleData(const List<TriangleData>& triangles, const bool_t filled, const size_t index, const size_t count)
{
    if (triangles.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(TriangleData) * count), &triangles[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_TriangleVao);
    m_TriangleShader->Use();

    DrawArraysInstanced(filled ? Graphics::DrawMode::Triangles : Graphics::DrawMode::LineLoop, 0, 3, static_cast<int32_t>(count));

    m_TriangleShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderTriangleColoredData(const List<TriangleColoredData>& trianglesColored, const bool_t filled, const size_t index, const size_t count)
{
    if (trianglesColored.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(TriangleColoredData) * count), &trianglesColored[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_TriangleColoredVao);
    m_TriangleColoredShader->Use();

    DrawArraysInstanced(filled ? Graphics::DrawMode::Triangles : Graphics::DrawMode::LineLoop, 0, 3, static_cast<int32_t>(count));

    m_TriangleColoredShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderRectangleData(const List<RectangleData>& rectangles, const bool_t filled, const size_t index, const size_t count)
{
    if (rectangles.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(RectangleData) * count), &rectangles[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_RectangleVao);
    m_RectangleShader->Use();

    if (filled)
        DrawElementsInstanced(Graphics::DrawMode::Triangles, 6, Graphics::DataType::UnsignedInt, nullptr, static_cast<int32_t>(count));
    else
        DrawArraysInstanced(Graphics::DrawMode::LineLoop, 0, 4, static_cast<int32_t>(count));

    m_RectangleShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderCircleData(const List<CircleData>& circles, const size_t index, const size_t count)
{
    if (circles.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(CircleData) * count), &circles[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_CircleVao);
    m_CircleShader->Use();

    DrawElementsInstanced(Graphics::DrawMode::Triangles, 6, Graphics::DataType::UnsignedInt, nullptr, static_cast<int32_t>(count));

    m_CircleShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderArcData(const List<ArcData>& arcs, const size_t index, const size_t count)
{
    if (arcs.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(ArcData) * count), &arcs[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_ArcVao);
    m_ArcShader->Use();

    DrawElementsInstanced(Graphics::DrawMode::Triangles, 6, Graphics::DataType::UnsignedInt, nullptr, static_cast<int32_t>(count));

    m_ArcShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderTextureData(const List<TextureData>& textures, const uint32_t textureId, const size_t index, const size_t count)
{
    if (textures.Empty())
        return;

    m_Vbo.SetData(static_cast<int64_t>(sizeof(TextureData) * count), &textures[index], Graphics::BufferUsage::StreamDraw);

    BindVertexArray(m_TextureVao);
    Graphics::BindTexture(textureId);
    m_TextureShader->Use();

    DrawElementsInstanced(Graphics::DrawMode::Triangles, 6, Graphics::DataType::UnsignedInt, nullptr, static_cast<int32_t>(count));

    m_TextureShader->Unuse();
    Graphics::BindTexture(0);
    Graphics::BindVertexArray(0);
}

void Draw::RenderTextData(const List<TextData>& texts, const size_t index, const size_t count)
{
    BindVertexArray(m_TextVao);
    m_TextShader->Use();

    for (size_t i = 0; i < count; i++)
    {
        const TextData& data = texts[index + i];

        m_TextShader->SetUniform("color", data.color);

        Vector2 offset = data.position + Vector2::UnitY() * data.font->CalcTextSize(data.text).y * data.scale;

        for (const char_t c : data.text)
        {
            const Font::Character& character = data.font->m_Characters.at(c);

            if (character.size != Vector2i::Zero()) // Do not draw invisible characters
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

                BindTexture(character.texture);

                m_TextVbo.SetSubData(0, sizeof(vertices), vertices.data());

                DrawElements(Graphics::DrawMode::Triangles, 6, Graphics::DataType::UnsignedInt, nullptr);
            }

            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            offset.x += static_cast<float_t>(character.advance >> 6) * data.scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }

        Graphics::BindTexture(0);
    }

    m_TextShader->Unuse();
    Graphics::BindVertexArray(0);
}

void Draw::RenderRenderTargetData(const List<RenderTargetData>& renderTargets, const size_t index, const size_t count)
{
    BindVertexArray(m_RenderTargetVao);
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

        m_RenderTargetSsbo.SetData(
            static_cast<int32_t>(sizeof(LightSource) * lightSources.GetSize()),
            lightSources.GetData(),
            Graphics::BufferUsage::StreamDraw
        );

        Graphics::BindTexture(data.renderTarget->GetTextureId());

        Graphics::MemoryBarrier(Utils::ToFlags(Graphics::MemoryBarrierFlags::ShaderStorageBarrier));

        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 0, m_RenderTargetSsbo);
        DrawElements(Graphics::DrawMode::Triangles, 6, Graphics::DataType::UnsignedInt, nullptr);
    }

    BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 0, 0);
    Graphics::BindTexture(0);
    m_RenderTargetShader->Unuse();
    Graphics::BindVertexArray(0);
}
