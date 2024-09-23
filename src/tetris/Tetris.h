#pragma once

#include "GraphicsManager.h"
#include "Coordinate.h"
#include "RandomGenerator.h"
#include "EventManager.h"
#include <unordered_map>
#include <random>
#include <memory>
#include "Piece.h"
#include "Grid.h"

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

    int padding = 40;
    int screenWidth = 2560;
    int screenHeight = 1440;
    int gridSquareSize = (screenHeight - 2 * padding) / 22;
    int gridWidth = 10 * gridSquareSize;
    int gridHeight = 20 * gridSquareSize;
    int gridX = (screenWidth - gridWidth) / 2;   // Center horizontally
    int gridY = (screenHeight - gridHeight) / 2; // Center vertically

    std::unique_ptr<Piece> currentPiece;
    std::unique_ptr<Grid> grid;

    void setupEventHandlers();
    void update();
    void render() const;
};