#pragma once

#include <Mountain/Resource/ShaderBase.hpp>
#include <Mountain/Utils/FileSystemWatcher.hpp>

#include "Mountain/Game.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Utils/Color.hpp"

#include "Scenes/TestScene.hpp"

class GameExample : public Game
{
	static inline GameExample* m_Instance = nullptr;

public:
	STATIC_GETTER(GameExample&, , *m_Instance)

    explicit GameExample(const char_t* windowTitle);

	// Inherited from Game
	void LoadResources() override;
	void Initialize() override;
    void Shutdown() override;
	void Update() override;
	void Render() override;

	void RenderDebug() const;

	void RenderImGui();

	GETTER(TestScene*, Scene, m_ActiveScene)
	/// @brief Sets the next scene to be used. This will take effect on the next frame.
	void SetScene(TestScene* newScene);

private:
    List<TestScene*> m_Scenes;

	TestScene* m_ActiveScene = nullptr;
	TestScene* m_NextActiveScene = nullptr;

	Color m_ClearColor = Color::Black();

	bool_t m_EnableDebugRendering = true;

	FileSystemWatcher m_AssetsWatcher{ "assets" };

	FileSystemWatcher m_ShadersWatcher;
	List<Pointer<ShaderBase>> m_ShadersToReload;
	std::mutex m_ShadersToReloadMutex;

	void InitializeFileSystemWatchers();

    void ReloadShader(const std::filesystem::path& path);

	void HandleSceneChange();
};
