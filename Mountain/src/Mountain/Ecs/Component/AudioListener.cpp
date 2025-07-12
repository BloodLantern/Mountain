#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Ecs/Component/AudioListener.hpp"

#include <array>

#include <ImGui/imgui.h>

#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Audio/Sound.hpp"
#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Input/Time.hpp"

using namespace Mountain;

void AudioListener::Update()
{
    m_Listener.SetPosition(m_Entity->position, dopplerEffect);
}

float_t AudioListener::GetVolume() const { return m_Listener.GetVolume(); }

void AudioListener::SetVolume(const float_t newVolume)
{
    m_Listener.SetVolume(newVolume);
}
