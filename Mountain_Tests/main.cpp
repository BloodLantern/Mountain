#include <iostream>

#include "game_example.hpp"

int main(int, char*[])
{
	test::GameExample game("Mountain tests");
	game.Initialize();
	game.MainLoop();
	game.Shutdown();
}
