#pragma once

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

class SDLManager {
public:
    SDLManager();
    ~SDLManager();

    void clearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
    void presentRenderer() const;
    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
    void drawRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
    void delay(Uint32 ms) const;
    Uint32 getTicks() const;

    int getWindowWidth();
    int getWindowHeight();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    //TODO set dynamically based on current window.
    //TODO need to implement window resizing
    const int windowWidth = 2560;
    const int windowHeight = 1440;
};