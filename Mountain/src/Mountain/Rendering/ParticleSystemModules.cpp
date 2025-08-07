#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Rendering/ParticleSystemModules.hpp"

#include <ImGui/imgui.h>

#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Rendering/ParticleSystem.hpp"
#include "Mountain/Utils/ImGuiUtils.hpp"

using namespace Mountain::ParticleSystemModules;

ModuleBase::ModuleBase(const Types type)
    : m_Type(type)
{
}

void ModuleBase::SetComputeShaderUniforms(const ComputeShader&) const
{
}

void ModuleBase::SetDrawShaderUniforms(const Shader&) const
{
}

void ModuleBase::RenderDebug(const ParticleSystem&, const Vector2) const
{
}

bool_t ModuleBase::BeginImGui(Types* enabledModulesInt) const
{
    ImGui::PushID(this);

    ImGui::CheckboxFlags("##enabled", reinterpret_cast<uint32_t*>(enabledModulesInt), static_cast<uint32_t>(m_Type));
    ImGui::SameLine();
    const bool_t result = ImGui::TreeNode(std::string{magic_enum::enum_name(m_Type)}.c_str());

    if (!result)
        ImGui::PopID();

    return result;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ModuleBase::EndImGui() const
{
    ImGui::TreePop();

    ImGui::PopID();
}

void Shape::SetComputeShaderUniforms(const ComputeShader& computeShader) const
{
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

void Shape::RenderImGui()
{
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
            Draw::Arc(center, circle.radius, rotation, circle.arcAngle, 1.f, actualScale, DrawColor);
            Draw::Arc(center, circle.radius - circle.radius * circle.radiusThickness, rotation, circle.arcAngle, 1.f, actualScale, DrawColor);
            break;

        case ShapeType::Line:
        {
            const Vector2 left = -Vector2::UnitX() * line.radius;
            const Vector2 right = Vector2::UnitX() * line.radius;
            Draw::Line(center + left.Rotated(rotation), center + right.Rotated(rotation), DrawColor);
            break;
        }

        case ShapeType::Rectangle:
            Draw::Rectangle(center, actualScale, rotation, Vector2::One() * 0.5f, DrawColor);
            const Vector2 actualScaleThickness = actualScale * (Vector2::One() - rectangle.scaleThickness);
            Draw::Rectangle(center, actualScaleThickness, rotation, Vector2::One() * 0.5f, DrawColor);
            break;
    }
}

void ForceOverLifetime::SetComputeShaderUniforms(const ComputeShader& computeShader) const
{
    computeShader.SetUniform("forceOverLifetime.force", force);
    computeShader.SetUniform("forceOverLifetime.easingType", easingType);
}

void ForceOverLifetime::RenderImGui()
{
    Vector2 direction = force.Normalized();
    ImGuiUtils::DirectionVector("Direction", &direction);
    float_t strength = force.Length();
    ImGui::DragFloat("Strength", &strength);
    force = direction * (strength == 0.f ? 1.f : strength);
    ImGui::ComboEnum("Easing type", &easingType);
}

void ColorOverLifetime::SetComputeShaderUniforms(const ComputeShader& computeShader) const
{
    computeShader.SetUniform("colorOverLifetime.colorMin", colorMin);
    computeShader.SetUniform("colorOverLifetime.colorMax", colorMax);
    computeShader.SetUniform("colorOverLifetime.easingType", easingType);
}

void ColorOverLifetime::RenderImGui()
{
    ImGui::ColorEdit4("Start color", colorMin.Data());
    ImGui::ColorEdit4("End color", colorMax.Data());
    ImGui::ComboEnum("Easing type", &easingType);
}

void ColorBySpeed::SetComputeShaderUniforms(const ComputeShader& computeShader) const
{
    computeShader.SetUniform("colorBySpeed.colorMin", colorMin);
    computeShader.SetUniform("colorBySpeed.colorMax", colorMax);
    computeShader.SetUniform("colorBySpeed.speedMin", speedMin);
    computeShader.SetUniform("colorBySpeed.speedMax", speedMax);
    computeShader.SetUniform("colorBySpeed.easingType", easingType);
}

void ColorBySpeed::RenderImGui()
{
    ImGui::ColorEdit4("Color min", colorMin.Data());
    ImGui::ColorEdit4("Color max", colorMax.Data());
    ImGui::DragFloat("Speed min", &speedMin);
    ImGui::DragFloat("Speed max", &speedMax);
    ImGui::ComboEnum("Easing type", &easingType);
}

void Renderer::RenderImGui()
{
    ImGuiUtils::SelectResource("texture", &texture, true);
}
