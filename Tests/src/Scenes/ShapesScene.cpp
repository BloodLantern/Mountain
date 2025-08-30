#include "Common.hpp"

#include "Scenes/ShapesScene.hpp"

#include <Mountain/Graphics/Draw.hpp>
#include <Mountain/Graphics/Renderer.hpp>
#include <Mountain/Utils/ImGuiUtils.hpp>

#define UPDATE_DRAW_POSITION drawPosition = GetDrawPosition((index)++)

ShapesScene::ShapesScene()
    : Base{"Shapes"}
{
}

void ShapesScene::Render()
{
    TestScene::Render();

    Draw::SetSortMode(DrawSortMode::Immediate);

    size_t index = 0;

    const Vector2 drawSize = GetDrawSize();

    const Vector2 usedDrawSize = drawSize * 0.8f;
    const Vector2 halfUsedDrawSize = usedDrawSize * 0.5f;

    Vector2 drawPosition;

    UPDATE_DRAW_POSITION;
    Draw::Point(drawPosition, m_Color1);

    UPDATE_DRAW_POSITION;
    Draw::Line(drawPosition - halfUsedDrawSize, drawPosition + halfUsedDrawSize, m_Color1);

    UPDATE_DRAW_POSITION;
    Draw::Line(drawPosition - halfUsedDrawSize, drawPosition + halfUsedDrawSize, m_Color1, m_Color2);

    UPDATE_DRAW_POSITION;
    Draw::Triangle(
        drawPosition - halfUsedDrawSize * Vector2{1.f, -1.f},
        drawPosition + halfUsedDrawSize,
        drawPosition - Vector2::UnitY() * halfUsedDrawSize.y,
        m_Color1
    );

    UPDATE_DRAW_POSITION;
    Draw::Triangle(
        drawPosition - halfUsedDrawSize * Vector2{1.f, -1.f},
        drawPosition + halfUsedDrawSize,
        drawPosition - Vector2::UnitY() * halfUsedDrawSize.y,
        m_Color1,
        m_Color2,
        m_Color3
    );

    UPDATE_DRAW_POSITION;
    Draw::TriangleFilled(
        drawPosition - halfUsedDrawSize * Vector2{1.f, -1.f},
        drawPosition + halfUsedDrawSize,
        drawPosition - Vector2::UnitY() * halfUsedDrawSize.y,
        m_Color1
    );

    UPDATE_DRAW_POSITION;
    Draw::TriangleFilled(
        drawPosition - halfUsedDrawSize * Vector2{1.f, -1.f},
        drawPosition + halfUsedDrawSize,
        drawPosition - Vector2::UnitY() * halfUsedDrawSize.y,
        m_Color1,
        m_Color2,
        m_Color3
    );

    UPDATE_DRAW_POSITION;
    Draw::Rectangle(drawPosition - halfUsedDrawSize, usedDrawSize, 0.f, Vector2::Zero(), m_Color1);

    UPDATE_DRAW_POSITION;
    Draw::RectangleFilled(drawPosition - halfUsedDrawSize, usedDrawSize, 0.f, Vector2::Zero(), m_Color1);

    UPDATE_DRAW_POSITION;
    Draw::Circle(
        drawPosition,
        (halfUsedDrawSize.x + halfUsedDrawSize.y) * 0.5f,
        m_Thickness,
        m_Scale,
        m_Color1
    );

    UPDATE_DRAW_POSITION;
    Draw::CircleFilled(
        drawPosition,
        (halfUsedDrawSize.x + halfUsedDrawSize.y) * 0.5f,
        m_Scale,
        m_Color1
    );

    UPDATE_DRAW_POSITION;
    Draw::Arc(
        drawPosition,
        (halfUsedDrawSize.x + halfUsedDrawSize.y) * 0.5f,
        m_ArcStartingAngle,
        m_ArcDeltaAngle,
        m_Thickness,
        m_Scale,
        m_Color1
    );

    UPDATE_DRAW_POSITION;
    Draw::ArcFilled(
        drawPosition,
        (halfUsedDrawSize.x + halfUsedDrawSize.y) * 0.5f,
        m_ArcStartingAngle,
        m_ArcDeltaAngle,
        m_Scale,
        m_Color1
    );
}

void ShapesScene::RenderDebug()
{
    TestScene::RenderDebug();

    if (m_ShowGrid)
    {
        const Vector2 drawSize = GetDrawSize();

        const Vector2 firstPosition = GetDrawPosition(0) - drawSize * 0.5f;

        for (size_t i = 1; i < ShapesRowSize; i++)
        {
            const float_t x = static_cast<float_t>(i) * drawSize.x;
            Draw::Line(firstPosition + Vector2{x, 0.f}, firstPosition + Vector2{x, drawSize.y * ShapesRowCount}, Color::Lime());
        }

        for (size_t i = 0; i <= ActualShapesCount / ShapesRowSize; i++)
        {
            const float_t y = static_cast<float_t>(i) * drawSize.y;
            Draw::Line(firstPosition + Vector2{0.f, y}, firstPosition + Vector2{drawSize.x * ShapesRowSize, y}, Color::Lime());
        }
    }
}

void ShapesScene::RenderImGui()
{
    TestScene::RenderImGui();

    ImGui::Checkbox("Show grid", &m_ShowGrid);

    ImGui::SeparatorText("Shapes settings");
    ImGui::TextColored(Color::Gray(), "These settings are only applied for the Draw functions that support it");

    ImGui::ColorEdit4("Color 1", m_Color1.Data());
    ImGui::ColorEdit4("Color 2", m_Color2.Data());
    ImGui::ColorEdit4("Color 3", m_Color3.Data());

    ImGui::DragFloat("Thickness", &m_Thickness, 0.1f, 1.f, std::numeric_limits<float_t>::max());
    ImGui::DragFloat2("Scale", m_Scale.Data(), 0.01f);

    ImGui::DragAngle("Arc starting angle", &m_ArcStartingAngle);
    ImGui::DragAngle("Arc delta angle", &m_ArcDeltaAngle, 0.1f, 0.f);
}

Vector2 ShapesScene::GetDrawPosition(const size_t index)
{
    const size_t xIndex = index % ShapesRowSize;
    const size_t yIndex = index / ShapesRowSize;

    const Vector2 drawSize = GetDrawSize();
    const float_t remainingVerticalSpace = static_cast<float_t>(Renderer::GetCurrentRenderTarget().GetSize().y) - drawSize.y * ShapesRowCount;

    return Vector2{drawSize.x * static_cast<float_t>(xIndex), drawSize.y * static_cast<float_t>(yIndex) + remainingVerticalSpace * 0.5f} + drawSize * 0.5f;
}

Vector2 ShapesScene::GetDrawSize()
{
    return Vector2::One() * (static_cast<float_t>(Renderer::GetCurrentRenderTarget().GetSize().x) / static_cast<float_t>(ShapesRowSize));
}
