#pragma once

#include "GraphicsManager.h"
#include "Coordinate.h"
#include "RandomGenerator.h"
#include "EventManager.h"
#include <unordered_map>
#include <random>
#include <memory>

class Tetris
{
public:
    Tetris();
    void run();
private:
    GraphicsManager graphics;
    EventManager eventManager;
    RandomGenerator rng;

    Uint32 lastTime;
    float deltaTime;
    bool quit = false;

    void setupEventHandlers();
    void update();
    void render() const;
};