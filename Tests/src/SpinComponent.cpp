#include "SpinComponent.hpp"

#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Ecs/Component/AudioSource.hpp"
#include "Mountain/Input/Time.ixx"
#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Resource/ResourceManager.ixx"

#include "TestGame.hpp"

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
    Mountain::Draw::Circle(m_Entity->position, 5.f, Vector2::One(), Mountain::Color::Fuchsia());
}
