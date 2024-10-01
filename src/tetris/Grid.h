#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "Drawable.h"
#include "Coordinate.h"

namespace tetris
{
    class Piece;

    class Grid
        : core::Drawable
    {
    public:
        Grid();

        int getGridX() const;
        int getGridY() const;
        int getGridWidth() const;
        int getGridHeight() const;

        void draw(const core::GraphicsManager *graphics) const override;
        const std::vector<std::unique_ptr<Piece>> &getPlacedPieces() const;
        void placePiece(std::unique_ptr<Piece> piece);
        void handleRowCompletion();

    private:
        int _padding;
        int _gridSquareSize;
        int _gridX, _gridY;
        int _gridWidth, _gridHeight;
        int _screenWidth, _screenHeight;
        std::vector<std::unique_ptr<Piece>> _placedPieces;

        void drawVerticalLines(const core::GraphicsManager *graphics) const;
        void drawHorizontalLines(const core::GraphicsManager *graphics) const;
        void removeRow(int row);
        void shiftRowsDown(int row);
    };
}
