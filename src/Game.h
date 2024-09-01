#pragma once

#include "SDLManager.h"
#include "Entity.h"
#include "Coordinate.h"
#include <unordered_map>
#include <random>
#include <memory>

class Game {
public:
    Game();
    void run();

private:
    SDLManager sdlManager;
    //TODO refactor the need for a renderer out of this class so we can encapsulate SDL code into one class interface
    SDL_Renderer* renderer;

    std::unique_ptr<Entity> mainEntity;
    std::unordered_map<Coordinate, Entity> entities;

    //TODO refactor RNG specific code to its own class
    std::random_device rd;
    std::default_random_engine engine;
    std::uniform_int_distribution<int> rectSpawnDist;
    std::uniform_int_distribution<int> xDist;
    std::uniform_int_distribution<int> yDist;
    
    int spawnWaitCount = 0;
    const int spawnWaitLimit = 25;
    int movementSpeed = 700;

    Uint32 lastTime;
    float deltaTime;

    //TODO refactor window/SDL code to SDL manager
    const int windowWidth = 800;
    const int windowHeight = 600;

    bool quit = false;

    void handleEvents();
    void update();
    void render() const;
    void spawnEntities();
    void handleEntityInteractions();
    bool isWithinRange(const Coordinate& coord, const Coordinate& center, int width, int height) const;
};