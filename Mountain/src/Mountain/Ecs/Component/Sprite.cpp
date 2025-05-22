module Mountain:Ecs_Component_Sprite;
import :Ecs_Component_Sprite;

import :Ecs_Entity;
import :Input_Time;
import :Resource_ResourceManager;

using namespace Mountain;

Sprite::Sprite(std::string spriteName)
    : m_Name(std::move(spriteName))
{
    SetupTextures();
}

Sprite::Sprite(std::string spriteName, const float_t frameDuration)
    : m_Name(std::move(spriteName))
    , m_FrameDuration(frameDuration)
{
    SetupTextures();
}

void Sprite::Update()
{
    m_UpdateTimer -= Time::GetDeltaTime();

    if (m_UpdateTimer < 0.f)
    {
        m_UpdateTimer = m_FrameDuration;
        m_CurrentIndex = (m_CurrentIndex + 1) % m_Textures.GetSize();
    }
}

void Sprite::SetupTextures()
{
    // Find all Textures with a name as follows: m_Name + any number
    ResourceManager::FindAll<Texture>(
        [this](const Pointer<Texture>& t) -> bool_t
        {
            const File& f = *t->GetFile();
            const std::string& name = f.GetPathNoExtension();
            if (!name.starts_with(m_Name))
                return false;

            std::string&& index = name.substr(m_Name.size());
            if (std::ranges::find_if(index, [](auto c) -> bool_t { return !std::isdigit(c); }) != index.end())
                return false;

            return true;
        },
        &m_Textures
    );

    std::ranges::sort(m_Textures, [](auto&& a, auto&& b) -> bool_t { return a->GetName() < b->GetName(); });

    m_UpdateTimer = m_FrameDuration;
}

const Pointer<Texture>& Sprite::Get() { return m_Textures[m_CurrentIndex]; }

const std::string& Sprite::GetName() const { return m_Name; }

void Sprite::SetName(const std::string& name) { m_Name = name; }

float_t Sprite::GetFrameDuration() const { return m_FrameDuration; }

void Sprite::SetFrameDuration(const float_t frameDuration) { m_FrameDuration = frameDuration; }

const List<Pointer<Texture>>& Sprite::GetTextures() const { return m_Textures; }

size_t Sprite::GetCurrentIndex() const { return m_CurrentIndex; }

float_t Sprite::GetUpdateTimer() const { return m_UpdateTimer; }
