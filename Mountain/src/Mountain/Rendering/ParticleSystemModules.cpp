#include "Mountain/Rendering/ParticleSystemModules.hpp"

#include <ImGui/imgui.h>

#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Rendering/ParticleSystem.hpp"
#include "Mountain/Utils/ImGuiUtils.hpp"

using namespace Mountain::ParticleSystemModules;

void Base::RenderDebug(const ParticleSystem&, const Vector2) const
{
}

bool_t Base::BeginImGui(uint32_t* const enabledModulesInt, const Types type) const
{
    ImGui::PushID(this);

    ImGui::CheckboxFlags("##enabled", enabledModulesInt, static_cast<uint32_t>(type));
    ImGui::SameLine();
    const bool_t result = ImGui::TreeNode(std::string{magic_enum::enum_name(type)}.c_str());

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

    computeShader.SetUniform("shape.type", static_cast<uint32_t>(type));

    switch (type)
    {
        case ShapeType::Circle:
            computeShader.SetUniform("shape.circle.radius", circle.radius);
            computeShader.SetUniform("shape.circle.radiusThickness", circle.radiusThickness);
            computeShader.SetUniform("shape.circle.arcAngle", circle.arcAngle);
            computeShader.SetUniform("shape.circle.arc.mode", static_cast<uint32_t>(circle.arc.mode));
            computeShader.SetUniform("shape.circle.arc.spread", circle.arc.spread);
            break;

        case ShapeType::Line:
            computeShader.SetUniform("shape.line.radius", line.radius);
            computeShader.SetUniform("shape.line.arc.mode", static_cast<uint32_t>(line.arc.mode));
            computeShader.SetUniform("shape.line.arc.spread", line.arc.spread);
            break;

        case ShapeType::Rectangle:
            computeShader.SetUniform("shape.rectangle.scaleThickness", rectangle.scaleThickness);
            break;
    }

    computeShader.SetUniform("shape.offset", offset);
    computeShader.SetUniform("shape.rotation", rotation);
    computeShader.SetUniform("shape.scale", scale);
}

void Shape::RenderImGui(uint32_t* enabledModulesInt)
{
    if (!BeginImGui(enabledModulesInt, Types::Shape))
        return;

    ImGui::ComboEnum("Type", &type);

    static constexpr auto ShapeArcRenderImGui = [](ShapeArc& arc)
    {
        ImGui::Text("Arc");
        ImGui::Indent();
        ImGui::ComboEnum("Mode", &arc.mode);
        ImGui::DragFloat("Spread", &arc.spread, 0.01f, 0.f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Unindent();
    };

    switch (type)
    {
        case ShapeType::Circle:
            ImGui::DragFloat("Radius", &circle.radius, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragFloat("Radius thickness", &circle.radiusThickness, 0.01f, 0.f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragAngle("Arc angle", &circle.arcAngle, 0.1f, 0.f, 360.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ShapeArcRenderImGui(circle.arc);
            break;

        case ShapeType::Line:
            ImGui::DragFloat("Radius", &line.radius, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ShapeArcRenderImGui(line.arc);
            break;

        case ShapeType::Rectangle:
            ImGui::DragFloat2("Scale thickness", rectangle.scaleThickness.Data(), 0.01f, 0.f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            break;
    }

    ImGui::DragFloat2("Offset", offset.Data(), 0.1f);
    ImGui::DragAngle("Rotation", &rotation, 0.1f, 0.f, 0.f, "%.2f");
    ImGui::DragFloat2("Scale", scale.Data(), 0.01f);

    ImGui::Checkbox("Show spawn area", &showSpawnArea);

    EndImGui();
}

void Shape::RenderDebug(const ParticleSystem& system, const Vector2 renderTargetSizeDiff) const
{
    if (!showSpawnArea)
        return;

    static constexpr Color DrawColor = Color::Green();

    const Vector2 center = (system.position + offset) * renderTargetSizeDiff;
    const Vector2 actualScale = scale * renderTargetSizeDiff;
    switch (type)
    {
        case ShapeType::Circle:
            Draw::Circle(center, circle.radius, actualScale, DrawColor);
            Draw::Circle(center, circle.radius - circle.radius * circle.radiusThickness, actualScale, DrawColor);
            break;

        case ShapeType::Line:
            // TODO - Take rotation into account
            Draw::Line(center - Vector2::UnitX() * line.radius, center + Vector2::UnitX() * line.radius, DrawColor);
            break;

        case ShapeType::Rectangle:
            // TODO - Take rotation into account
            Draw::Rectangle(center - actualScale * 0.5f, actualScale, DrawColor);
            const Vector2 actualScaleThickness = actualScale * (Vector2::One() - rectangle.scaleThickness);
            Draw::Rectangle(center - actualScaleThickness * 0.5f, actualScaleThickness, DrawColor);
            break;
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
