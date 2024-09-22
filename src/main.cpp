#include <iostream>

#include "Game.h"
#include "Tetris.h"

void runTetris()
{
    Tetris tetris;
    tetris.run();
}

void runDemoGame()
{
    Game game;
    game.run();
}

int main(int argc, char *argv[])
{
    try
    {
        runTetris();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}