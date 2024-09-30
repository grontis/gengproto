#include "GraphicsManager.h"
#include "Colors.h"

namespace core
{
    GraphicsManager::GraphicsManager(std::string windowName, Uint32 initWidth, Uint32 initHeight)
    {
        _windowWidth = initWidth;
        _windowHeight = initHeight;

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
        }

        _window = SDL_CreateWindow("gengproto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   _windowWidth, _windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (!_window)
        {
            SDL_Quit();
            throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
        }

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!_renderer)
        {
            SDL_DestroyWindow(_window);
            SDL_Quit();
            throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
        }
    }

    GraphicsManager::~GraphicsManager()
    {
        if (_renderer)
            SDL_DestroyRenderer(_renderer);
        if (_window)
            SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void GraphicsManager::startFrame(core::G_COLOR color, Uint8 alpha) const
    {
        clearScreen(color, alpha);
    }

    void GraphicsManager::draw(const core::GRectangle &rect) const
    {
        setDrawColor(rect.color, rect.alpha);
        SDL_RenderFillRect(_renderer, &rect.rect);
    }

    void GraphicsManager::drawLine(int x1, int y1, int x2, int y2) const
    {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); // TODO parameter of color?
        SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
    }

    void GraphicsManager::render() const
    {
        presentRenderer();
    }

    void GraphicsManager::clearScreen(core::G_COLOR color, Uint8 alpha) const
    {
        // TODO any better data structure than tuple to use in this scenario?
        std::tuple<Uint8, Uint8, Uint8> colorValues = core::Colors::getColor(color);

        // TODO error handling here?
        Uint8 r = std::get<0>(colorValues);
        Uint8 g = std::get<1>(colorValues);
        Uint8 b = std::get<2>(colorValues);
        SDL_SetRenderDrawColor(_renderer, r, g, b, alpha);
        SDL_RenderClear(_renderer);
    }

    void GraphicsManager::presentRenderer() const
    {
        SDL_RenderPresent(_renderer);
    }

    void GraphicsManager::setDrawColor(core::G_COLOR color, Uint8 alpha) const
    {
        std::tuple<Uint8, Uint8, Uint8> colorValues = core::Colors::getColor(color);

        // TODO error handling here?
        Uint8 r = std::get<0>(colorValues);
        Uint8 g = std::get<1>(colorValues);
        Uint8 b = std::get<2>(colorValues);

        SDL_SetRenderDrawColor(_renderer, r, g, b, alpha);
    }

    int GraphicsManager::getWindowWidth()
    {
        return _windowWidth;
    }

    int GraphicsManager::getWindowHeight()
    {
        return _windowHeight;
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
}
