#include "Common.hpp"

#include "Scenes/SpriteAnimationsScene.hpp"

#include <Mountain/Window.hpp>
#include <Mountain/FileSystem/FileManager.hpp>
#include <Mountain/Rendering/Draw.hpp>
#include <Mountain/Resource/ResourceManager.hpp>
#include <Mountain/Utils/ImGuiUtils.hpp>

SpriteAnimationsScene::SpriteAnimationsScene()
    : Base{"Sprite Animations"}
{
    m_Entity = new Entity;
    m_Sprite = m_Entity->AddComponent<Sprite>();

    m_Sprite->name = "assets/strawberry/normal";

    m_Entities.AddNow(m_Entity);
}

void SpriteAnimationsScene::LoadResources()
{
    const Pointer<Directory>& directory = FileManager::LoadDirectory("assets/strawberry");
    for (const Pointer<File>& file : directory->GetChildFiles())
        ResourceManager::Load<Texture>(file);

    m_Sprite->SetupTextures();
}

void SpriteAnimationsScene::Render()
{
    TestScene::Render();

    const Pointer<Texture>& currentTexture = m_Sprite->Get();
    const Vector2i currentTextureSize = currentTexture->GetSize();
    const Vector2i windowSize = Window::GetSize();

    const Vector2 drawScale = 0.5f * Vector2::One()
        * (static_cast<float_t>(std::min(windowSize.x, windowSize.y)) / static_cast<float_t>(std::min(currentTextureSize.x, currentTextureSize.y)));

    Draw::Texture(*currentTexture, windowSize * 0.5f - currentTextureSize * 0.5f * drawScale, drawScale, m_Rotation, m_Origin);
}

void SpriteAnimationsScene::RenderImGui()
{
    TestScene::RenderImGui();

    float_t frameDuration = m_Sprite->frameDuration;
    ImGui::InputFloat("Frame duration", &frameDuration, 0.001f, 0.01f);
    m_Sprite->frameDuration = std::max(frameDuration, 0.f);

    ImGui::DragAngle("Rotation", &m_Rotation);
    ImGuiUtils::GridPlotting("Origin", &m_Origin, 0, 1);
}

void SpriteAnimationsScene::UnloadResources()
{
    const Pointer<Directory>& directory = FileManager::Get<Directory>("assets/strawberry");

    for (const Pointer<File>& file : directory->GetChildFiles())
        ResourceManager::Unload(file->GetResource());

    FileManager::Unload(directory);
}
