#include "Common.hpp"

#include <iostream>

#include <Mountain/Rendering/Renderer.hpp>

#include "TestGame.hpp"
#include "Mountain/globals.hpp"

USE_DEDICATED_GPU

// To use Live++ on certain machines only (those that have a license, for example),
// define the environment variable MOUNTAIN_LPP and give it the value USE_LPP.
// It will only be enabled in the Debug configuration.

#ifdef USE_LPP
#include "Mountain/Utils/Logger.hpp"
// include the API for Windows, 64-bit, C++
#include "LPP_API_x64_CPP.h"

namespace
{
	bool LppFilterModuleCallback(void*, const wchar_t* const path)
	{
		const std::wstring str = path;
		if (str.contains(L"Tests.exe") || str.contains(L"Mountain.dll"))
			return true;
		return false;
	}
}
#endif

#if defined(ENVIRONMENT_WINDOWS) && defined(NDEBUG)
#include "Mountain/Utils/Windows.hpp"

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main(int, char**)
#endif
{
#ifdef USE_LPP
	std::println(std::cout, "Starting program, waiting for Live++ initialization...");
	std::flush(std::cout);

	// create a synchronized agent, loading the Live++ agent from the given path, e.g. "ThirdParty/LivePP"
	lpp::LppSynchronizedAgent lppAgent = lpp::LppCreateSynchronizedAgent(nullptr, L"LivePP");

	// bail out in case the agent is not valid
	if (!LppIsValidSynchronizedAgent(&lppAgent))
	{
		std::println(std::cerr, "Couldn't initialize Live++, exiting now");
		std::flush(std::cerr);
		return EXIT_FAILURE;
	}

	// enable Live++ for all loaded modules
	lppAgent.EnableModule(lpp::LppGetCurrentModulePath(), lpp::LPP_MODULES_OPTION_ALL_IMPORT_MODULES, nullptr, &LppFilterModuleCallback);
#endif

	NoBinaryResources = true;
	BuiltinShadersPath = "../Mountain/shaders_internal";
	BuiltinAssetsPath = "../Mountain/assets_internal";
	BreakOnGraphicsError = true;

	TestGame* game = new TestGame("Mountain tests");

#ifdef USE_LPP
	game->LoadResources();
	game->Initialize();

	game->Start();

	// run the main loop
	while (game->NextFrame())
	{
		// listen to hot-reload and hot-restart requests
		if (lppAgent.WantsReload(lpp::LPP_RELOAD_OPTION_SYNCHRONIZE_WITH_RELOAD))
		{
			// client code can do whatever it wants here, e.g., synchronize across several threads, the network, etc.
			// ...

			Logger::LogInfo("Loading C++ hot reload changes...");
			// Not necessary, but we might as well synchronize the console logs
			Logger::Synchronize();
			Renderer::DebugString("Loading C++ hot reload changes...", 5.f);

			lppAgent.Reload(lpp::LPP_RELOAD_BEHAVIOUR_WAIT_UNTIL_CHANGES_ARE_APPLIED);
		}

		if (lppAgent.WantsRestart())
		{
			// client code can do whatever it wants here, e.g., finish logging, abandon threads, etc.
			// ...

			Logger::LogInfo("Hot restarting application");

			game->Shutdown();
			delete game;

			lppAgent.Restart(lpp::LPP_RESTART_BEHAVIOUR_DEFAULT_EXIT, 0, nullptr);
			break;
		}
	}

	game->Shutdown();
#else
	game->Play();
#endif

	delete game;

#ifdef USE_LPP
	// destroy the Live++ agent
	LppDestroySynchronizedAgent(&lppAgent);
#endif

    return EXIT_SUCCESS;
}
