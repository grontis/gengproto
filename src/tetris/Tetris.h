#pragma once

#include <unordered_map>
#include <random>
#include <memory>
#include <vector>

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
        core::GraphicsManager _graphics;
        core::EventManager _eventManager;
        core::RandomGenerator _rng;

        Uint32 _lastTime;
        float _deltaTime;
        bool _quit = false;

        Uint32 _movementCooldown = 100;
        Uint32 _rotationCooldown = 150;
        std::unordered_map<tetris::CONTROLS, Uint32> _lastMoveTimes;

        Uint32 _autoMovementCooldown = 400;
        Uint32 _lastAutoMovementTime;

        int _padding = 40;
        int _screenWidth = 2560;
        int _screenHeight = 1440;
        int _gridSquareSize = (_screenHeight - 2 * _padding) / 22;
        int _gridWidth = 10 * _gridSquareSize;
        int _gridHeight = 20 * _gridSquareSize;
        int _gridX = (_screenWidth - _gridWidth) / 2;   // Center horizontally
        int _gridY = (_screenHeight - _gridHeight) / 2; // Center vertically

        std::unique_ptr<Piece> _currentPiece;
        std::unique_ptr<Grid> _grid;

        void setupEventHandlers();
        void update();
        void render() const;
        void spawnNewPiece();
        void handleAutoMovement();
    };
}
