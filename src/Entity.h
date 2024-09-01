#pragma once

#include <SDL2/SDL.h>

struct Entity {
    SDL_Rect rect;
    SDL_Color color;

    Entity(int x, int y, int w, int h, SDL_Color c);

    void render(SDL_Renderer* renderer) const;
    void move(int dx, int dy);
};