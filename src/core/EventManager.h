#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

using KeyAction = std::function<void()>;

namespace core
{
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
        void registerKeyAction(SDL_Scancode key, KEY_EVENT_TYPE keyEventType, KeyAction action);
        void registerQuitAction(KeyAction action);

    private:
        std::unordered_map<SDL_Scancode, std::vector<KeyAction>> _keyDownActions;
        std::unordered_map<SDL_Scancode, std::vector<KeyAction>> _keyUpActions;
        std::unordered_map<SDL_Scancode, std::vector<KeyAction>> _keyHeldActions;
        std::vector<KeyAction> _quitActions;
    };
}
