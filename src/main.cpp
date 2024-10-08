#include <iostream>

#include "Tetris.h"

void runTetris()
{
    tetris::Tetris tetris;
    tetris.run();
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