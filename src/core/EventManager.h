#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <unordered_map>
#include <vector>

using KeyAction = std::function<void()>;

typedef enum
{
    KEYDOWN,
    KEYUP,
    KEYHELD
} KEY_EVENT_TYPE;

class EventManager
{
public:
    EventManager();

    void handleEvents();
    void registerKeyAction(SDL_Scancode key, KEY_EVENT_TYPE keyEventType, KeyAction action) ;
    void registerQuitAction(KeyAction action);

private:
    std::unordered_map<SDL_Scancode, std::vector<KeyAction>> keyDownActions;
    std::unordered_map<SDL_Scancode, std::vector<KeyAction>> keyUpActions;
    std::unordered_map<SDL_Scancode, std::vector<KeyAction>> keyHeldActions;
    std::vector<KeyAction> quitActions;
};