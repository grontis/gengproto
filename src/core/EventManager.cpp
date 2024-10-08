#include "EventManager.h"

namespace core
{
    EventManager::EventManager() {}

    void EventManager::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                for (auto &action : _quitActions)
                {
                    action();
                }
            }
            else if (event.type == SDL_KEYDOWN && !event.key.repeat)
            {
                SDL_Scancode key = event.key.keysym.scancode;
                if (_keyDownActions.find(key) != _keyDownActions.end())
                {
                    for (const auto &action : _keyDownActions[key])
                    {
                        action();
                    }
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                SDL_Scancode key = event.key.keysym.scancode;
                if (_keyUpActions.find(key) != _keyUpActions.end())
                {
                    for (const auto &action : _keyUpActions[key])
                    {
                        action();
                    }
                }
            }
        }

        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        for (const auto &pair : _keyHeldActions)
        {
            SDL_Scancode key = pair.first;
            if (currentKeyStates[key])
            {
                for (const auto &action : pair.second)
                {
                    action();
                }
            }
        }
    }

    void EventManager::registerKeyAction(SDL_Scancode key, KEY_EVENT_TYPE keyEventType, KeyAction action)
    {
        switch (keyEventType)
        {
        case KEYDOWN:
            _keyDownActions[key].push_back(action);
            break;
        case KEYUP:
            _keyUpActions[key].push_back(action);
            break;
        case KEYHELD:
            _keyHeldActions[key].push_back(action);
            break;
        }
    }

    void EventManager::registerQuitAction(KeyAction action)
    {
        _quitActions.push_back(action);
    }
}
