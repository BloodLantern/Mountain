#include "spin_component.hpp"

#include "test_game.hpp"
#include "audio/component/audio_source.hpp"
#include "input/time.hpp"
#include "rendering/draw.hpp"
#include "resource/resource_manager.hpp"
#include "scene/entity.hpp"

void SpinComponent::Added()
{
    Mountain::AudioSource* source = m_Entity->AddComponent<Mountain::AudioSource>();
    source->audioTrack = Mountain::ResourceManager::Get<Mountain::AudioTrack>("assets/sfx.ogg");
    source->SetLooping(true);
    source->SetVolume(0.2f);
    source->Play();
}

void SpinComponent::Update()
{
    const float_t time = Mountain::Time::GetTotalTime() * 0.5f;
    constexpr Vector2i halfResolution(BaseResolution.x / 2, BaseResolution.y / 2);
    m_Entity->position = { std::cos(time) * halfResolution.x + halfResolution.x, std::sin(time) * halfResolution.y + halfResolution.y };
}

void SpinComponent::DebugRender()
{
    Mountain::Draw::Circle(m_Entity->position, 5.f, Mountain::Color::Fuchsia());
}
