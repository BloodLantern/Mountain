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
    m_ImGuiHeaderOpen = Mountain::ImGuiUtils::PushCollapsingHeader(m_Name.c_str());
}

void TestScene::RenderImGui()
{
}

void TestScene::AfterRenderImGui()
{
    if (m_ImGuiHeaderOpen)
        Mountain::ImGuiUtils::PopCollapsingHeader();
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
