#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Ecs/Scene.hpp"

#include "Mountain/Ecs/Entity.hpp"

using namespace Mountain;

void Scene::Begin()
{
    ZoneScoped;

    for (Entity* entity : m_Entities)
        entity->SceneBegin();
}

void Scene::BeforeUpdate()
{
    ZoneScoped;

    m_Entities.UpdateLists();
    const auto onNextFrameCopy = onNextFrame;
    onNextFrame.Clear();
    onNextFrameCopy();
}

void Scene::Update()
{
    ZoneScoped;

    for (Entity* entity : m_Entities)
        entity->Update();
}

void Scene::AfterUpdate()
{
    ZoneScoped;

    const auto onEndOfCurrentFrameCopy = onEndOfCurrentFrame;
    onEndOfCurrentFrame.Clear();
    onEndOfCurrentFrameCopy();
}

void Scene::BeforeRender()
{
}

void Scene::Render()
{
    ZoneScoped;

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
    ZoneScoped;

    for (Entity* entity : m_Entities)
        entity->RenderDebug();
}

void Scene::AfterRenderDebug()
{
}

void Scene::End()
{
    ZoneScoped;

    for (Entity* entity : m_Entities)
        entity->SceneEnd();
}
