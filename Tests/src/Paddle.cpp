#include "Paddle.hpp"

#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/scene/component/audio_listener.hpp"
#include "Mountain/scene/component/light_source.hpp"

Paddle::Paddle(const Vector2& pos)
    : Entity(pos)
{
    const auto listener = AddComponent<Mountain::AudioListener>();
    listener->SetVolume(0.f);
    
    const auto light = AddComponent<Mountain::LightSource>();
    light->intensity = 1.f;
    light->radius = 50.f;
}

void Paddle::LoadResources()
{
    m_Texture = Mountain::ResourceManager::Get<Mountain::Texture>("assets/strawberry/normal00.png");
}

void Paddle::Update()
{
    Entity::Update();
    
    Vector2 movement;
    if (Mountain::Input::GetKey(Mountain::Key::Left))
        movement.x = -1.f;
    if (Mountain::Input::GetKey(Mountain::Key::Right))
        movement.x =  1.f;
    if (Mountain::Input::GetKey(Mountain::Key::Up))
        movement.y = -1.f;
    if (Mountain::Input::GetKey(Mountain::Key::Down))
        movement.y =  1.f;

    position += movement.Normalized() * movementSpeed * Mountain::Time::GetDeltaTime();
}

void Paddle::Render()
{
    Entity::Render();

    Mountain::Draw::Texture(
        *m_Texture,
        position - m_Texture->GetSize() * 0.5f,
        Vector2::One(),
        0.f,
        Vector2::Zero(),
        Vector2::One(),
        Mountain::Color::White()
    );
}
