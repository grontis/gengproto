#include "EventManager.h"

EventManager::EventManager() {}

void EventManager::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            for (auto &action : quitActions)
            {
                action();
            }
        }
    }

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    for (const auto &pair : keyActions)
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

void EventManager::registerKeyAction(SDL_Scancode key, KeyAction action)
{
    keyActions[key].push_back(action);
}

void EventManager::registerQuitAction(KeyAction action)
{
    quitActions.push_back(action);
}