#pragma once

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
#include "GRectangle.h"

class GraphicsManager
{
public:
    GraphicsManager(std::string windowName, Uint32 initWidth, Uint32 initHeigh);
    ~GraphicsManager();

    void startFrame(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
    void draw(const GRectangle &rect) const;
    void render() const;

    //TODO refactor into Time class
    void delay(Uint32 ms) const;
    Uint32 getTicks() const;

    int getWindowWidth();
    int getWindowHeight();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // TODO set dynamically based on current window.
    // TODO need to implement window resizing
    Uint32 windowWidth;
    Uint32 windowHeight;

    void clearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
    void presentRenderer() const;
    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
};