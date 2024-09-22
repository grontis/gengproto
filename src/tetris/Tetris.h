#pragma once

#include "GraphicsManager.h"
#include "Coordinate.h"
#include "RandomGenerator.h"
#include "EventManager.h"
#include <unordered_map>
#include <random>
#include <memory>
#include "Piece.h"

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
    int movementSpeed = 700;
    bool quit = false;

    std::unique_ptr<Piece> currentPiece;

    void setupEventHandlers();
    void update();
    void render() const;
};