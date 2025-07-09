#pragma once

#include <Mountain/Ecs/Scene.hpp>

using namespace Mountain;  // NOLINT(clang-diagnostic-header-hygiene)

class TestScene : public Scene
{
public:
	using Base = Scene;

    explicit TestScene(std::string name);

    virtual void LoadPersistentResources();

    virtual void UnloadPersistentResources();

    void Begin() override;

    void Render() override;

    virtual void BeforeRenderImGui();

    virtual void RenderImGui();

    virtual void AfterRenderImGui();

    void End() override;

    GETTER(const std::string&, Name, m_Name)

private:
    std::string m_Name;

    /// @brief Called in @c Begin()
    virtual void LoadResources();

    /// @brief Called in @c End()
    virtual void UnloadResources();
};
