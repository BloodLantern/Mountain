#include "Common.hpp"

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

void TestScene::LoadResources()
{
}

void TestScene::Begin()
{
    Scene::Begin();
}

void TestScene::Render()
{
    Scene::Render();

    Draw::Clear(Color::Black());
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
    Scene::End();
}

void TestScene::UnloadResources()
{
}
