#pragma once

#include "Common.hpp"

#include <Mountain/Ecs/Scene.hpp>

class TestScene : public Scene
{
public:
	using Base = Scene;

    explicit TestScene(std::string name);

    virtual void LoadPersistentResources();

    virtual void UnloadPersistentResources();

    /// @brief Called right before @c Begin()
    virtual void LoadResources();

    /// @brief Called right after @c LoadResources()
    void Begin() override;

    void Render() override;

    virtual void BeforeRenderImGui();

    virtual void RenderImGui();

    virtual void AfterRenderImGui();

    /// @brief Called right after @c UnloadResources()
    void End() override;

    /// @brief Called right after @c End()
    virtual void UnloadResources();

    GETTER(const std::string&, Name, m_Name)

private:
    std::string m_Name;
};
