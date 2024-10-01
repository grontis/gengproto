#include "Grid.h"
#include "Piece.h"

namespace tetris
{
    Grid::Grid()
    {
        // TODO set dynamically
        _padding = 40;
        _screenWidth = 2560;
        _screenHeight = 1440;

        _gridSquareSize = (_screenHeight - 2 * _padding) / 22;

        _gridWidth = 10 * _gridSquareSize;
        _gridHeight = 20 * _gridSquareSize;

        _gridX = (_screenWidth - _gridWidth) / 2;   // Center horizontally
        _gridY = (_screenHeight - _gridHeight) / 2; // Center vertically
    }

    int Grid::getGridX() const { return _gridX; }
    int Grid::getGridY() const { return _gridY; }
    int Grid::getGridWidth() const { return _gridWidth; }
    int Grid::getGridHeight() const { return _gridHeight; }

    void Grid::draw(const core::GraphicsManager *graphics) const
    {
        drawVerticalLines(graphics);
        drawHorizontalLines(graphics);
    }

    void Grid::drawVerticalLines(const core::GraphicsManager *graphics) const
    {
        for (int i = 0; i <= 10; ++i)
        {
            int x = _gridX + i * _gridSquareSize;
            graphics->drawLine(x, _gridY, x, _gridY + _gridHeight);
        }
    }

    void Grid::drawHorizontalLines(const core::GraphicsManager *graphics) const
    {
        for (int i = 0; i <= 20; ++i)
        {
            int y = _gridY + i * _gridSquareSize;
            graphics->drawLine(_gridX, y, _gridX + _gridWidth, y);
        }
    }

    const std::vector<std::unique_ptr<Piece>> &Grid::getPlacedPieces() const
    {
        return _placedPieces;
    }

    void Grid::placePiece(std::unique_ptr<Piece> piece)
    {
        _placedPieces.push_back(std::move(piece));
    }
}
