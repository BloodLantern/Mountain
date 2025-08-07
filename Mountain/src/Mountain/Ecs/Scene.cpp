#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Ecs/Scene.hpp"

#include "Mountain/Ecs/Entity.hpp"

using namespace Mountain;

void Scene::Begin()
{
    for (Entity* entity : m_Entities)
        entity->SceneBegin();
}

void Scene::BeforeUpdate()
{
    m_Entities.UpdateLists();
    const auto onNextFrameCopy = onNextFrame;
    onNextFrame.Clear();
    onNextFrameCopy();
}

void Scene::Update()
{
    for (Entity* entity : m_Entities)
        entity->Update();
}

void Scene::AfterUpdate()
{
    const auto onEndOfCurrentFrameCopy = onEndOfCurrentFrame;
    onEndOfCurrentFrame.Clear();
    onEndOfCurrentFrameCopy();
}

void Scene::BeforeRender()
{
}

void Scene::Render()
{
    for (Entity* entity : m_Entities)
        entity->Render();
}

void Scene::AfterRender()
{
}

void Scene::BeforeRenderDebug()
{
}

void Scene::RenderDebug()
{
    for (Entity* entity : m_Entities)
        entity->RenderDebug();
}

void Scene::AfterRenderDebug()
{
}

void Scene::End()
{
    for (Entity* entity : m_Entities)
        entity->SceneEnd();
}
