#include "Mountain/rendering/particle_system_modules.hpp"

#include <ImGui/imgui.h>

#include "Mountain/utils/imgui_utils.hpp"

using namespace Mountain::ParticleSystemModules;

bool_t Base::BeginImGui(uint32_t* const enabledModulesInt, const Types type, const char_t* const name) const
{
    ImGui::PushID(this);

    ImGui::CheckboxFlags("##enabled", enabledModulesInt, static_cast<uint32_t>(type));
    ImGui::SameLine();
    const bool_t result = ImGui::TreeNode(name);

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

void ColorOverLifetime::SetComputeShaderUniforms(const ComputeShader& computeShader, const Types enabledModules) const
{
    if (!(enabledModules & Types::ColorOverLifetime))
        return;

    computeShader.SetUniform("colorOverLifetime.start", start);
    computeShader.SetUniform("colorOverLifetime.end", end);
}

void ColorOverLifetime::RenderImGui(uint32_t* const enabledModulesInt)
{
    if (!BeginImGui(enabledModulesInt, Types::ColorOverLifetime, "ColorOverLifetime"))
        return;

    ImGui::ColorEdit4("Start", start.Data());
    ImGui::ColorEdit4("End", end.Data());

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
    if (!BeginImGui(enabledModulesInt, Types::ForceOverLifetime, "ForceOverLifetime"))
        return;

    Vector2 direction = force.Normalized();
    ImGuiUtils::DirectionVector("Direction", &direction);
    float_t strength = force.Length();
    ImGui::DragFloat("Strength", &strength);
    force = direction * (strength == 0.f ? 1.f : strength);

    EndImGui();
}
