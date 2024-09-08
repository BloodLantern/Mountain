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
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw::Points(const Vector2* positions, const uint32_t count, const Color& color)
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    
    glBufferData(GL_ARRAY_BUFFER, static_cast<int64_t>(sizeof(Vector2)) * count, positions, GL_STREAM_DRAW);

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
        const Vector2 position = m_CameraMatrix * positions[i];
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

void Draw::Circle(const Vector2 center, const float_t radius, const Color& color) { CircleInternal(center, radius, false, color); }

void Draw::CircleFilled(const Vector2 center, const float_t radius, const Color& color) { CircleInternal(center, radius, true, color); }

void Draw::Texture(
    const Mountain::Texture& texture,
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
        * static_cast<Matrix>(antiDiagonalFlip)
        * static_cast<Matrix>(diagonalFlip)
        * Matrix::Scaling({ static_cast<float_t>(textureSize.x) * scale.x, static_cast<float_t>(textureSize.y) * scale.y, 1.f });

    Matrix uvProjection = Matrix::Orthographic(lowerUv.x, higherUv.x, lowerUv.y, higherUv.y, -1.f, 1.f);

    m_DrawList.texture.Emplace(transformation, uvProjection, color);

    if (!m_DrawList.textureId.Empty() && m_DrawList.textureId.Back() == texture.GetId())
    {
        m_DrawList.commands.Back().count++;
        return;
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
    
    glBindVertexArray(m_RenderTargetVao);
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderTargetVbo);
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
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), nullptr);
    glEnableVertexAttribArray(0);
    
    m_PostProcessingShader->Use();
    
    m_PostProcessingShader->SetUniform("projection", m_ProjectionMatrix * m_CameraMatrix);
    
    m_PostProcessingShader->SetUniform("halfImagePixelSize", renderTarget.GetSize() * uvDiff * 0.5f);
    m_PostProcessingShader->SetUniform("position", position);
    m_PostProcessingShader->SetUniform("scale", scale);
    m_PostProcessingShader->SetUniform("rotation", rotation);

    m_PostProcessingShader->SetUniform("horizontalFlip", flipFlags & DrawTextureFlipping::Horizontal);
    m_PostProcessingShader->SetUniform("verticalFlip", flipFlags & DrawTextureFlipping::Vertical);

    Matrix2 diagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::Diagonal)
    {
        static constexpr Matrix2 M(1.f, 1.f, -1.f, 1.f);
        diagonalFlip = M * Matrix2::Scaling({ 1.f, -1.f }) * M.Inverted();
    }
    m_PostProcessingShader->SetUniform("diagonalFlip", diagonalFlip);

    Matrix2 antiDiagonalFlip = Matrix2::Identity();
    if (flipFlags & DrawTextureFlipping::AntiDiagonal)
    {
        static constexpr Matrix2 M(-1.f, 1.f, 1.f, 1.f);
        antiDiagonalFlip = M * Matrix2::Scaling({ 1.f, -1.f }) * M.Inverted();
    }
    m_PostProcessingShader->SetUniform("antiDiagonalFlip", antiDiagonalFlip);
    
    m_PostProcessingShader->SetUniform("actualScale", scale * renderTarget.GetCameraScale());
    m_PostProcessingShader->SetUniform("color", color);
    m_PostProcessingShader->SetUniform("ambientColor", renderTarget.ambientLight);
    const auto& lightSources = renderTarget.GetLightSources();
    m_PostProcessingShader->SetUniform("lightSourceCount", static_cast<int32_t>(lightSources.size()));
    for (size_t i = 0; i < lightSources.size(); ++i)
    {
        const LightSource* lightSource = lightSources[i];
        std::string name = std::format("lightSources[{}].", i);
        m_PostProcessingShader->SetUniform(name + "color", lightSource->color);
        m_PostProcessingShader->SetUniform(name + "intensity", lightSource->intensity);
        m_PostProcessingShader->SetUniform(name + "radius", lightSource->radius);
        m_PostProcessingShader->SetUniform(name + "angleMin", lightSource->angleMin);
        m_PostProcessingShader->SetUniform(name + "angleMax", lightSource->angleMax);
        m_PostProcessingShader->SetUniform(name + "position", renderTarget.GetCameraMatrix() * lightSource->GetPosition() * scale);
    }
    
    glBindTexture(GL_TEXTURE_2D, renderTarget.GetTextureId());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_PostProcessingShader->Unuse();

    glBindVertexArray(0);
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
    points.Clear();
    pointsColored.Clear();
    line.Clear();
    lineColored.Clear();
    triangle.Clear();
    triangleColoredFilled.Clear();
    triangleFilled.Clear();
    triangleColored.Clear();
    rectangle.Clear();
    rectangleFilled.Clear();
    circle.Clear();
    texture.Clear();
    textureId.Clear();
    text.Clear();
    renderTarget.Clear();

    commands.Clear();
}

