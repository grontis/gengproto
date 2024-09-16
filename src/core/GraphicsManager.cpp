#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(std::string windowName, Uint32 initWidth, Uint32 initHeight)
{
    windowWidth = initWidth;
    windowHeight = initHeight;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
    }

    window = SDL_CreateWindow("gengproto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window)
    {
        SDL_Quit();
        throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
    }
}

GraphicsManager::~GraphicsManager()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void GraphicsManager::startFrame(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    clearScreen(r, g, b, a);
}

void GraphicsManager::draw(const GRectangle &rect) const
{
    setDrawColor(rect.color.r, rect.color.g, rect.color.b, rect.color.a);
    SDL_RenderFillRect(renderer, &rect.rect);
}

void GraphicsManager::render() const
{
    presentRenderer();
}

void GraphicsManager::clearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

void GraphicsManager::presentRenderer() const
{
    SDL_RenderPresent(renderer);
}

void GraphicsManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int GraphicsManager::getWindowWidth()
{
    return windowWidth;
}

int GraphicsManager::getWindowHeight()
{
    return windowHeight;
}

// TODO refactor this into a static Time class? What is the best practice for this c++?
void GraphicsManager::delay(Uint32 ms) const
{
    SDL_Delay(ms);
}

// TODO refactor this into a static Time class? What is the best practice for this c++?
Uint32 GraphicsManager::getTicks() const
{
    return SDL_GetTicks();
}
