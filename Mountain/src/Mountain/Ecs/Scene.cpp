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
}

void Scene::Update()
{
    for (Entity* entity : m_Entities)
        entity->Update();
}

void Scene::AfterUpdate()
{
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

void Scene::RenderDebug()
{
    for (Entity* entity : m_Entities)
        entity->RenderDebug();
}

void Scene::End()
{
    for (Entity* entity : m_Entities)
        entity->SceneEnd();
}

void Scene::GainFocus()
{
}

void Scene::LoseFocus()
{
}
