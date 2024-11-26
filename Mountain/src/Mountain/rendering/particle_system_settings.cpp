#include "Mountain/rendering/particle_system_settings.hpp"

#include <ImGui/imgui.h>

#include "Mountain/input/time.hpp"
#include "Mountain/rendering/particle_system.hpp"
#include "Mountain/utils/imgui_utils.hpp"

using namespace Mountain::ParticleSystemSettings;

bool_t Base::RenderImGuiHeader(const std::string_view typeName)
{
    ImGui::Checkbox(std::format("##enabled{}", typeName).c_str(), &enabled);
    ImGui::SameLine();
    if (!ImGui::TreeNode(typeName.data()))
        return false;

    if (!enabled)
        ImGui::BeginDisabled();

    return true;
}

void Base::RenderImGuiFooter()
{
    if (!enabled)
        ImGui::EndDisabled();

    ImGui::TreePop();
}

void ColorOverLifetime::Update(ParticleSystem& system, Particle& particle, float_t) const
{
    particle.color = Calc::Lerp(start, end, 1.f - particle.lifetime / system.particleLifetime, function);
}

void ColorOverLifetime::RenderImGui(ParticleSystem&)
{
    if (!RenderImGuiHeader("ColorOverLifetime"))
        return;

    ImGui::ColorEdit4("Start color", start.Data());
    ImGui::ColorEdit4("End color", end.Data());

    ImGuiUtils::ComboEaser("Function", &function);

    RenderImGuiFooter();
}

void Acceleration::Update(ParticleSystem&, Particle& particle, const float_t deltaTime) const
{
    particle.velocity += acceleration * deltaTime;
}

void Acceleration::RenderImGui(ParticleSystem&)
{
    if (!RenderImGuiHeader("Acceleration"))
        return;

    Vector2 direction = acceleration.Normalized();
    ImGuiUtils::DirectionVector("Direction", &direction);
    float_t strength = acceleration.Length();
    ImGui::DragFloat("Strength", &strength);
    acceleration = direction * (strength == 0.f ? 1.f : strength);

    RenderImGuiFooter();
}
