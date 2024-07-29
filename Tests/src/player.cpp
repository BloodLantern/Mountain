#include "player.hpp"

#include "audio/component/audio_listener.hpp"
#include "input/input.hpp"
#include "input/time.hpp"
#include "rendering/draw.hpp"
#include "resource/resource_manager.hpp"

Player::Player(const Vector2& position)  // NOLINT(clang-diagnostic-shadow-field)
    : Entity(position)
{
    AddComponent<Mountain::AudioListener>();
}

void Player::LoadResources()
{
    m_Texture = Mountain::ResourceManager::Get<Mountain::Texture>("assets/strawberry/normal00.png");
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

    position += movement * movementSpeed * Mountain::Time::GetDeltaTime();
}

void Player::Render()
{
    Entity::Render();

    Mountain::Draw::Texture(*m_Texture, position - m_Texture->GetSize() * 0.5f, Vector2::One(), 0.f, Mountain::Color::White());
}
