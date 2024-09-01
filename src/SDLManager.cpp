#include "SDLManager.h"

SDLManager::SDLManager() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
    }

    window = SDL_CreateWindow("gengproto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        SDL_Quit();
        throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
    }
}

SDLManager::~SDLManager() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* SDLManager::getRenderer() const {
    return renderer;
}