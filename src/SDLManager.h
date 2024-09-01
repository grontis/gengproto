#pragma once

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

class SDLManager {
public:
    SDLManager();
    ~SDLManager();

    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};