#include "game_of_life.hpp"

USE_DEDICATED_GPU

int main(int32_t, char_t**)
{
    GameOfLife* game = new GameOfLife("Conway's Game of Life");
    game->Initialize();
    game->MainLoop();
    game->Shutdown();
    delete game;

    return 0;
}
