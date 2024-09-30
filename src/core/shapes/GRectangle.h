#pragma once

#include <SDL2/SDL.h>

#include "Colors.h"

namespace core
{
    struct GRectangle
    {
        SDL_Rect rect;
        G_COLOR color;
        Uint8 alpha;

        GRectangle(int x, int y, int w, int h, G_COLOR color, Uint8 alpha);
    };
}