void Draw::Initialize()
{
    glCreateBuffers(6, &m_RectangleEbo);
    glCreateVertexArrays(10, &m_Vao);

    InitializeLineBuffers();
    InitializeLineColoredBuffers();
    InitializeTriangleBuffers();
    InitializeTriangleColoredBuffers();
    InitializeRectangleBuffers();
    InitializeCircleBuffers();
    InitializeTextureBuffers();
    InitializeTextBuffers();
}

void Draw::LoadResources()
{
    m_LineShader = ResourceManager::Get<Shader>("line");
    m_LineColoredShader = ResourceManager::Get<Shader>("line_colored");
    m_TriangleShader = ResourceManager::Get<Shader>("triangle");
    m_TriangleColoredShader = ResourceManager::Get<Shader>("triangle_colored");
    m_RectangleShader = ResourceManager::Get<Shader>("rectangle");
    m_CircleShader = ResourceManager::Get<Shader>("circle");
    
    m_PrimitiveShader = ResourceManager::Get<Shader>("primitive");
    m_PrimitiveColoredShader = ResourceManager::Get<Shader>("primitive_colored");
    m_TextureShader = ResourceManager::Get<Shader>("texture");
    m_TextShader = ResourceManager::Get<Shader>("text");

    m_PostProcessingShader = ResourceManager::Get<Shader>("post_processing");
}

void Draw::Shutdown()
{
    glDeleteBuffers(6, &m_RectangleEbo);
    glDeleteVertexArrays(10, &m_Vao);
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
    
    glBindVertexArray(0);
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
    
    glBindVertexArray(0);
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
    
    glBindVertexArray(0);
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
    
    glBindVertexArray(0);
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
    
    glBindVertexArray(0);
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
    // Color
    SetVertexAttribute(++index, 4, sizeof(CircleData), offset += sizeof(float_t), 1);
    // Filled
    SetVertexAttributeInt(++index, 1, sizeof(CircleData), offset += sizeof(Color), 1);
    
    glBindVertexArray(0);
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
    
    glBindVertexArray(0);
}

void Draw::InitializeTextBuffers()
{
    glBindVertexArray(m_TextVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleEbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_TextVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * 4, nullptr, GL_DYNAMIC_DRAW);

    SetVertexAttribute(0, 4, sizeof(Vector4), 0);
    
    glBindVertexArray(0);
}

void Draw::Render()
{
    size_t lineIndex = 0, lineColoredIndex = 0;
    size_t triangleIndex = 0, triangleColoredIndex = 0, triangleFilledIndex = 0, triangleColoredFilledIndex = 0;
    size_t rectangleIndex = 0, rectangleFilledIndex = 0;
    size_t circleIndex = 0;
    size_t textureIndex = 0, textureIdIndex = 0;
    size_t textIndex = 0;
    
    const List<CommandData>& commands = m_DrawList.commands;
    for (size_t i = 0; i < commands.GetSize(); i++)
    {
        const CommandData& command = commands[i];
        const size_t count = command.count;

        switch (command.type)
        {
            case DrawDataType::Points:
                break;
                
            case DrawDataType::PointsColored:
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
                break;
        }
    }
    
    m_DrawList.Clear();
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
    
    m_LineShader->SetUniform("projection", proj);
    m_LineColoredShader->SetUniform("projection", proj);
    m_TriangleShader->SetUniform("projection", proj);
    m_TriangleColoredShader->SetUniform("projection", proj);
    m_RectangleShader->SetUniform("projection", proj);
    m_CircleShader->SetUniform("projection", proj);
    m_TextureShader->SetUniform("projection", proj);
    
    m_PrimitiveShader->SetUniform("projection", proj);
    m_PrimitiveColoredShader->SetUniform("projection", proj);
    m_TextShader->SetUniform("projection", proj);
    
    m_CircleShader->SetUniform("camera", m_CameraMatrix);
    m_CircleShader->SetUniform("cameraScale", m_CameraScale);
}

void Draw::CircleInternal(const Vector2 center, const float_t radius, const bool_t filled, const Color& color)
{
    m_DrawList.circle.Emplace(
        Matrix::Translation(static_cast<Vector3>(center - Vector2::One() * radius)) * Matrix::Scaling(
            { radius * 2.f, radius * 2.f, 1.f }
        ),
        center,
        radius,
        color,
        filled
    );
    m_DrawList.AddCommand(DrawDataType::Circle);
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

            glBindTexture(GL_TEXTURE_2D, character.textureId);
            
            glNamedBufferSubData(m_TextVbo, 0, sizeof(vertices), vertices.data());
            
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            offset.x += static_cast<float_t>(character.advance >> 6) * data.scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    m_TextShader->Unuse();
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
