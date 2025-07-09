#include "Scenes/TestScene.hpp"

#include <Mountain/Rendering/Draw.hpp>
#include <Mountain/Utils/ImGuiUtils.hpp>

TestScene::TestScene(std::string name)
    : m_Name{std::move(name)}
{
}

void TestScene::LoadPersistentResources()
{
}

void TestScene::UnloadPersistentResources()
{
}

void TestScene::Begin()
{
    Scene::Begin();

    LoadResources();
}

void TestScene::Render()
{
    Scene::Render();

    Mountain::Draw::Clear(Mountain::Color::Black());
}

void TestScene::BeforeRenderImGui()
{
    ImGui::PushID(this);
}

void TestScene::RenderImGui()
{
}

void TestScene::AfterRenderImGui()
{
    ImGui::PopID();
}

void TestScene::End()
{
    UnloadResources();

    Scene::End();
}

void TestScene::LoadResources()
{
}

void TestScene::UnloadResources()
{
}
