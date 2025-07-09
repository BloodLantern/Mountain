#include "Scenes/SpriteAnimationsScene.hpp"

#include <Mountain/Window.hpp>
#include <Mountain/FileSystem/FileManager.hpp>
#include <Mountain/Rendering/Draw.hpp>
#include <Mountain/Resource/ResourceManager.hpp>

SpriteAnimationsScene::SpriteAnimationsScene()
    : Base{"Sprite Animations"}
{
    m_Entity = new Entity;
    m_Sprite = m_Entity->AddComponent<Sprite>();

    m_Sprite->name = "assets/strawberry/normal";

    m_Entities.AddNow(m_Entity);
}

void SpriteAnimationsScene::Render()
{
    TestScene::Render();

    const Pointer<Texture>& currentTexture = m_Sprite->Get();
    Draw::Texture(*currentTexture, Window::GetSize() * 0.5f - currentTexture->GetSize() * 0.5f);
}

void SpriteAnimationsScene::RenderImGui()
{
    TestScene::RenderImGui();

    float_t frameDuration = m_Sprite->frameDuration;
    ImGui::InputFloat("Frame duration", &frameDuration, 0.001f, 0.01f);
    frameDuration = std::min(frameDuration, 0.f);
}

void SpriteAnimationsScene::LoadResources()
{
    const Pointer<Directory>& directory = FileManager::LoadDirectory("assets/strawberry");
    for (const Pointer<File>& file : directory->GetChildFiles())
        ResourceManager::Load<Texture>(file);

    m_Sprite.SetupTextures();
}

void SpriteAnimationsScene::UnloadResources()
{
    const Pointer<Directory>& directory = FileManager::Get<Directory>("assets/strawberry");

    for (const Pointer<File>& file : directory->GetChildFiles())
        ResourceManager::Unload<Texture>(Utils::DynamicPointerCast<Texture>(file->GetResource()));

    FileManager::Unload(static_cast<Pointer<Entry>>(directory));
}
