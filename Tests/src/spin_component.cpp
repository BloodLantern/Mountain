#include "spin_component.hpp"

#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/scene/entity.hpp"
#include "Mountain/scene/component/audio_source.hpp"

#include "test_game.hpp"

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
    Mountain::Draw::Circle(m_Entity->position, 5.f, false, Mountain::Color::Fuchsia());
}
