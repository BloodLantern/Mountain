#include "Mountain/PrecompiledHeader.hpp"
#include "Mountain/Ecs/Component/Sprite.hpp"

#include "Mountain/Input/Time.hpp"
#include "Mountain/Resource/ResourceManager.hpp"

using namespace Mountain;

Sprite::Sprite(std::string spriteName)
    : name(std::move(spriteName))
{
    SetupTextures();
}

Sprite::Sprite(std::string spriteName, const float_t frameDuration)
    : name(std::move(spriteName))
    , frameDuration(frameDuration)
{
    SetupTextures();
}

void Sprite::Update()
{
    m_UpdateTimer -= Time::GetDeltaTime();

    if (m_UpdateTimer < 0.f)
    {
        m_UpdateTimer = frameDuration;
        m_CurrentIndex = (m_CurrentIndex + 1) % m_Textures.GetSize();
    }
}

void Sprite::SetupTextures()
{
    // Find all Textures with a name as follows: 'Sprite::name + any number'
    ResourceManager::FindAll<Texture>(
        [this](const Pointer<Texture>& t) -> bool_t
        {
            const File& f = *t->GetFile();
            const std::string& fName = f.GetPathNoExtension();
            if (!fName.starts_with(name))
                return false;

            const std::string& index = fName.substr(name.size());
            if (std::ranges::find_if(index, [](auto c) -> bool_t { return !std::isdigit(c); }) != index.end())
                return false;

            return true;
        },
        &m_Textures
    );

    m_Textures.Sort([](const Pointer<Texture>& a, const Pointer<Texture>& b) -> bool_t { return a->GetName() < b->GetName(); });

    m_UpdateTimer = frameDuration;
}

const Pointer<Texture>& Sprite::Get() const { return m_Textures[m_CurrentIndex]; }
