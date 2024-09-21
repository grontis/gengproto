#pragma once

#include "GraphicsManager.h"
#include "Entity.h"
#include "Coordinate.h"
#include "RandomGenerator.h"
#include "EventManager.h"
#include <unordered_map>
#include <random>
#include <memory>

class Game
{
public:
    Game();
    void run();

private:
    GraphicsManager graphics;
    EventManager eventManager;
    RandomGenerator rng;

    std::unique_ptr<Entity> mainEntity;
    std::unordered_map<Coordinate, Entity> entitiesMap;

    int spawnWaitCount = 0;
    const int spawnWaitLimit = 25;
    int movementSpeed = 700;

    Uint32 lastTime;
    float deltaTime;

    bool quit = false;

    void setupEventHandlers();
    void update();
    void render() const;
    void spawn();
    void spawnEntities();
    void handleEntityInteractions();
    bool isWithinRange(const Coordinate &coord, const Coordinate &center, int width, int height) const;
};