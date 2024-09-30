#include "EventManager.h"

EventManager::EventManager() {}

void EventManager::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            for (auto &action : quitActions) {
                action();
            }
        } else if (event.type == SDL_KEYDOWN && !event.key.repeat) {
            SDL_Scancode key = event.key.keysym.scancode;
            if (keyDownActions.find(key) != keyDownActions.end()) {
                for (const auto &action : keyDownActions[key]) {
                    action();
                }
            }
        } else if (event.type == SDL_KEYUP) {
            SDL_Scancode key = event.key.keysym.scancode;
            if (keyUpActions.find(key) != keyUpActions.end()) {
                for (const auto &action : keyUpActions[key]) {
                    action();
                }
            }
        }
    }

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    for (const auto &pair : keyHeldActions) {
        SDL_Scancode key = pair.first;
        if (currentKeyStates[key]) {
            for (const auto &action : pair.second) {
                action();
            }
        }
    }
}

void EventManager::registerKeyAction(SDL_Scancode key, KEY_EVENT_TYPE keyEventType, KeyAction action) {
    switch (keyEventType) {
        case KEYDOWN:
            keyDownActions[key].push_back(action);
            break;
        case KEYUP:
            keyUpActions[key].push_back(action);
            break;
        case KEYHELD:
            keyHeldActions[key].push_back(action);
            break;
    }
}


void EventManager::registerQuitAction(KeyAction action)
{
    quitActions.push_back(action);
}