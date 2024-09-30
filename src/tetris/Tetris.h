#pragma once

#include <unordered_map>
#include <random>
#include <memory>

#include "GraphicsManager.h"
#include "Coordinate.h"
#include "RandomGenerator.h"
#include "EventManager.h"

#include "Piece.h"
#include "Grid.h"
#include "PieceTemplates.h"
#include "Controls.h"

namespace tetris
{
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

        Uint32 movementCooldown = 100;
        Uint32 rotationCooldown = 150;
        std::unordered_map<tetris::CONTROLS, Uint32> lastMoveTimes;

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
}
