#include "Mountain/rendering/particle_system_modules.hpp"

#include <ImGui/imgui.h>

#include "Mountain/rendering/draw.hpp"
#include "Mountain/rendering/particle_system.hpp"
#include "Mountain/utils/imgui_utils.hpp"

using namespace Mountain::ParticleSystemModules;

void Base::RenderDebug(const ParticleSystem&, const Vector2) const
{
}

bool_t Base::BeginImGui(uint32_t* const enabledModulesInt, const Types type) const
{
    ImGui::PushID(this);

    ImGui::CheckboxFlags("##enabled", enabledModulesInt, static_cast<uint32_t>(type));
    ImGui::SameLine();
    const bool_t result = ImGui::TreeNode(magic_enum::enum_name(type).data());

    if (!result)
        ImGui::PopID();

    return result;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Base::EndImGui() const
{
    ImGui::TreePop();

    ImGui::PopID();
}

void Shape::SetComputeShaderUniforms(const ComputeShader& computeShader, const Types enabledModules) const
{
    if (!(enabledModules & Types::Shape))
        return;
}

void Shape::RenderImGui(uint32_t* enabledModulesInt)
{
    if (!BeginImGui(enabledModulesInt, Types::Shape))
        return;

    if (ImGui::ComboEnum("Type", &type))
    {
        switch (type)
        {
            case ShapeType::Circle:
                data = ShapeCircle{};
                break;

            case ShapeType::Line:
                data = ShapeLine{};
                break;

            case ShapeType::Rectangle:
                data = ShapeRectangle{};
                break;
        }
    }

    static constexpr auto ShapeArcRenderImGui = [](ShapeArc& arc)
    {
        ImGui::Indent();
        ImGui::ComboEnum("Mode", &arc.mode);
        ImGui::DragFloat("Spread", &arc.spread, 0.01f, 0.f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Unindent();
    };

    switch (type)
    {
        case ShapeType::Circle:
        {
            ShapeCircle& circle = std::get<ShapeCircle>(data);
            ImGui::DragFloat("Radius", &circle.radius, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragFloat("Radius thickness", &circle.radiusThickness, 0.01f, 0.f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragAngle("Arc angle", &circle.arcAngle, 0.1f, 0.f, Calc::TwoPi, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ShapeArcRenderImGui(circle.arc);
            break;
        }

        case ShapeType::Line:
        {
            ShapeLine& line = std::get<ShapeLine>(data);
            ImGui::DragFloat("Radius", &line.radius, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ShapeArcRenderImGui(line.arc);
            break;
        }

        case ShapeType::Rectangle:
        {
            ShapeRectangle& rectangle = std::get<ShapeRectangle>(data);
            ImGui::DragFloat2("Scale thickness", rectangle.scaleThickness.Data(), 0.01f, 0.f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            break;
        }
    }

    ImGui::DragFloat2("Offset", offset.Data(), 0.1f);
    ImGui::DragAngle("Rotation", &rotation, 0.1f, 0.f, 0.f, "%.2f");
    ImGui::DragFloat2("Scale", scale.Data(), 0.01f);

    ImGui::Checkbox("Show wireframe", &showWireframe);

    EndImGui();
}

void Shape::RenderDebug(const ParticleSystem& system, const Vector2 renderTargetSizeDiff) const
{
    if (!showWireframe)
        return;

    const Vector2 center = (system.position + offset) * renderTargetSizeDiff;
    switch (type)
    {
        case ShapeType::Circle:
        {
            const ShapeCircle& circle = std::get<ShapeCircle>(data);
            Draw::Circle(center, circle.radius, scale * renderTargetSizeDiff, Color::Green());
            break;
        }
        case ShapeType::Line:
        {
            const ShapeLine& line = std::get<ShapeLine>(data);
            break;
        }
        case ShapeType::Rectangle:
        {
            const ShapeRectangle& rectangle = std::get<ShapeRectangle>(data);
            break;
        }
    }
}

void ColorOverLifetime::SetComputeShaderUniforms(const ComputeShader& computeShader, const Types enabledModules) const
{
    if (!(enabledModules & Types::ColorOverLifetime))
        return;

    computeShader.SetUniform("colorOverLifetime.target", target);
}

void ColorOverLifetime::RenderImGui(uint32_t* const enabledModulesInt)
{
    if (!BeginImGui(enabledModulesInt, Types::ColorOverLifetime))
        return;

    ImGui::ColorEdit4("Target", target.Data());

    EndImGui();
}

void ForceOverLifetime::SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const
{
    if (!(enabledModules & Types::ForceOverLifetime))
        return;

    computeShader.SetUniform("forceOverLifetime.force", force);
}

void ForceOverLifetime::RenderImGui(uint32_t* enabledModulesInt)
{
    if (!BeginImGui(enabledModulesInt, Types::ForceOverLifetime))
        return;

    Vector2 direction = force.Normalized();
    ImGuiUtils::DirectionVector("Direction", &direction);
    float_t strength = force.Length();
    ImGui::DragFloat("Strength", &strength);
    force = direction * (strength == 0.f ? 1.f : strength);

    EndImGui();
}
