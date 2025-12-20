#pragma once

#include "Scenes/TestScene.hpp"

constexpr usize ShapesCount = 13;
constexpr usize ActualShapesCount = std::bit_ceil(ShapesCount);
constexpr usize ShapesRowSize = 8;
constexpr usize ShapesRowCount = ActualShapesCount / ShapesRowSize;

class ShapesScene : public TestScene
{
public:
    using Base = TestScene;

    ShapesScene();

    void Render() override;

    void RenderDebug() override;

    void RenderImGui() override;

private:
    bool m_ShowGrid = false;

    Color m_Color1 = Color::White();
    Color m_Color2 = Color::Red();
    Color m_Color3 = Color::Aqua();

    f32 m_Thickness = 1.f;
    Vector2 m_Scale = Vector2::One();

    f32 m_ArcStartingAngle = Calc::PiOver2;
    f32 m_ArcDeltaAngle = Calc::Pi;

    static Vector2 GetDrawPosition(usize index);
    /// @brief Available size to draw for each shape
    static Vector2 GetDrawSize();
};
