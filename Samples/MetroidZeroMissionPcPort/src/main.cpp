#include "mzm_game.hpp"
#include "Mountain/core.hpp"

USE_DEDICATED_GPU

int32_t main(int32_t argc, char_t** argv)
{
    MzmGame{}.Play();

    return 0;
}
