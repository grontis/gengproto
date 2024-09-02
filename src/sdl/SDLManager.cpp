#include "SDLManager.h"

SDLManager::SDLManager() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
    }

    window = SDL_CreateWindow("gengproto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
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

void SDLManager::clearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

void SDLManager::presentRenderer() const {
    SDL_RenderPresent(renderer);
}

void SDLManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDLManager::drawRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    setDrawColor(r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

void SDLManager::delay(Uint32 ms) const {
    SDL_Delay(ms);
}

Uint32 SDLManager::getTicks() const {
    return SDL_GetTicks();
}

int SDLManager::getWindowWidth() {
    return windowWidth;
}

int SDLManager::getWindowHeight() {
    return windowHeight;
}