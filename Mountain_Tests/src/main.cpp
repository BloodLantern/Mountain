#include <iostream>

#include "game_example.hpp"

#include <run_length_encoding.hpp>

int main(int, char*[])
{
	/*test::GameExample game("Mountain tests");
	game.Initialize();
	game.MainLoop();
	game.Shutdown();*/

	std::cout << mountain::RunLengthEncoding::Encode("0000001110121010") << std::endl;
	std::cout << mountain::RunLengthEncoding::Decode(mountain::RunLengthEncoding::Encode("0000001110121010")) << std::endl;
}
