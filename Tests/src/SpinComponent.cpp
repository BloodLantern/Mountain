#include "Common.hpp"

#include "SpinComponent.hpp"

#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Ecs/Component/AudioSource.hpp"
#include "Mountain/Input/Time.hpp"
#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Resource/ResourceManager.hpp"

#include "TestGame.hpp"

void SpinComponent::Added()
{
    AudioSource* source = m_Entity->AddComponent<AudioSource>();
    source->audioTrack = ResourceManager::Get<AudioTrack>("assets/sfx.ogg");
    source->SetLooping(true);
    source->SetVolume(0.2f);
    source->Play();
}

void SpinComponent::Update()
{
    /*const float_t time = Mountain::Time::GetTotalTime() * 0.5f;
    constexpr Vector2i halfResolution(BaseResolution.x / 2, BaseResolution.y / 2);
    m_Entity->position = { std::cos(time) * halfResolution.x + halfResolution.x, std::sin(time) * halfResolution.y + halfResolution.y };*/
}

void SpinComponent::DebugRender()
{
    Draw::Circle(m_Entity->position, 5.f, 1.f, Vector2::One(), Color::Fuchsia());
}
