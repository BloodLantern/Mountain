#include <iostream>

#include "game_example.hpp"

int main(int, char*[])
{
	test::GameExample game;
	game.Initialize();
	game.MainLoop();
	game.Shutdown();
}
