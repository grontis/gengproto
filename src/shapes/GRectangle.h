#pragma once

#include <SDL2/SDL.h>

struct GRectangle {
    SDL_Rect rect;
    SDL_Color color;

    GRectangle(int x, int y, int w, int h, SDL_Color c);
};