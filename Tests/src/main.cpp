#include <iostream>

#include "test_game.hpp"
#include "Mountain/globals.hpp"
#include "Mountain/utils/logger.hpp"

USE_DEDICATED_GPU

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

int32_t main(int32_t, char_t**)
{
	std::cout << "Starting program, waiting for Live++ initialization..." << std::endl;

	// create a synchronized agent, loading the Live++ agent from the given path, e.g. "ThirdParty/LivePP"
	lpp::LppSynchronizedAgent lppAgent = lpp::LppCreateSynchronizedAgent(nullptr, L"LivePP");

	// bail out in case the agent is not valid
	if (!LppIsValidSynchronizedAgent(&lppAgent))
		return 1;

	// enable Live++ for all loaded modules
	lppAgent.EnableModule(lpp::LppGetCurrentModulePath(), lpp::LPP_MODULES_OPTION_ALL_IMPORT_MODULES, nullptr, &LppFilterModuleCallback);

	Mountain::NoBinaryResources = true;
	Mountain::BuiltinShadersPath = "Mountain/shaders";

	GameExample* game = new GameExample("Mountain tests");
	game->Initialize();

	// run the main loop
	while (game->NextFrame())
	{
		// listen to hot-reload and hot-restart requests
		if (lppAgent.WantsReload(lpp::LPP_RELOAD_OPTION_SYNCHRONIZE_WITH_RELOAD))
		{
			// client code can do whatever it wants here, e.g. synchronize across several threads, the network, etc.
			// ...

			// Not necessary, but we might as well synchronize the console logs
			Mountain::Logger::Synchronize();

			lppAgent.Reload(lpp::LPP_RELOAD_BEHAVIOUR_WAIT_UNTIL_CHANGES_ARE_APPLIED);
		}

		if (lppAgent.WantsRestart())
		{
			// client code can do whatever it wants here, e.g. finish logging, abandon threads, etc.
			// ...

			game->Shutdown();
			delete game;

			lppAgent.Restart(lpp::LPP_RESTART_BEHAVIOUR_DEFAULT_EXIT, 0, nullptr);
			break;
		}
	}

	game->Shutdown();
	delete game;

	// destroy the Live++ agent
	LppDestroySynchronizedAgent(&lppAgent);

    return 0;
}
