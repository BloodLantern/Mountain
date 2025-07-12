#include "Common.hpp"

#include "Player.hpp"

#include "Mountain/Ecs/Component/AudioListener.hpp"
#include "Mountain/Input/Input.hpp"
#include "Mountain/Input/Time.hpp"
#include "Mountain/Rendering/Draw.hpp"

Player::Player(const Vector2& pos, Mountain::LightSource& lightSource)
    : Entity(pos)
    , light(&lightSource)
{
    const auto listener = AddComponent<Mountain::AudioListener>();
    listener->SetVolume(0.f);

    lightSource.intensity = 1.f;
    lightSource.radius = 50.f;
}

void Player::LoadResources()
{
    sprite = AddComponent<Mountain::Sprite>("assets/strawberry/normal");
}

void Player::Update()
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
    light->position = position;
}

void Player::Render()
{
    Entity::Render();

    Mountain::Draw::Texture(
        *sprite->Get(),
        position,
        Vector2::One(),
        0.f,
        Vector2::One() * 0.5f,
        Vector2::Zero(),
        Vector2::One(),
        Mountain::Color::White()
    );
}
