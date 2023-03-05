#include <iostream>

#include <renderer.hpp>

void mainLoop(const double deltaTime);

int main(int, char*[])
{
	mountain::Renderer renderer;
	renderer.Initialize();
	renderer.BindUserGameLoop(mainLoop);
	renderer.MainLoop();
	renderer.Shutdown();
}

void mainLoop(const double deltaTime)
{

}
