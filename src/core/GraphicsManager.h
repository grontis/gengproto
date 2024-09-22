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

    void startFrame(core::G_COLOR color, Uint8 alpha) const;

    //TODO implement "generic" draw method that can be either overridden, or provided inline actions
    void draw(const core::GRectangle &rect) const;
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

    void clearScreen(core::G_COLOR color, Uint8 alpha) const;
    void presentRenderer() const;
    void setDrawColor(core::G_COLOR color, Uint8 alpha) const;
};