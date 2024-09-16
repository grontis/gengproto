#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <unordered_map>
#include <vector>

class EventManager
{
public:
    using KeyAction = std::function<void()>;

    EventManager();

    void handleEvents();
    void registerKeyAction(SDL_Scancode key, KeyAction action);
    void registerQuitAction(KeyAction action);

private:
    std::unordered_map<SDL_Scancode, std::vector<KeyAction>> keyActions;
    std::vector<KeyAction> quitActions;
};