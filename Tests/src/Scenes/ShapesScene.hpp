#pragma once

#include "Scenes/TestScene.hpp"

constexpr size_t ShapesCount = 13;
constexpr size_t ActualShapesCount = std::bit_ceil(ShapesCount);
constexpr size_t ShapesRowSize = 8;
constexpr size_t ShapesRowCount = ActualShapesCount / ShapesRowSize;

class ShapesScene : public TestScene
{
public:
    using Base = TestScene;

    ShapesScene();

    void Render() override;

    void RenderDebug() override;

    void RenderImGui() override;

private:
    bool_t m_ShowGrid = false;

    Color m_Color1 = Color::White();
    Color m_Color2 = Color::Red();
    Color m_Color3 = Color::Aqua();

    float_t m_Thickness = 1.f;
    Vector2 m_Scale = Vector2::One();

    float_t m_ArcStartingAngle = Calc::PiOver2;
    float_t m_ArcDeltaAngle = Calc::Pi;

    static Vector2 GetDrawPosition(size_t index);
    /// @brief Available size to draw for each shape
    static Vector2 GetDrawSize();
};
