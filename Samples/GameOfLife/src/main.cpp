#include "gol.hpp"

USE_DEDICATED_GPU

int main(int32_t, char_t**)
{
    Gol* game = new Gol("Conway's Game of Life");
    game->Initialize();
    game->MainLoop();
    game->Shutdown();
    delete game;

    return 0;
}
